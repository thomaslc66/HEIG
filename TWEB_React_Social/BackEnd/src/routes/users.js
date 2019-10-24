const users = require("express").Router();

users.get("/login", (req, res) => {
  res.status(200).json({ message: "UnAuthorized!" });
});

module.exports = users;
