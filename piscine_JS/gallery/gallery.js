const fs = require('fs');
const path = require('path');

function extract(directoryPath) {

    if (!fs.existsSync(directoryPath)) {
        throw new Error('The directory does not exist');
    }

    const files = fs.readdirSync(directoryPath);
    let emails = [];

    const emailRegex = /[a-z0-9._+%-]+@[a-z0-9.-]+\.[a-z]{2,}/g;

    for (let file of files) {
        let filePath = path.join(directoryPath, file);
        const  fileContent = fs.readFileSync(filePath, 'utf8');
        const matchedEmails = fileContent.match(emailRegex);

        if (matchedEmails) {
            for (email of matchedEmails)
            {
                emails.push(email);
            }
        }
    }

    return emails;
}

module.exports = { extract }
