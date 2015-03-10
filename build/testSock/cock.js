var zmq = require('zmq');

// socket to talk to server
console.log("Connecting to hello world server…");
var requester = zmq.socket('req');

var x = 0;

/*
requester.on("message", function(reply) {
  console.log("Received reply", x, ": [", reply.toString(), ']');
  x += 1;
  if (x === 10) {
    requester.close();
    process.exit(0);
  }
});
*/

requester.connect("tcp://localhost:5555");

for (var i = 0; i < 10; i++) {
  console.log("Sending request", i, '…');
  requester.send("Te quiero <3");
  // requester.recv()
}

process.on('SIGINT', function() {
  requester.close();
})