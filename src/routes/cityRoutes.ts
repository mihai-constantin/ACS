import { Application, Request, Response } from 'express';
import { CityController } from '../controllers/cityController';

export class CityRoutes {

  private city_controller: CityController = new CityController();

  public route(app: Application) {

    // -----    POST    -----
    app.post('/api/cities', (req: Request, res: Response) => {
      this.city_controller.create_city(req, res);
    });
  }

}