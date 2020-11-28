import { Request, Response } from 'express';
import Country from '../models/countryModel';

import ContryService from "../services/countryServices";

export class ContryController {
  private country_service: ContryService = new ContryService();

  // -----    GET    -----
  public async get_all_countries(req: Request, res: Response) {
    console.log('Getting all countries from database...');
    try {
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
      if (country) {
        res.json(country);
      } else {
        res.status(404).json('Country not found into database.');
      }
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
  
  // -----    PUT    -----
  public async update_country(req: Request, res: Response) {
    console.log('Updating country into database...');
    let country = await this.country_service.getCountryById(req.params.countryId);
    if (country) {
      if (req.body.name && req.body.latitude && req.body.longitude) {
        // if req.body.name exists already into database -> conflict
        let countries = await this.country_service.getCountries(req.query);
        for (let c of countries) {
          if (c.name == req.body.name && c._id != req.params.countryId) {
            res.status(409).json(`Country ${req.body.name} is already into database.`);
            return;
          }
        }
        country.name = req.body.name;
        country.latitude = req.body.latitude;
        country.longitude = req.body.longitude;
        country.save();
        res.status(200).json(country);
      } else {
        res.status(400).json(`Unable to save country into database because some fields are missing in request body.`);
      }
    } else {
      res.status(404).json('Country id not found into database.');
    } 
  }

  // -----    DELETE    -----
  public async delete_country(req: Request, res: Response) {
    console.log('Deleting country from database...');
    let country = await this.country_service.getCountryById(req.params.countryId);
    if (country) {
      country.remove((err) => {
        if (err) {
          res.json(`Unable ro delete contry from database, because ${err.message}`);
        }
        res.status(200).json(`Country ${country.name} was successfully deleted from databse.`);
      });
    } else {
      res.status(404).json('Country id not found into database.');
    }
  }

}
