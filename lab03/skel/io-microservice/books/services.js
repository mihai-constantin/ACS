const {
    query
} = require('../data');

const getBooks = async () => {
    console.info(`Getting all books ...`);

    const books = await query("SELECT id, title FROM books");

    return books;
};

const getBookById = async (id) => {
    console.info(`Getting book ${id} ...`);

    const books = await query("SELECT title, author, genre FROM books WHERE id = $1", [id]);

    return books[0];
};

const addBook = async (title, author, genre) => {
    console.info(`Adding book with title ${title}, author ${author} and genre ${genre} ...`);

    const books = await query("INSERT INTO books (title, author, genre) VALUES ($1, $2, $3) RETURNING id", [title, author, genre]);

    return books[0].id;
};  

module.exports = {
    getBooks,
    getBookById,
    addBook
}