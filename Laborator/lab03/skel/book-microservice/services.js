const {
    sendRequest
} = require('./http-client');

const getBooks = async () => {
    console.info(`Sending request to IO for all books ...`);
    
    const options = {
        url: `http://${process.env.IO_SERVICE_API_ROUTE}/books`
    }

    const books = await sendRequest(options);

    return books;
};

const getBookById = async (id) => {
    console.info(`Sending request to IO for book ${id} ...`);

    const options = {
        url: `http://${process.env.IO_SERVICE_API_ROUTE}/books/${id}`
    }

    const book = await sendRequest(options);

    return book;
};

const addBook = async (title, author, genre) => {
    console.info(`Sending request to IO to add book with title ${title}, author ${author} and genre ${genre} ...`);

    const options = {
        url: `http://${process.env.IO_SERVICE_API_ROUTE}/books`,
        method: 'POST',
        data: {
            title,
            author,
            genre
        }
    }

    const id = await sendRequest(options);

    return id;
};  

module.exports = {
    getBooks,
    getBookById,
    addBook
}