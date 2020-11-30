import { CreateQuery } from 'mongoose';
import Temperature, { ITemperature } from '../models/temperatureModel';

export default class TemperatureService {

  // -----    POST    -----
  public async createTemperature({_id, value, timestamp, city_id}: CreateQuery<ITemperature>): Promise<ITemperature> {
    return Temperature.create({
      _id,
      value,
      timestamp,
      city_id
    })
    .then((data: ITemperature) => {
      return data;
    })
    .catch((error: Error) => {
      throw error;
    });
  }

}