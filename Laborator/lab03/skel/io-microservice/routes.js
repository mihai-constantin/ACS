const Router = require('express').Router();

const BooksController = require('./books/controllers.js');

Router.use('/books', BooksController);

module.exports = Router;