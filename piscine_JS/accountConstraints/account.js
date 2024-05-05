"use strict";

const {
  InvalidUsernameError,
  InvalidPasswordError,
  InvalidYearOfBirthError,
} = require("./accountError");

class Account {

  constructor(username, password, yearOfBirth) {
    if (typeof username !== "string") {
      throw new InvalidUsernameError("username is not a string");
     }

    else if (username.length == 0) {
      throw new InvalidUsernameError("username size is = 0");
    }

    else if (!username.match("^[a-zA-Z0-9_-]*$")) {
      throw new InvalidUsernameError("username format is invalid");
    }


    else if (password.length < 8 || password.length > 100) {
      throw new InvalidPasswordError("pasword size is invalid");
    }

    else if (typeof password !== "string") {
      throw new InvalidPasswordError("pasword is not a string");
    }

    else if (!password.match("^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z]).+$")) {
      throw new InvalidPasswordError("pasword format is invalid");
    }


    else if(typeof yearOfBirth !== "number") {
      throw new InvalidYearOfBirthError("year of birth is not a number");
    }

    else if (yearOfBirth < 1800 || yearOfBirth > 2024) {
      throw new InvalidYearOfBirthError("year of birth is not possible");
    }

    else {
      this.username = username;
      this.password = password;
      this.yearOfBirth = yearOfBirth;
    }
  }

}

module.exports = {
  Account,
};
