// ./src/routes/auth.js

const express = require('express');
const jwt = require('jsonwebtoken');
const passport = require('passport');
const passportLocal = require('passport-local');
const passportJWT = require('passport-jwt');
const { jwtOptions } = require('../../config');
const userDataBase = require('../dataBase/userDatabase');
const bcrypt = require('bcryptjs');

const router = express.Router();

const LocalStrategy = passportLocal.Strategy;
const JwtStrategy = passportJWT.Strategy;
const extractJwt = passportJWT.ExtractJwt;

/**
 * JWT Passport strategy to authenticate user
 * and check access token
 */
passport.use(
  'jwt-strategy',
  new JwtStrategy(
    {
      secretOrKey: jwtOptions.secret,
      jwtFromRequest: extractJwt.fromAuthHeaderAsBearerToken()
    },
    (jwtPayload, done) => {
      const { userId } = jwtPayload;
      //query the dataBase
      userDataBase.getUserById(userId).then((user, err) => {
        if (err) {
          return done(null, false);
        }
        return done(null, user.toJSON());
      });
    }
  )
);

/**
 * Local Passport strategy to login user and get bearer token
 */
passport.use(
  'local-strategy',
  new LocalStrategy(
    { usernameField: 'login', passwordField: 'password' },
    (username, password, done) => {
      // DataBase query
      userDataBase.getUserByLogin(username).then((user, error) => {
        if (error) {
          return done(error, false, { message: ' Error during request ' });
        }
        if (!user) {
          return done(null, false, { message: 'Incorrect username.' });
        }
        const passwordHash = user.password;
        // TODO if compareSync === true
        if (bcrypt.compareSync(password, passwordHash)) {
          return done(null, user.toJSON());
        } else {
          return done(null, false, { message: 'Incorrect password.' });
        }
      });
    }
  )
);

/**
 * For user login purpose
 */
router.post(
  '/login',
  passport.authenticate('local-strategy', { session: false }),
  (req, res) => {
    const { password, ...user } = req.user;
    const token = jwt.sign({ userId: user.id }, jwtOptions.secret);
    res.send({ user, token });
  }
);

/**
 * For user registration purpose
 */
router.post('/register', (req, res) => {
  const user = req.body;
  // send the user to the DB
  // the password hash is executed before insertion in DB
  userDataBase.insertUser(user).then(result => {
    res.send(result);
  });
});

// Do not forget
module.exports = router;
