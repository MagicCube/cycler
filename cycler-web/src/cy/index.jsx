import React from 'react';
import { render } from 'react-dom';

import App from './app/App.jsx';

import './index.html';
import './res/index.less';


render(
  <App />,
  document.getElementById('cy-root')
);
