const Router = require('express').Router();

const {
    ServerError
} = require('./errors');

const {
    getBookById,
    getBooks,
    addBook
} = require('./services.js');

Router.get('/', async (req, res) => {
    
    const books = await getBooks();

    res.json(books);
});

Router.get('/:id', async (req, res) => {

    const {
        id
    } = req.params;

    const book = await getBookById(id);

    res.json(book);
});

Router.post('/', async (req, res) => {

    const {
        title,
        author,
        genre
    } = req.body;

    if (!title) {
        throw new ServerError('No title provided!', 400);
    }

    if (!author) {
        throw new ServerError('No author provided!', 400);
    }

    if (!genre) {
        throw new ServerError('No genre provided!', 400);
    }

    const id = await addBook(title, author, genre);

    res.json(id);
});

module.exports = Router;