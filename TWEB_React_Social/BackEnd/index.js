// if for automatic deployement purpose.
if (process.env.NODE_MODE !== "production") {
  /* eslint-disable global-require */
  require("dotenv").config({ path: `${__dirname}/../.env` });
  /* eslint-enable global-require */
}

// Bring in our dependencies
const app = require("express")();
// use cors for front end request compatibility
const cors = require("cors");

const port = process.env.PORT || 3000;

/* *******************************************************
 * Routes and models
 ******************************************************* */
require("./src/models/Users");
require("./config/passport");
const routes = require("./src/routes/routes");
const users = require("./src/routes/users");

/* *******************************************************
 * Default route
 ******************************************************* */
app.get("/", routes);

app.get("/login", users);

/* ******************************************************
 * Error Handler
 ******************************************************* */
// Difficult to test
/* istanbul ignore next */
app.use((err, req, res) => {
  res.status(err.status || 500);

  res.json({
    errors: {
      message: err.message,
      error: err
    }
  });
});

// Turn on that server!
app.listen(port, () => {
  console.log(`Listening on http://localhost:${port}`);
});
