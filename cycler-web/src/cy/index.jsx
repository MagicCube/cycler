import React from 'react';
import { render } from 'react-dom';
import { Provider } from 'react-redux';

import App from './app/App.jsx';
import actionCreators from './action/creators';
import { configStore } from './store';

import './index.html';
import './res/index.less';

const store = configStore();

function poll() {
  updateNow();

  setTimeout(() => {
    poll();
  }, 2000);
}

function updateNow() {
  store.dispatch(actionCreators.updateNow());
}


render(
  <Provider store={store}>
    <App />
  </Provider>,
  document.getElementById('cy-root')
);

poll();
