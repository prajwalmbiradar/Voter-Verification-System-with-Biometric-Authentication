//headers
const https = require('node:https');
const fs = require("fs");
const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');
const socketIo = require('socket.io');
//const http = require('http')
var lock = true
const express = require('express');
const app = express();
/*var server = app.listen(3100, '0.0.0.0', function () {
  console.log("server started");
}); */
const options = {
  key: fs.readFileSync("key.pem"),
  cert: fs.readFileSync("cert.pem")
};

const server = https.createServer(options, app).listen(3100, '0.0.0.0', () => {
  console.log("HTTPS server started on port 3100");
});
app.use(express.json()); // <-- this parses JSON body correctly

const io = socketIo(server);
const bodyParser = require('body-parser');
//const fs = require("fs");
const urlencodedParser = bodyParser.urlencoded({ extended: true });
const url = require('url');
const { error } = require('node:console');
const { json } = require('body-parser');
app.use("", express.static(__dirname + "/serverfolder"));

//firebase app  
//********************************************************** */

const admin = require("firebase-admin");

// Load your service account key
const serviceAccount = require("./votingdata-2481-firebase-adminsdk-ciuia-9ba970fc6b.json");

// Initialize Firebase
admin.initializeApp({
  credential: admin.credential.cert(serviceAccount),
  databaseURL: "https://votingdata-2481-default-rtdb.asia-southeast1.firebasedatabase.app"
});

const db = admin.database();
const votesRef = db.ref("votes");

async function updateVotes(m, w) {
  try {
    await votesRef.transaction((currentData) => {
      const data = currentData || { menvotes: 0, womenvotes: 0, totalvotes: 0 };

      return {
        menvotes: data.menvotes + m,
        womenvotes: data.womenvotes + w,
        totalvotes: data.totalvotes + m + w,
      };
    });

    console.log(`✅ Votes updated: men +${m}, women +${w}`);
  } catch (error) {
    console.error("❌ Error updating votes:", error);
  }
}


//updateVotes(1,0);
//updateVotes(0,1);

//******************************************************* */
//serial port things

var port = new SerialPort({
  path: 'COM11',
  baudRate: 9600,
  dataBits: 8,
  parity: 'none',
  stopBits: 1,
  flowControl: false
});

let parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }));
port.on("open", () => {
  console.log('serial port open');
});
parser.on('data', data => {
  console.log(data);
  if(data.includes('x77yyert')){
  io.emit("pressballot", "press the button");
  }
  if(data.includes('countvote')){
    if(data.includes('M')){
      updateVotes(1,0);
      console.log("updated m");
      
    }
    if(data.includes('W')){
      updateVotes(0,1);
      console.log("updated m");
    }
    }
  if(data.includes('scanbarcode')){
    lock = false;
    }
  
  });

io.on("connection", (socket) => {
  
  console.log('client connected');
  socket.on('voted',(ard)=>{
    console.log(ard);
    socket.broadcast.emit('cclear' , 'clear to give vote')
    port.write('yes voted');
    console.log("written to vote");
    
  })
  socket.on('ballotg',(ard)=>{
    console.log(ard);
    socket.broadcast.emit('bclear' , ' allowed to vote')
  })

  
});

app.get("/cu", (req, res) => {
  console.log("request incoming");
  res.sendFile(__dirname + "/serverfolder/" + "control.html");
});
app.get("/bu", (req, res) => {
    console.log("request incoming");
    res.sendFile(__dirname + "/serverfolder/" + "ballot.html");
  });
app.get("/scan", (req, res) => {
    console.log("request incoming");
    res.sendFile(__dirname + "/serverfolder/" + "scanner.html");
});
app.post("/barcode", (req, res) => {
  console.log("request incoming");
  //console.log(req.body.code);
  var nu = req.body.code
  console.log(nu);
  console.log(lock);
  
  if(lock == false){
    port.write(nu);
    console.log("written to port");
    
  }
  lock = true
  
});
  //***************************************** */
  app.get("/main", (req, res) => {
    console.log("request incoming");
    res.sendFile(__dirname + "/serverfolder/" + "main.html");
  });
  //***************************************** */
  