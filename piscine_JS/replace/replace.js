function replace(input) {
    const regex = /(\d{2})\/(\d{2})\/(\d{4})/g;
    return input.replace(regex, (match, month, day, year) => `${year}-${month}-${day}`);
}

module.exports = { replace };