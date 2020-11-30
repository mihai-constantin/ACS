import { Application, Request, Response } from 'express';
import { TemperatureController } from '../controllers/temperatureController';

export class TemperatureRoutes {

  private temperature_controller: TemperatureController = new TemperatureController();

  public route(app: Application) {

    // -----    GET    -----
    app.get('/api/temperatures', (req: Request, res: Response) => {
      this.temperature_controller.get_all_temperatures(req, res);
    });

    // -----    GET BY ID    -----
    app.get('/api/temperatures/:temperatureId', (req: Request, res: Response) => {
      this.temperature_controller.get_temperature_by_id(req, res);
    });

    // -----    GET BY CITY    -----
    app.get('/api/temperatures/city/:cityId', (req: Request, res: Response) => {
      this.temperature_controller.get_temperatures_by_city(req, res);
    });

    // -----    GET BY COUNTRY    -----
    app.get('/api/temperatures/country/:countryId', (req: Request, res: Response) => {
      this.temperature_controller.get_temperatures_by_country(req, res);
    });

    // -----    POST    -----
    app.post('/api/temperatures', (req: Request, res: Response) => {
      this.temperature_controller.create_temperature(req, res);
    });

  }

}