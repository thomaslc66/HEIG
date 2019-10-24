if (process.env.NODE_MODE !== 'production') {
  require('dotenv').config({
    path: `${__dirname}/.env`
  });
}

const express = require('express');
const cors = require('cors');
const passport = require('passport');
const api = require('./src/routes/api');
const auth = require('./src/routes/auth');
const { db } = require('./src/dataBase/database');

const app = express();
const { port } = require('./config');

app.use(express.json());
app.use(cors());

// Passport middleware
app.use(passport.initialize());
//app.use(cors());

app.use('/', api);
app.use('/auth', auth);

app.use((err, req, res, next) => {
  console.log(err);
  res.status(500).send('Upps something went wrong');
});

app.listen(port, () => {
  db.connect();
  console.log(`server start at http://localhost:${port}`);
});
