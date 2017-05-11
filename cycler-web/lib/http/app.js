const bodyParser = require('body-parser');
const compression = require('compression');
const express = require('express');


const devMode = process.env.NODE_ENV !== 'production';
console.log(`Running in ${devMode ? 'DEV' : 'PRODUCTION'} mode.`);

// Instantialize express.
const app = express();

// Add HTTP body parsers.
app.use(compression());
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));

if (devMode) {
  // Add Webpack
  const webpack = require('webpack');
  const webpackMiddleware = require('webpack-dev-middleware');
  const webpackConfig = require('../../webpack.config');
  const compiler = webpack(webpackConfig);
  app.use(webpackMiddleware(compiler, webpackConfig.devServer));
} else {
  app.use(express.static('public'));
}


module.exports = app;
