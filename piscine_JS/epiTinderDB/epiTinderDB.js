const { Sequelize, DataTypes } = require('sequelize');

const USERNAME = process.env.USERNAME;
const PASSWORD = process.env.PASSWORD

const sequelize = new Sequelize('postgres', USERNAME, PASSWORD, {
  host: 'localhost',
  dialect: 'postgres',
  port: 5432,
  logging: false,
  define: {
    timestamps: false
  }
});

const User = sequelize.define('User', {
  name: DataTypes.STRING,
  age: DataTypes.INTEGER,
  description: DataTypes.STRING
}, {
  tableName: 'epitinder_users'
});

async function connectToDB() {
  try {
    await sequelize.authenticate();
    console.log('Connection has been established successfully.');
    return sequelize;
  } catch (error) {
    console.error('Unable to connect to the database:', error);
    return null;
  }
}

async function getAllUsers() {
  return await User.findAll({raw : true});
}

async function getUser(id) {
  return await User.findByPk(id, {raw : true});
}

async function addUser(newUser) {
  try {
    if (Object.keys(newUser).length === 3) {
      user = await User.create(newUser);
      return { id: user.id, name: user.name, age: user.age, description: user.description };
    }
    else 
    {
      return null;
    }
  } catch (error) {
    console.error('Error adding user:', error);
    return null;
  }
}


async function updateUser(user) {
  try {
    const existingUser = await User.findByPk(user.id);
    if (existingUser && Object.keys(user).length === 4) {
      user = await existingUser.update(user);
      return {id: user.id, name: user.name, age: user.age, description: user.description};
    }
    return null;
  } catch (error) {
    console.error('Error updating user:', error);
    return null;
  }
}

async function deleteUser(id) {
  const user = await User.findByPk(id);
  if (user) {
    await user.destroy();
    return { id: user.id, name: user.name, age: user.age, description: user.description};
  }
  return null;
}

async function getAllUsersName() {
  return await User.findAll({
    attributes: ['name'], raw: true
  });
}

async function getAllYoungAdults() {
  return await User.findAll({
    where: {
      age: {
        [Sequelize.Op.gte]: 18,
        [Sequelize.Op.lt]: 30
      }
    }
  , raw: true});
}

module.exports = {
  connectToDB,
  getAllUsers,
  getUser,
  addUser,
  updateUser,
  deleteUser,
  getAllUsersName,
  getAllYoungAdults
};