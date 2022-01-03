import { CreateQuery } from 'mongoose';
import Country, { ICountry } from '../models/countryModel';

export default class ContryService {

  // -----    GET    -----
  public async getCountries(query: any) {
    return await Country.find(query)
    .then(countries => {
      return countries;
    })
    .catch(err => {
      throw new Error(`Unable to retrieve countries list from database because ${err.message}`);
    });
  }

  // -----    GET BY ID    -----
  public async getCountryById(id: string) {
    return await Country.findById(id)
    .then(country => {
      return country;
    })
    .catch(err => {
      throw new Error(`Unable to retrieve country from database, because ${err.message}`);
    });
  }

  // -----    POST    -----
  public async createCountry({_id, name, latitude, longitude}: CreateQuery<ICountry>): Promise<ICountry> {
    return Country.create({
      _id,
      name,
      latitude,
      longitude
    })
    .then((data: ICountry) => {
      return data;
    })
    .catch((error: Error) => {
      throw error;
    });
  }

}
