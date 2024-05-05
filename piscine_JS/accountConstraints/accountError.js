class InvalidUsernameError extends Error {
    constructor(errorMessage) {
        super("Invalid username : " + errorMessage);
        this.name = "InvalidUsernameError";
    }
}

class InvalidPasswordError extends Error {
    constructor(errorMessage) {
        super("Invalid password : " + errorMessage);
        this.name = "InvalidPasswordError";
    }

}

class InvalidYearOfBirthError extends Error {
    constructor(errorMessage) {
        super("Invalid year of birth : " + errorMessage);
        this.name = "InvalidYearOfBirthError";
    }
}

module.exports = {
    InvalidUsernameError,
    InvalidPasswordError,
    InvalidYearOfBirthError,
};