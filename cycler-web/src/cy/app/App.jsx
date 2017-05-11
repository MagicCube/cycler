import React from 'react';

import Meters from '../meter/Meters';

import '../res/app.less';


export default class App extends React.Component {
  render() {
    return (
      <div className="cy-app">
        <div className="side-panel">
          <Meters />
        </div>
        <div className="chart-panel">
        </div>
      </div>
    );
  }
}
