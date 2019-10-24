// ./src/routes/api.js

const express = require('express');
const passport = require('passport');
const router = express.Router();

router.get(
  '/private',
  passport.authenticate('jwt-strategy', { session: false }),
  (req, res) => {
    res.send({ message: 'Hey this is a private message' });
  }
);

router.get('/public', (req, res) => {
  res.send({ message: 'Hey this is a public message' });
});

router.get(
  '/me',
  passport.authenticate('jwt-strategy', { session: false }),
  (req, res) => {
    const { password, ...resultuser } = req.user;

    res.send({ user: resultuser });
  }
);

router.get('/', (req, res) => {
  res.send({ message: 'hello' });
});

// Do not forget
module.exports = router;
