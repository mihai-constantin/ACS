import { CreateQuery } from 'mongoose';
import City, { ICity } from '../models/cityModel';

export default class CityService {
  
  // -----    POST    -----
  public async createCity({_id, name, latitude, longitude, country_id}: CreateQuery<ICity>): Promise<ICity> {
    return City.create({
      _id,
      name,
      latitude,
      longitude,
      country_id
    })
    .then((data: ICity) => {
      return data;
    })
    .catch((error: Error) => {
      throw error;
    });
  }

}