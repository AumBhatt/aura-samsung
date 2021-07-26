const myPort = 8001;


const WebSocket = require('ws');
const WebSocketServer = new WebSocket.Server( { port: myPort } );
console.clear();

if(WebSocketServer) {
    console.log(`Listening @ ws://localhost:${myPort}`);
}

WebSocketServer.on("connection", (client) => {
    client.send(`{"event":"ms.channel.connect"}`);
    console.log("Client Connected");
    client.on("message", (msg) => {
        console.log(`Client Says: ${msg}`);
    });

    client.on("close", (client) => {
        console.log("Client Disconnected");
    });


});

/* const http = require('http');
const server = http.createServer();

server.on('upgrade', function upgrade(request, socket, head) {
    const pathname = request.url;
    //console.log("ClientPath: " + pathname);
    WebSocketServer.handleUpgrade(request, socket, head, function done(WebSocket) {
      WebSocketServer.emit('connection', WebSocket, request);
    });
  });
//server.listen(myPort); */