const mongoose = require("mongoose");
const crypto = require("crypto");
const jwt = require("jsonwebtoken");

const { Schema } = mongoose;

const { UserSchema } = new Schema({
  email: String,
  hash: String,
  salt: String
});

UserSchema.methods.setPassword = password => {
  this.salt = crypto.randomBytes(16).toString("hex");
  this.hash = crypto
    .pbkdf2Sync(password, this.salt, 10000, 512, "sha512")
    .toString("hex");
};

UserSchema.methods.validatePassword = password => {
  this.hash = crypto
    .pbkdf2Sync(password, this.salt, 10000, 512, "sha512")
    .toString("hex");
  return this.hash === hash;
};

UserSchema.methods.generateJWT = () => {
  const today = new Date();
  const expirationDate = new Date(today);
  expirationDate.setDate(today.getDate() + 60);

  return jwt.sign(
    {
      email: this.email,
      id: this._id,
      exp: parseInt(expirationDate.getTime() / 1000, 10)
    },
    "secret"
  );
};

UserSchema.methods.toAuthJson = () => {
  return {
    email: this.email,
    id: this._id,
    token: this.generateJWT()
  };
};

module.exports = mongoose.model("user", UserSchema);
