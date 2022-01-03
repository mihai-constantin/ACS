import mongoose, { Schema, Document } from 'mongoose';

export interface ITemperature extends Document {
  _id: string;
  value: number;
  timestamp: string;
  city_id: string;
}

const TemperatureSchema: Schema = new Schema({
  _id: {
    type: mongoose.Schema.Types.ObjectId,
    required: true,
    auto: true
  },
  value: {
    type: Number,
    required: true
  },
  timestamp: {
    type: String,
    required: false
  },
  city_id: {
    type: String,
    required: true
  }
});

TemperatureSchema.index( { "city_id": 1 , "timestamp": 1}, { unique: true } )

export default mongoose.model<ITemperature>('Temperature', TemperatureSchema);
