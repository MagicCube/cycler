import React from 'react';


export default class TimeMeter extends React.Component {
  static defaultProps = {
    value: 0
  }

  formatMinutes(seconds) {
    return (seconds / 60).toFixed(1);
  }

  render() {
    return (
      <div className="cy-time-meter cy-meter">
        <div className="label">Elapsed</div>
        <div className="value">
          <span className="number">{this.formatMinutes(this.props.value)}</span>
          <span className="unit">min</span>
        </div>

        <div className="label2">Time</div>
        <div className="value2">
          <span className="time">{new Date().toTimeString().substr(0, 5)}</span>
        </div>
      </div>
    );
  }
}
