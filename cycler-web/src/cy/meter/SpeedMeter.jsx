import React from 'react';


export default class SpeedMeter extends React.Component {
  static defaultProps = {
    value: 0
  }

  render() {
    return (
      <div className="cy-speed-meter cy-meter">
        <div className="label">Speed</div>
        <div className="value">
          <span className="number">{this.props.value.toFixed(2)}</span>
          <span className="unit">km/h</span>
        </div>
      </div>
    );
  }
}
