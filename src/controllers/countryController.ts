import { Request, Response } from 'express';
import { requestResponse } from '../errors';
import { response_status_codes } from '../errors/model';
import Country from '../models/countryModel';
import City from '../models/cityModel';
import Temperature from '../models/temperatureModel';

import ContryService from "../services/countryServices";
import CityService from '../services/cityServices';

export class ContryController {
  
  private country_service: ContryService = new ContryService();
  private city_service: CityService = new CityService();

  // -----    GET    -----
  public async get_all_countries(req: Request, res: Response) {
    console.log('Getting all countries from database...');
    try {
      let countries = await this.country_service.getCountries(req.query);
      requestResponse(response_status_codes.success, countries, res);
    } catch (err) {
      requestResponse(response_status_codes.internal_server_error, `Unable to get contries from database because ${err}`, res);
    }
  }

  // -----    GET BY ID    -----
  public async get_country_by_id(req: Request, res: Response) {
    console.log("Getting contry by id...");
    try {
      let country = await this.country_service.getCountryById(req.params.countryId);
      if (country) {
        requestResponse(response_status_codes.success, country, res);
      } else {
        requestResponse(response_status_codes.not_found, 'Country not found into database.', res);
      }
    } catch (err) {
      requestResponse(response_status_codes.not_found, 'Invalid country id format.', res);
    }
  }

  // -----    POST    -----
  public async create_country(req: Request, res: Response) {
    console.log('Saving country into database...');
    try {
      let country = new Country(req.body);
      await this.country_service.createCountry(country);
      requestResponse(response_status_codes.created, country, res);
    } catch(err) {
      if (err.name == "ValidationError") {
        requestResponse(response_status_codes.bad_request, 'Unable to save country into database because some fields are missing in request body.', res);
      } else if (err.code == 11000) {
        requestResponse(response_status_codes.conflict, `Unable to save ${req.body.name} into database because the name is duplicate.`, res);
      } else {
        requestResponse(response_status_codes.internal_server_error, 'Internal server error.', res);
      }
    }
  }
  
  // -----    PUT    -----
  public async update_country(req: Request, res: Response) {
    console.log('Updating country into database...');
    try {
      let country = await this.country_service.getCountryById(req.params.countryId);
      if (country) {
        if (req.body.name && req.body.latitude && req.body.longitude) {
          let countries = await this.country_service.getCountries(req.query);
          for (let c of countries) {
            if (c.name == req.body.name && c._id != req.params.countryId) {
              requestResponse(response_status_codes.conflict, `Country ${req.body.name} is already into database.`, res);
              return;
            }
          }
          country.name = req.body.name;
          country.latitude = req.body.latitude;
          country.longitude = req.body.longitude;
          country.save();
          requestResponse(response_status_codes.success, country, res);
        } else {
          requestResponse(response_status_codes.bad_request, 'Unable to save country into database because some fields are missing in request body.', res);
        }
      } else {
        requestResponse(response_status_codes.not_found, 'Country id not found into database.', res);
      } 
    } catch (err) {
      requestResponse(response_status_codes.not_found, 'Invalid country id format.', res);
    }
  }

  // -----    DELETE    -----
  public async delete_country(req: Request, res: Response) {
    console.log('Deleting country from database...');
    try {
      let country = await this.country_service.getCountryById(req.params.countryId);
      if (country) {
        let cities = await this.city_service.getCities({country_id: req.params.countryId});
        for (let city of cities) {
          await Temperature.deleteMany({city_id: city._id});
        }
        await City.deleteMany({country_id: req.params.countryId});
        country.remove((err) => {
          if (err) {
            requestResponse(response_status_codes.internal_server_error, `Unable to delete country from database, because ${err.message}`, res);
          }
          requestResponse(response_status_codes.success, `Country ${country?.name} was successfully deleted from databse.`, res);
        });
      } else {
        requestResponse(response_status_codes.not_found, 'Country id not found into database.', res);
      }
    } catch (err) {
      requestResponse(response_status_codes.not_found, 'Invalid country id format.', res);
    }
    
  }

}
