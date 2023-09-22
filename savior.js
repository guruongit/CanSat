const SerialPort = require("serialport");
const Readline = require("@serialport/parser-readline");

const port = new SerialPort("COM7",{
    bautRate: 9600,

})

const parser = new Readline();
port.pipe(parser);

parser.on("data",(line) => console.log(line));

port.write("ROBOT POWER ON");

// 

var serialport = require("serialport");
var SerailPort = serialport.SerialPort;
var portName = process.argv[2];

var myPort = SerailPort(portName,{
    bautRate:9600, 
    parser:serialport.parsers.readline("\r\n")
})

myPort.on('open',onOpen);
myPort.on('data', onData);

function onOPen(){
    console.log("Open Connection");
}

function onData(data){
    console.log("on Data " + data);
}