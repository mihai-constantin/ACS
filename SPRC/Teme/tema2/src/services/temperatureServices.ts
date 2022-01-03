import { CreateQuery } from 'mongoose';
import Temperature, { ITemperature } from '../models/temperatureModel';

export default class TemperatureService {

  // -----    GET    -----
  public async getTemperatures(query: any) {
    return await Temperature.find(query)
    .then(temperatures => {
      return temperatures;
    })
    .catch(err => {
      throw new Error(`Unable to retrieve temperatures list from database because ${err.message}`);
    });
  }

  // -----    GET BY ID    -----
  public async getTemperatureById(id: string) {
    return await Temperature.findById(id)
    .then(temperature => {
      return temperature;
    })
    .catch(err => {
      throw new Error(`Unable to retrieve temperature from database, because ${err.message}`);
    });
  }

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