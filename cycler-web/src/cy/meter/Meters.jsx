import React from 'react';

import { now, reset } from '../api';
import DistanceMeter from './DistanceMeter';
import SpeedMeter from './SpeedMeter';
import TimeMeter from './TimeMeter';

import '../res/meters.less';


export default class Meters extends React.Component {
  constructor(...args) {
    super(...args);

    this.state = { };
  }

  componentDidMount() {
    this.poll();
  }

  async poll() {
    try {
      await this.updateData();
    } catch (e) {

    }

    setTimeout(() => {
      this.poll();
    }, 2000);
  }

  async updateData() {
    const data = await now();
    this.setState(data);
  }

  reset() {
    reset();
  }

  render() {
    return (
      <div className={this.state.state === 1 ? 'cy-meters running' : 'cy-meters'}>
        <section>
          <DistanceMeter value={this.state.distance} />
        </section>
        <section>
          <SpeedMeter value={this.state.speed} averageValue={this.state.distance / (this.state.elapsed / 60 / 60)} />
        </section>
        <section>
          <TimeMeter value={this.state.elapsed} />
        </section>
        <section>
          <button className="reset" onClick={() => this.reset()}>RESET</button>
        </section>
      </div>
    );
  }
}
