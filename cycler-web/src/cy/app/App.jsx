import React from 'react';

import Map from '../map/Map';
import Meters from '../meter/Meters';

import '../res/app.less';


export default class App extends React.Component {
  render() {
    return (
      <div className="cy-app">
        <aside className="side-panel">
          <Meters />
        </aside>
        <main className="main-panel">
          <Map />
        </main>
      </div>
    );
  }
}
