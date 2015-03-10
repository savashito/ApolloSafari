var net = require('net');

// execute c++ program, 
// send data to sockets
// c++ prints things recevided


// execute c++ program, 
// var spawn = require('child_process').spawn;
// cv = spawn('./server');

console.log('Server runugn');

/*
// connect to prgam, the program is a server
cv.stdout.on('data',function(data){
	console.log('Data '+data+'\n');
	


})
*/

var client = net.connect({port: 22000},
	    function() { //'connect' listener
		  console.log('connected to server!');
		  //client.write('world!\r\n');
		  // send data trhou sockets
		  // client.write('Miauuuu!\r\n');
		});
/*
client.on('end', function() {
  console.log('disconnected from server');
});
*/
// cv.stdout.write("Te quiero matar!!");



/*
var client = net.connect({port: 22000},
    function() { //'connect' listener
	  console.log('connected to server!');
	  client.write('world!\r\n');
	});



client.on('data', function(data) {
  console.log(data.toString());
//  client.end();
});

client.on('end', function() {
  console.log('disconnected from server');
});
*/

