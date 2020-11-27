import { Application, Request, Response } from 'express';
import { ContryController } from "../controllers/countryController";

export class CountryRoutes {

  private country_controller: ContryController = new ContryController();

  public route(app: Application) {

    // -----    GET    -----
    app.get('/api/countries', (req: Request, res: Response) => {
      this.country_controller.get_all_countries(req, res);
    });

    // -----    GET BY ID    -----
    app.get('/api/countries/:countryId', (req: Request, res: Response) => {
      this.country_controller.get_country_by_id(req, res);
    });

    // -----    POST    -----
    app.post('/api/countries', (req: Request, res: Response) => {
      this.country_controller.create_country(req, res);
    });


  }

}
