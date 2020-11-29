import { Request, Response } from 'express';
import { requestResponse } from '../errors';
import { response_status_codes } from '../errors/model';
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
      requestResponse(response_status_codes.success, cities, res);
    } catch (err) {
      requestResponse(response_status_codes.internal_server_error, `Unable to get cities from database because ${err}`, res);
    }
  }

  // -----    GET BY ID    -----
  public async get_city_by_id(req: Request, res: Response) {
    console.log("Getting city by id...");
    try {
      let city = await this.city_service.getCityById(req.params.cityId);
      if (city) {
        requestResponse(response_status_codes.success, city, res);
      } else {
        requestResponse(response_status_codes.not_found, 'City not found into database.', res);
      }
    } catch (err) {
      requestResponse(response_status_codes.not_found, 'Invalid city id format.', res);
    }
  }

  // -----    GET BY COUNTRY    -----
  public async get_city_by_country(req: Request, res: Response) {
    console.log("Getting cities by contry...");
    try {
      let country = await this.country_service.getCountryById(req.params.countryId);
      if (country) {
        let cities = await this.city_service.getCities({country_id: req.params.countryId});
        requestResponse(response_status_codes.success, cities, res);
      } else {
        requestResponse(response_status_codes.not_found, 'Country not found into database.', res);
      }
    } catch (err) {
      requestResponse(response_status_codes.not_found, 'Invalid country id format.', res);
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
        requestResponse(response_status_codes.created, city, res);
      } else {
        requestResponse(response_status_codes.not_found, 'Country not found into database.', res);
      }
    } catch(err) {
      if (err.name == "ValidationError") {
        requestResponse(response_status_codes.bad_request, 'Unable to save city into database because some fields are missing in request body.', res);
      } else if (err.code == 11000) {
        requestResponse(response_status_codes.conflict, 'Unable to save city into database because the tuple (country_id, name) is duplicate.', res);
      } else {
        requestResponse(response_status_codes.not_found, 'Invalid country id format.', res);
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
              let cities = await this.city_service.getCities({country_id: country._id});
              for (let c of cities) {
                if (c.name == req.body.name) {
                  requestResponse(response_status_codes.conflict, `Country ${country.name} already has ${c.name} city into database`, res);
                  return;
                }
              }
              city.name = req.body.name;
              city.latitude = req.body.latitude;
              city.longitude = req.body.longitude;
              city.country_id = req.body.country_id;
              city.save();
              requestResponse(response_status_codes.success, city, res);
            } else {
              requestResponse(response_status_codes.not_found, 'Contry not found into database', res);
            }
          } catch (err) {
            requestResponse(response_status_codes.not_found, 'Invalid country id format.', res);
          }
        } else {
          requestResponse(response_status_codes.bad_request, 'Unable to save city into database because some fields are missing in request body.', res);
        }
      } else {
        requestResponse(response_status_codes.not_found, 'City id not found into database.', res);
      } 
    } catch (err) {
      requestResponse(response_status_codes.not_found, 'Invalid city id format.', res);
    }
  }

  // -----    DELETE    -----
  public async delete_city(req: Request, res: Response) {
    console.log('Deleting city from database...');
    try {
      let city = await this.city_service.getCityById(req.params.cityId);
      if (city) {
        city.remove((err) => {
          if (err) {
            requestResponse(response_status_codes.internal_server_error, `Unable to delete city from database, because ${err.message}`, res);
          }
          requestResponse(response_status_codes.success, `City ${city?.name} was successfully deleted from databse.`, res);
        });
      } else {
        requestResponse(response_status_codes.not_found, 'City id not found into database.', res);
      }
    } catch (err) {
      requestResponse(response_status_codes.not_found, 'Invalid city id format.', res);
    }
  }

}
