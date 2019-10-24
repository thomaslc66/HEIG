module.exports = {
  port: process.env.PORT,
  jwtOptions: {
    secret: process.env.JWT_SECRET
  },
  dataBaseOptions: {
    dbName: process.env.DB_NAME,
    dbUrl: process.env.DB_URL
  }
};
