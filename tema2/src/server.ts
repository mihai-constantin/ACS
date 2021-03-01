import app from "./config/app";
import endpoint from './endpoints.config';

const PORT = endpoint.PORT;

app.listen(PORT, () => {
  console.log('Express server listening on port ' + PORT);
});
