import { Application, Request, Response } from 'express';
import { CityController } from '../controllers/cityController';

export class CityRoutes {

  private city_controller: CityController = new CityController();

  public route(app: Application) {

    // -----    GET    -----
    app.get('/api/cities', (req: Request, res: Response) => {
      this.city_controller.get_all_cities(req, res);
    });

    // -----    GET BY ID    -----
    app.get('/api/cities/:cityId', (req: Request, res: Response) => {
      this.city_controller.get_city_by_id(req, res);
    });

    // -----    GET BY COUNTRY    -----
    app.get('/api/cities/country/:countryId', (req: Request, res: Response) => {
      this.city_controller.get_city_by_country(req, res);
    });

    // -----    POST    -----
    app.post('/api/cities', (req: Request, res: Response) => {
      this.city_controller.create_city(req, res);
    });
  }

}