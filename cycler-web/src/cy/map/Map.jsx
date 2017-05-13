import L from 'leaflet';
import React from 'react';

import '../res/map.less';

// 32.05157, 118.72953
// 32.10018, 118.90189

export default class Map extends React.Component {
  componentDidMount() {
    this.map = L.map(this.container, {
      center: [32.05157, 118.72953],
      zoom: 17,
      zoomControl: false
    });
    this.tileLayer = L.tileLayer('https://api.mapbox.com/styles/v1/mapbox/traffic-night-v2/tiles/256/{z}/{x}/{y}?access_token=pk.eyJ1IjoiaGVucnkxOTg0IiwiYSI6ImI1a0FvUzQifQ.zLCAzKNjXNiRUQoJBzAsZQ');
    this.map.addLayer(this.tileLayer);
  }

  render() {
    return (
      <div ref={(div) => { this.container = div; }} className="cy-map" />
    );
  }
}
