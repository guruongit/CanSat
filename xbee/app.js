const { SerialPort } = require('serialport')
const { ReadlineParser } = require('@serialport/parser-readline')
const port = new SerialPort({ path: 'COM8', baudRate: 14400 })


//Server
var http = require('http');
var fs = require('fs');
var index = fs.readFileSync('index.html');
const { Server } = require("socket.io");


const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }))

var app = http.createServer(function(req, res){
    res.writeHead(200,{'Content-Type':'text/html'});
    res.end(index);   
});

var io = new Server();
io.listen(app);

io.on('connection', function(data){
    
    console.log('Node.js is listening!');
});


parser.on('data', function(data){
    console.log(data);
    io.emit('data',data);
    
});

app.listen(3000);