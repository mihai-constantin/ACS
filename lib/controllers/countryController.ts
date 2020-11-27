import { Request, Response } from 'express';
import Country from '../models/countryModel';

import ContryService from "../services/countryServices";

export class ContryController {
  private country_service: ContryService = new ContryService();

  // -----    GET    -----
  public async get_all_countries(req: Request, res: Response) {
    console.log('Getting all countries from database...');
    try {
      console.log(JSON.stringify(req.query));
      let countries = await this.country_service.getCountries(req.query);
      res.status(200).json(countries);
    } catch (err) {
      res.json(`Unable to get contries from database because ${err}`);
    }
  }

  // -----    GET BY ID    -----
  public async get_country_by_id(req: Request, res: Response) {
    console.log("Getting contry by id...");
    try {
      let country = await this.country_service.getCountryById(req.params.countryId);
      res.json(country);
    } catch (err) {
      res.json(`Unable to retrieve country from database, because ${err.message}`);
    }
  }

  // -----    POST    -----
  public async create_country(req: Request, res: Response) {
    console.log('Saving country into database...');
    try {
      let country = new Country(req.body);
      await this.country_service.createContry(country);
      res.status(201).json(country);
    } catch(err) {
      if (err.name == "ValidationError") {
        res.status(400).json(`Unable to save country into database because some fields are missing in request body.`);
      } else if (err.code == 11000) {
        res.status(409).json(`Unable to save country into database because the name is duplicate.`);
      } else {
        res.status(500).json(`Internal server error.`);
      }
    }
  }

}
