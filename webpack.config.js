const path = require('path');

module.exports = {
  entry: './client/Index.bs.js',
  // If you ever want to use webpack during development, change 'production'
  // to 'development' as per webpack documentation. Again, you don't have to
  // use webpack or any other bundler during development! Recheck README if
  // you didn't know this
  mode: 'production',
  devtool: 'inline-source-map',
  output: {
    path: path.join(__dirname, "build"),
    filename: 'index.deploy.js',
  },
};