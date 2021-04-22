const {
    Pool
  } = require('pg');
  
  const options = {
    host: process.env.PGHOST,
    database: process.env.PGDATABASE,
    port: process.env.PGPORT,
    user: process.env.PGUSER,
    password: process.env.PGPASSWORD,
  }
  
  const pool = new Pool(options);
  
  const query = async (text, params) => {
    const {
      rows,
    } = await pool.query(text, params);
    return rows;
  };
  
  module.exports = {
    query,
  };