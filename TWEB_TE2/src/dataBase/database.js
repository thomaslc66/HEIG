// ./src/dataBase/database.js

const mongoose = require('mongoose');
mongoose.set('useFindAndModifiy', false);
mongoose.set('useCreateIndex', true);
const { dataBaseOptions } = require('../../config');

/**
 * Database
 */
class DataBase {
  constructor() {
    this.dbName = dataBaseOptions.dbName;
    this.dbUrl = dataBaseOptions.dbUrl;
    this.db = null;

    this.connect = this.connect.bind(this);
    this.close = this.close.bind(this);
    this.clear = this.clear.bind(this);
    this.saveInDb = this.saveInDb.bind(this);
  }

  /**
   * initialisation of the database
   */
  connect() {
    mongoose.connect(
      `${this.dbUrl}/${this.dbName}`,
      {
        useNewUrlParser: true
      }
    );

    this.db = mongoose.connection;

    this.db.once('close', () => {
      console.log('Disconnected from db');
    });

    this.db.on('error', () => {
      console.error.bind(console, 'Connection error: ');
      this.close();
    });

    this.db.once('open', () => {
      console.log('Connected to DB => OK');
    });
  }

  close() {
    return this.db.close();
  }

  clear() {
    return this.db.dropDatabase();
  }

  saveInDb(value) {
    return value.save();
  }
}

const db = new DataBase();

module.exports = {
  db,
  DataBase
};
