import React from 'react';


export default class DistanceMeter extends React.Component {
  static defaultProps = {
    value: 0
  }

  render() {
    return (
      <div className="cy-distance-meter cy-meter">
        <div className="label">Distance</div>
        <div className="value">
          <span className="number">{this.props.value.toFixed(2)}</span>
          <span className="unit">km</span>
        </div>
      </div>
    );
  }
}
