import mongoose, { Schema, Document } from 'mongoose';

export interface ICity extends Document {
  _id: string;
  name: string;
  latitude: number;
  longitude: number;
  country_id: string;
}

const CitySchema: Schema = new Schema({
  _id: {
    type: mongoose.Schema.Types.ObjectId,
    required: true,
    auto: true
  },
  name: {
    type: String,
    required: true,
  },
  latitude: {
    type: Number,
    required: true
  },
  longitude: {
    type: Number,
    required: true
  },
  country_id: {
    type: String,
    required: true
  }
});

CitySchema.index( { "country_id": 1 , "name": 1}, { unique: true } )

export default mongoose.model<ICity>('City', CitySchema);
