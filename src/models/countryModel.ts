import mongoose, { Schema, Document } from 'mongoose';

export interface ICountry extends Document {
  _id: string;
  name: string;
  latitude: number;
  longitude: number;
}

const ContrySchema: Schema = new Schema({
  _id: {
    type: mongoose.Schema.Types.ObjectId,
    required: true,
    auto: true
  },
  name: {
    type: String,
    required: true,
    unique : true,
    dropDups: true
  },
  latitude: {
    type: Number,
    required: true
  },
  longitude: {
    type: Number,
    required: true
  }
});

export default mongoose.model<ICountry>('Country', ContrySchema);
