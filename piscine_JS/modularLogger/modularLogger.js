function loggerFactory() {
    const logs = [];
    const logLevels = ['ERROR','WARN', 'INFO', 'DEBUG'];

    function addLog(date, nameLogLevel, message) {
        if (!logLevels.includes(nameLogLevel)) {
            console.log(`${nameLogLevel} is an invalid log level. Please use one of the following: DEBUG, INFO, WARN, ERROR.`);
            return;
        }
        const timeString = date.toTimeString().split(' ')[0];
        const formattedMessage = `[${timeString}][${nameLogLevel}] - ${message}`;
        logs.push({ level: logLevels.indexOf(nameLogLevel), message: formattedMessage });
    }

    function printLogs(level) {
        if (typeof level !== 'number' || isNaN(level) || level < 0) {
            console.log('Bad argument.');
            return;
        }
        logs.forEach(log => {
            if (log.level <= level || level >= logLevels.length) {
                console.log(log.message);
            }
        });
    }

    return function (level) {
        if (level === undefined) {
            return addLog;
        } else {
            return printLogs(level);
        }
    };
}

module.exports = { loggerFactory }