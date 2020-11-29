import { CreateQuery } from 'mongoose';
import City, { ICity } from '../models/cityModel';

export default class CityService {

  // -----    GET    -----
  public async getCities(query: any) {
    return await City.find(query)
    .then(cities => {
      return cities;
    })
    .catch(err => {
      throw new Error(`Unable to retrieve cities list from database because ${err.message}`);
    });
  }

  // -----    GET BY ID    -----
  public async getCityById(id: string) {
    return await City.findById(id)
    .then(city => {
      return city;
    })
    .catch(err => {
      throw new Error(`Unable to retrieve city from database, because ${err.message}`);
    });
  }

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