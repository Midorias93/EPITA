let fs = require('fs');

function readUsersFromJSONFile(JSON_filename) {
  /*
   ** Return the list of users stored in the JSON file
   ** JSON_filename: path to the JSON file
   */
  const content = fs.readFileSync(JSON_filename, (err) => {
    if (err) {
      console.error(err);
      return;
    }
  });
  return JSON.parse(content).users;
}

function writeUsersToJSONFile(JSON_filename, users) {
  /*
   ** Overwrite the given JSON_filename with the given
   ** list of users.
   ** JSON_filename: path to the JSON file
   ** users : list of users objects
   */
  const usersJSON = JSON.stringify({ users: users });
  fs.writeFileSync(JSON_filename, usersJSON, (err) => {
    if (err) {
      console.error(err);
      return;
    }
  });
}


function epiTinderWebServer(host, port, filename) {
  let express = require('express');
  let app = express();
  app.use(express.json());
  let server = app.listen(port, host, () => {
    console.log(`Server running at http://${host}:${port}/`);
  });


  app.get('/', (req, res) => {
    res.status(200).json({ message: "Hello World!" });
  });

  app.get('/users', (req, res) => {
    const users = readUsersFromJSONFile(filename);
    res.status(200).json(users);
  });

  app.post('/users', (req, res) => {
    let users = readUsersFromJSONFile(filename);
    max = 0;
    for (x of users) {
      if (x.id > max) {
        max = x.id;
      }

    }
    let id = max === 0 ? 0 : max + 1;
    const newUser = {
      id: id,
      name: req.body.name,
      description: req.body.description,
      age: req.body.age,

    };
    users.push(newUser);
    writeUsersToJSONFile(filename, users);
    res.status(201).json(newUser);
  });

  app.get('/users/:id', (req, res) => {
    const users = readUsersFromJSONFile(filename);
    let user = null;
    for (x of users) {
      if (x.id == req.params.id) {
        user = x;
      }
    }
    if (user) {
      res.status(200).json(user);
    } else {
      res.status(404).json({ message: `No user with id: ${req.params.id} found` });
    }
  });

  app.put('/users/:id', (req, res) => {
    let users = readUsersFromJSONFile(filename);
    let index = -1;
    for (let i = 0; i < users.length; i++) {
      if (users[i].id == req.params.id) {
        index = i;
      }
    }
    if (index === -1) {
      res.status(404).json({ message: `No user with id: ${req.params.id} found` });
    } else {
      ide = Number(req.params.id);
      users[index] = {
        id: ide,
        name : req.body.name,
        description : req.body.description,
        age : req.body.age,
      };
      writeUsersToJSONFile(filename, users);
      res.status(201).json(users[index]);
    }
  });

  app.delete('/users/:id', (req, res) => {
    let users = readUsersFromJSONFile(filename);
    let index = -1;
    for (let i = 0; i < users.length; i++) {
      if (users[i].id == req.params.id) {
        index = i;
      }
    }
    if (index === -1) {
      res.status(404).json({ message: `No user with id: ${req.params.id} found` });
    } else {
      const [deletedUser] = users.splice(index, 1);
      writeUsersToJSONFile(filename, users);
      res.status(200).json(deletedUser);
    }
  });

  app.use((req, res) => {
    res.status(404).json({message: "Not found"})
  });
  return server;  
}

module.exports = { epiTinderWebServer };