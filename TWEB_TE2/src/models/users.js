// ./src/models/users.js

const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const schema = new Schema(
  {
    login: String,
    email: String,
    password: String
  },
  { versionKey: false }
);

module.exports = mongoose.model('user', schema);
