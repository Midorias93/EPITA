const WebSocket = require('ws');

function startServer() {
    const wss = new WebSocket.Server({ port: 8080 });
    let clientID = 0;
    const clients = {};
    const ws_clients = {};

    console.log('Websocket server is running on port 8080.');

    wss.on('connection', (ws, request) => {
        clientID++;
        const userName = new URL(request.url, 'http://localhost:8080').searchParams.get('username');
        if (Object.values(clients).includes(userName)) {
            ws.close(1008, `Username: "${userName}" is already taken`);
            console.log(`[${clientID}] ${userName}: trying to establish connection`);
            console.log(`[${clientID}] Disconnected: [1008] Username: \"${userName}\" is already taken`)
            return;
        }

        wss.clients.forEach((client) => { 
            if (client.readyState === WebSocket.OPEN && client !== ws) {
                client.send(`${userName} connected`)
            }
        });

        clients[clientID] = userName;
        ws_clients[clientID] = ws;

        ws.send(`Welcome ${userName}`);

        const totalPlayers = Object.keys(clients).length;

        const message = totalPlayers === 1 ? `${userName}, you are the only player connected` :
            `${totalPlayers} players are connected`;
        ws.send(message);

        if (totalPlayers < 4) {
            wss.clients.forEach(client => {
                if (client.readyState === WebSocket.OPEN) {
                    client.send(`Waiting for ${4 - totalPlayers} other players to start the game`)
                }
        });
        }

        if (totalPlayers === 4) {
            Object.keys(ws_clients).forEach(id => {
                    if (ws_clients[id].readyState === WebSocket.OPEN) {
                        ws_clients[id].send(`Match will start soon, disconnecting ${clients[id]} from the lobby`);
                        ws_clients[id].close(1000, 'Match is starting');
                    }
            });
        }



        ws.on('close', (code, reason) => {

            let id = -1;
            let keys = Object.keys(ws_clients);
            for (key of keys)
            {
                if (ws_clients[key] === ws) {
                    id = key;
                }
            }


            console.log(`[${id}] Disconnected: [${code}] ${reason}`);
            delete clients[id];
            delete ws_clients[id];

            wss.clients.forEach(client => {
                if (client.readyState === WebSocket.OPEN) {
                    client.send(`${userName} disconnected`);
                }
            });
        });

        ws.on('message', (message) => {

            let id = -1;
            let keys = Object.keys(ws_clients);
            for (key of keys)
            {
                if (ws_clients[key] === ws) {
                    id = key;
                }
            }
            
            console.log(`[${id}] ${message}`);
        });

        ws.on('error', (error) => {
            console.error(`WebSocket error: ${error}`);
        });
    });

    return wss;
}

module.exports = { startServer };
