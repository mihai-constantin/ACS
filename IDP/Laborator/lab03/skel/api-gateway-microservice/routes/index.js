const Router = require('express').Router();

const BooksRoute = require('./books.js');

Router.use('/books', BooksRoute);

module.exports = Router;
