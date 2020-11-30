import { Application, Request, Response } from 'express';
import { TemperatureController } from '../controllers/temperatureController';

export class TemperatureRoutes {

  private temperature_controller: TemperatureController = new TemperatureController();

  public route(app: Application) {

    // -----    POST    -----
    app.post('/api/temperatures', (req: Request, res: Response) => {
      this.temperature_controller.create_temperature(req, res);
    });


  }

}