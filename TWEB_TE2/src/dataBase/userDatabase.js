const User = require('../models/users');
const { DataBase } = require('./database');
const bcrypt = require('bcryptjs');

class UserDatabase extends DataBase {
  constructor() {
    super();
    this.getUserById = this.getUserById.bind(this);
    this.getUserByLogin = this.getUserByLogin.bind(this);
  }

  /**
   *
   */
  insertUser(user, done) {
    //crypt password
    const salt = bcrypt.genSaltSync(10);
    const hash = bcrypt.hashSync(user.password, salt);

    // TODO if you change the schema don't forget to delete the database
    const dbUser = new User({
      id: user.id,
      login: user.login,
      email: user.email,
      password: hash
    });

    return this.saveInDb(dbUser, done);
  }

  /**
   *
   */
  getUserById(id) {
    return User.findOne({
      id
    });
  }

  getUserByLogin(login) {
    return User.findOne({
      login
    });
  }

  isInDbAndReturnUser(username, password) {
    console.log(username);
    console.log(password);
  }
}

const userDatabase = new UserDatabase();
module.exports = userDatabase;
