import { connect } from 'react-redux';
import L from 'leaflet';
import polyline from '@mapbox/polyline';
import React from 'react';
import Smooth from '../../vendor/smooth';

import routeData from '../../../data/route.json';

import '../res/map.less';


const ORIGIN = [32.05157, 118.72953];
const DESTINATION = [32.10018, 118.90189];


@connect(
  state => ({ distance: state.now.distance })
)
export default class Map extends React.Component {
  componentDidMount() {
    this.initMap();
    this.initRoute();
    this.initMarker();
    this.setDistance(0);
  }

  initMap() {
    this.map = L.map(this.container, {
      center: [32.05157, 118.72953],
      zoom: 14,
      zoomControl: false
    });
    this.map.on('dragend', this._map_dragend.bind(this));
    this.tileLayer = L.tileLayer('https://api.mapbox.com/styles/v1/mapbox/traffic-night-v2/tiles/256/{z}/{x}/{y}?access_token=pk.eyJ1IjoiaGVucnkxOTg0IiwiYSI6ImI1a0FvUzQifQ.zLCAzKNjXNiRUQoJBzAsZQ');
    this.map.addLayer(this.tileLayer);
  }

  initRoute() {
    const lats = [];
    const lngs = [];
    const rawPoints = polyline.decode(routeData.trip.legs[0].shape);
    const points = rawPoints.map((p) => {
      lats.push(p[0] / 10);
      lngs.push(p[1] / 10);
      return [p[0] / 10, p[1] / 10];
    });
    const latSmooth = Smooth(lats);
    const lngSmooth = Smooth(lngs);
    this.steps = [];
    const distance = 20 * 1000;
    for (let i = 0; i < distance; i++) {
      const index = points.length / distance * i;
      const step = [
        latSmooth(index),
        lngSmooth(index)
      ];
      this.steps.push(step);
    }
    this.map.addLayer(L.polyline(points, { color: 'silver' }));
  }

  initMarker() {
    this.marker = L.circleMarker(ORIGIN, {
      radius: 8,
      color: 'red',
      stroke: 1,
      fillColor: 'red',
      fillOpacity: 0.9
    });
    this.map.addLayer(this.marker);
  }

  setDistance(km) {
    const stepIndex = Math.round(km * 1000);
    const point = this.steps[stepIndex];
    this.marker.setLatLng(point);
    if (this._last_dragend === 0 || new Date() - this._last_dragend > 5000) {
      this.map.panTo(point, { noMoveStart: true });
    }
  }

  render() {
    if (this.props.distance) {
      this.setDistance(this.props.distance);
    }
    return (
      <div ref={(div) => { this.container = div; }} className="cy-map" />
    );
  }


  _last_dragend = 0;
  _map_dragend() {
    this._last_dragend = new Date().getTime();
  }
}
