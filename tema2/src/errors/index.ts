import { Response } from 'express';
import { response_status_codes } from './model'

export function requestResponse(http_status_code: response_status_codes, message: any, res: Response) {
  res.status(http_status_code).json(message);
}
