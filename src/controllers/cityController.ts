import { Request, Response } from 'express';
import City from '../models/cityModel'

import CityService from "../services/cityServices"
import ContryService from '../services/countryServices';

export class CityController {

  private city_service: CityService = new CityService();
  private country_service: ContryService = new ContryService();

  // -----    POST    -----
  public async create_city(req: Request, res: Response) {
    console.log('Saving city into database...');
    try {
      let country = await this.country_service.getCountryById(req.body.country_id);
      if (country) {
        let city = new City(req.body);
        await this.city_service.createCity(city);
        res.status(201).json(city);
      } else {
        res.status(404).json('Country not found into database.');
      }
    } catch(err) {
      if (err.name == "ValidationError") {
        res.status(400).json(`Unable to save city into database because some fields are missing in request body.`);
      } else if (err.code == 11000) {
        res.status(409).json(`Unable to save city into database because the tuple (country_id, name) is duplicate.`);
      } else {
        res.status(500).json('Invalid country id format.');
      }
    }
  }

}