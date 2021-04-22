const Router = require("express").Router();

const { sendRequest } = require("../http-client");

Router.get("/", async (req, res) => {
  console.info(`Forwarding request for get books ...`);

  const getBooksRequest = {
    url: `http://${process.env.BOOKS_SERVICE_API_ROUTE}`,
  };

  const books = await sendRequest(getBooksRequest);

  res.json(books);
});

Router.get("/:id", async (req, res) => {
  const { id } = req.params;

  console.info(`Forwarding request for get book ${id} ...`);

  const getBookIdRequest = {
    url: `http://${process.env.BOOKS_SERVICE_API_ROUTE}/${id}`,
  };

  const book = await sendRequest(getBookIdRequest);

  res.json(book);
});

Router.post("/", async (req, res) => {
  const { title, author, genre } = req.body;

  const postBookRequest = {
    url: `http://${process.env.BOOKS_SERVICE_API_ROUTE}`,
    method: "POST",
    data: {
      title,
      author,
      genre,
    },
  };

  const id = await sendRequest(postBookRequest);

  res.json({ id });
});

module.exports = Router;
