import { Request, Response } from 'express';
import { requestResponse } from '../errors';
import { response_status_codes } from '../errors/model';
import Temperature from '../models/temperatureModel';

import TemperatureService from "../services/temperatureServices";
import CityService from "../services/cityServices";

export class TemperatureController {

  private temperature_service: TemperatureService = new TemperatureService();
  private city_service: CityService = new CityService();

  // -----    POST    -----
  public async create_temperature(req: Request, res: Response) {
    console.log('Saving temperature into database...');
    try {
      if (!req.body.value || !req.body.city_id) {
        requestResponse(response_status_codes.bad_request, 'Unable to save temperature into database because some fields are missing in request body.', res);
        return;
      }
      let city = await this.city_service.getCityById(req.body.city_id);
      if (city) {
        let temperature = new Temperature(req.body);
        let current_day = new Date(Date.now());
        temperature.timestamp = current_day.toISOString().split('T')[0];
        await this.temperature_service.createTemperature(temperature);
        requestResponse(response_status_codes.created, temperature, res);
      } else {
        requestResponse(response_status_codes.not_found, 'City not found into database.', res);
      }
    } catch(err) {
      if (err.name == "ValidationError") {
        requestResponse(response_status_codes.bad_request, 'Unable to save temperature into database because some fields are missing in request body.', res);
      } else if (err.code == 11000) {
        requestResponse(response_status_codes.conflict, 'Unable to save temperature into database because the tuple (city_id, timestamp) is duplicate.', res);
      } else {
        requestResponse(response_status_codes.not_found, 'Invalid city id format.', res);
      }
    }
  }

}