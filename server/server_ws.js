const myPort = 3000;

const WebSocket = require('ws');
const WebSocketServer = new WebSocket.Server( { port: myPort } );
console.clear();

if(WebSocketServer) {
    console.log(`Listening @ ws://localhost:${myPort}`);
}

WebSocketServer.on("connection", (client) => {
    console.log("New Client Connected");

    client.on("message", (msg) => {
        console.log(`Client Says: ${msg}`);
        client.send(`Server Says: ${msg}`);
    });


});
