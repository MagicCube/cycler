import { bindActionCreators } from 'redux';
import { connect } from 'react-redux';
import React from 'react';

import actionCreators from '../action/creators';

import DistanceMeter from './DistanceMeter';
import SpeedMeter from './SpeedMeter';
import TimeMeter from './TimeMeter';

import '../res/meters.less';


@connect(
  state => state.now,
  dispatch => ({
    actions: bindActionCreators(actionCreators, dispatch)
  })
)
export default class Meters extends React.Component {
  render() {
    return (
      <div className={this.props.state === 1 ? 'cy-meters running' : 'cy-meters'}>
        <section>
          <DistanceMeter value={this.props.distance} />
        </section>
        <section>
          <SpeedMeter value={this.props.speed} averageValue={this.props.distance / (this.props.elapsed / 60 / 60)} />
        </section>
        <section>
          <TimeMeter value={this.props.elapsed} />
        </section>
        <section>
          <button className="reset" onClick={() => this.props.actions.reset()}>RESET</button>
        </section>
      </div>
    );
  }
}
