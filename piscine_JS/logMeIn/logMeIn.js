const express = require('express');
const jwt = require('jsonwebtoken');


function logMeIn(host, port) {
  let app = express();
  app.use(express.json());
  let server = app.listen(port, host, () => {
    console.log(`Server running at http://${host}:${port}/`);
  });

  const JWT_SECRET_KEY = process.env.JWT_SECRET_KEY;

  app.get('/', (req, res) => {
    res.status(200).json({message: "Hello World!"});
  });

  app.post('/login', (req, res) => {
    let {username, password} = req.body;
    if (username === "xavier.login" && password === "1234"){ // faire une check sur le mots de passe de l'utilisateur
        let token = jwt.sign(req.body, JWT_SECRET_KEY);
        res.status(200).json({jwt: token})
    }
    else
    {
        res.status(401).json({error: "Invalid username or password"})
    }

  });

  app.get('/secret', (req, res) => {
    try{
        let token = req.headers.authorization.split(' ')[1];
        jwt.verify(token, JWT_SECRET_KEY);
        res.status(200).json({message: "Access granted"})
    }
    catch {
        res.status(401).json({error: "Unauthorized"})
    }

  });

  return server;


}

module.exports = { logMeIn };