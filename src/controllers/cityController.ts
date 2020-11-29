import { Request, Response } from 'express';
import City from '../models/cityModel'

import CityService from "../services/cityServices"
import ContryService from '../services/countryServices';

export class CityController {

  private city_service: CityService = new CityService();
  private country_service: ContryService = new ContryService();

  // -----    GET    -----
  public async get_all_cities(req: Request, res: Response) {
    console.log('Getting all cities from database...');
    try {
      let cities = await this.city_service.getCities(req.query);
      res.status(200).json(cities);
    } catch (err) {
      res.json(`Unable to get cities from database because ${err}`);
    }
  }

  // -----    GET BY ID    -----
  public async get_city_by_id(req: Request, res: Response) {
    console.log("Getting city by id...");
    try {
      let city = await this.city_service.getCityById(req.params.cityId);
      if (city) {
        res.json(city);
      } else {
        res.status(404).json('City not found into database.');
      }
    } catch (err) {
      res.status(500).json('Invalid city id format.');
    }
  }

  // -----    GET BY COUNTRY    -----
  public async get_city_by_country(req: Request, res: Response) {
    console.log("Getting cities by contry...");
    try {
      let country = await this.country_service.getCountryById(req.params.countryId);
      if (country) {
        let cities = await this.city_service.getCities({country_id: req.params.countryId});
        res.status(200).json(cities);
      } else {
        res.status(404).json('Country not found into database.');
      }
    } catch (err) {
      res.status(500).json('Invalid country id format.');
    }
  }

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

  // -----    PUT    -----
  public async update_city(req: Request, res: Response) {
    console.log('Updating city into database...');
    try {
      let city = await this.city_service.getCityById(req.params.cityId);
      if (city) {
        if (req.body.name && req.body.latitude && req.body.longitude && req.body.country_id) {
          try {
            let country = await this.country_service.getCountryById(req.body.country_id);
            if (country) {
              // console.log(JSON.stringify(country));
              let cities = await this.city_service.getCities({country_id: country._id});
              for (let c of cities) {
                if (c.name == req.body.name) {
                  res.status(409).json(`Country ${country.name} already has ${c.name} city into database`);
                  return;
                }
              }
              city.name = req.body.name;
              city.latitude = req.body.latitude;
              city.longitude = req.body.longitude;
              city.country_id = req.body.country_id;
              city.save();
              res.status(200).json(city);
            } else {
              res.status(404).json("Contry not found into database");
            }
          } catch (err) {
            res.status(500).json("Invalid country id format.");
          }
        } else {
          res.status(400).json(`Unable to save city into database because some fields are missing in request body.`);
        }
      } else {
        res.status(404).json('City id not found into database.');
      } 
    } catch (err) {
      res.status(500).json('Invalid city id format.');
    }
  }

}