const WebSocket = require('ws');

function addClient(userName) {
    const ws = new WebSocket(`ws://localhost:8080?username=${userName}`);

    ws.on('open', () => {
        ws.send(`${userName}: trying to establish connection`);
    });

    ws.on('message', (message) => {
        console.log(`<server to ${userName}>: ${message}`);
    });

    ws.on('close', (code, reason) => {
        console.log(`<server to ${userName}>: Connection has been closed: [${code}] ${reason}`);
    });

    ws.on('error', (error) => {
        console.error(`WebSocket error: ${error}`);
    });

    return ws;
}

module.exports = { addClient };