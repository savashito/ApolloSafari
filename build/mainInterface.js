// Develop by : Rodrigo Savage
// Hackaton 2015 March 7
// code that generates ip camara for drone
var net = require('net');
var arDrone = require('ar-drone');
var Myo = require('myo');
var myMyo = Myo.create();
var PaVEParser = require('ar-drone/lib/video/PaVEParser');
var parser = new PaVEParser();
var client = arDrone.createClient();
var parrot = require('./parrot.js');
var video = client.getVideoStream();

myMyo.on('connected', function () {
    myMyo.setLockingPolicy('none');
});
myMyo.on('fist', function(edge){
	parrot.liftoff(client);
});
myMyo.on('wave_out', function(edge){
	parrot.right(client);
});
myMyo.on('wave_in', function(edge){
	parrot.left(client);
});
myMyo.on('fingers_spread', function(edge){
    parrot.lander(client);
});
myMyo.on('rest', function(edge){
	parrot.stop(client);
});


video.pipe(parser);
var server = net.createServer(

	function(c) { //'connection' listener
	  console.log('client connected');
	  c.setNoDelay(true);
	  c.on('end', function() {
	    console.log('client disconnected');
	  });

	  
		 parser
		  .on('data', function(data) {
		    // requester.send(data.payload);
		    // c.flush();
		    c.write(data.payload)

		  //  console.log(data.payload);
		 })
		  .on('end', function() {
		   // output.end();
		 });
		
	  

	  // c.write('hello\r\n');
	  // c.pipe(c);
	}
);



server.listen(8124, function() { //'listening' listener
  // console.log('server bound');


});
/////////////

// var net = require('net');
// var arDrone = require('ar-drone');
// var PaVEParser = require('ar-drone/lib/video/PaVEParser');
// var parser = new PaVEParser();
// var video = arDrone.createClient().getVideoStream();


// video.pipe(parser);
// var server = net.createServer(

// 	function(c) { //'connection' listener
// 	  console.log('client connected');
// 	  c.setNoDelay(true);
// 	  c.on('end', function() {
// 	    console.log('client disconnected');
// 	  });

	  
// 		 parser
// 		  .on('data', function(data) {
// 		    // requester.send(data.payload);
// 		    // c.flush();
// 		    c.write(data.payload)

// 		    console.log(data.payload);
// 		 })
// 		  .on('end', function() {
// 		   // output.end();
// 		 });
		
	  

// 	  // c.write('hello\r\n');
// 	  // c.pipe(c);
// 	}
// );



// server.listen(8124, function() { //'listening' listener
//   // console.log('server bound');


// });





///////


/*
var zmq = require('zmq');
var arDrone = require('ar-drone');
var PaVEParser = require('ar-drone/lib/video/PaVEParser');
var spawn = require('child_process').spawn;


// cv = spawn('./app');
var requester = zmq.socket('req');
requester.connect("tcp://localhost:5555");

var parser = new PaVEParser();
var video = arDrone.createClient().getVideoStream();


video.on('error',console.log);

parser
  .on('data', function(data) {
    requester.send(data.payload);
    console.log(data.payload);
  })
  .on('end', function() {
   // output.end();
  });
video.pipe(parser);

*/
/*
while(1){
	data = "monsdx";
	console.log(data);
	requester.send(data);
}*/

/*
video.on('data', function(data){

	// cv.stdout.write(data);
	console.log(data);
	requester.send(data);
});
*/


// cv.stdout.write('Miauuu\n');
// cv.stdout.on('data',function(data){
// 	console.log(data);
// })


/*
    ls    = spawn('ls', ['-lh', '/usr']); 

ls.stdout.on('data', function (data) {
  console.log('stdout: ' + data);
});

*/
// var crypto = require('crypto');
// var fs = require('fs');
// var wstream = fs.createWriteStream('myBinaryFile');
// // creates random Buffer of 100 bytes
// var buffer = crypto.randomBytes(100);
// wstream.write(buffer);
// wstream.end();

