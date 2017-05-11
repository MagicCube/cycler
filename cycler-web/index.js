const http = require('http');

const app = require('./lib/http/app');

const httpServer = http.createServer(app);
const port = process.env.PORT ? parseInt(process.env.PORT, 0) : 3000;
httpServer.listen(port, () => {
  console.info(`cycler-web server is now listening at HTTP ${port}.`);
});
