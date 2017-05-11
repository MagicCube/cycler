import React from 'react';


export default class SpeedMeter extends React.Component {
  static defaultProps = {
    value: 0,
    averageValue: 0
  }

  constructor(...args) {
    super(...args);
    this.state = {
      mode: 'tantaneous'
    };
  }

  handleClick() {
    if (this.state.mode === 'tantaneous') {
      this.setState({ mode: 'average' });
    } else {
      this.setState({ mode: 'tantaneous' });
    }
  }

  render() {
    return (
      <div className="cy-speed-meter cy-meter" onClick={() => this.handleClick()}>
        <div className="label">{this.state.mode === 'tantaneous' ? 'Speed' : 'Average Speed'}</div>
        <div className="value">
          <span className="number">
            { this.state.mode === 'tantaneous' ? this.props.value.toFixed(2) : this.props.averageValue.toFixed(2) }
          </span>
          <span className="unit">km/h</span>
        </div>
      </div>
    );
  }
}
