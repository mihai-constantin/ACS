CREATE TABLE IF NOT EXISTS books (
    id serial PRIMARY KEY,
    title varchar NOT NULL,
    author varchar NOT NULL
);