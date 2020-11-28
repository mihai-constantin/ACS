import express from 'express';
import mongoose from 'mongoose'
import bodyParser from 'body-parser';
import { CountryRoutes } from '../routes/countryRoutes';

class App {

  public app: express.Application;
  public mongoUrl: string = 'mongodb://mongo:27017/db-sprc';

  private country_routes: CountryRoutes = new CountryRoutes();

  constructor() {
    this.app = express();
    this.config();
    this.mongoSetup();
    this.country_routes.route(this.app);
  }

  private config(): void {
    // support application/json type post data
    this.app.use(bodyParser.json());
    //support application/x-www-form-urlencoded post data
    this.app.use(bodyParser.urlencoded({ extended: false }));
  }

  private mongoSetup(): void {
    mongoose.connect(this.mongoUrl, { useNewUrlParser: true, useUnifiedTopology: true, useCreateIndex: true, useFindAndModify: false });
    console.log('Connected to MongoDB!');
  }
}
export default new App().app;
