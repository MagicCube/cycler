import React from 'react';


export default class TimeMeter extends React.Component {
  static defaultProps = {
    value: 0
  }

  constructor(...args) {
    super(...args);

    this.state = {
      mode: 'elapsed'
    };
  }

  formatMinutes(seconds) {
    return (seconds / 60).toFixed(1);
  }

  handleClick() {
    if (this.state.mode === 'elapsed') {
      this.setState({ mode: 'clock' });
    } else {
      this.setState({ mode: 'elapsed' });
    }
  }

  render() {
    let value = null;
    if (this.state.mode === 'elapsed') {
      value = (
        <div className="value">
          <span className="number">{this.formatMinutes(this.props.value)}</span>
          <span className="unit">min</span>
        </div>
      );
    } else {
      value = (
        <div className="value">
          <span className="time">{new Date().toTimeString().substr(0, 5)}</span>
        </div>
      );
    }
    return (
      <div className="cy-time-meter cy-meter" onClick={() => this.handleClick()}>
        <div className="label">{this.state.mode === 'elapsed' ? 'Elapsed' : 'Time'}</div>
        {value}
      </div>
    );
  }
}
