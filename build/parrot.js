var arDrone = require('ar-drone');
var client  = arDrone.createClient();

exports.liftoff = function(client) {
	client.takeoff();
	client
		.after(5000, function() {
			console.log('liftoff');
		  this.up(1);
		  console.log('liftoff done');
		})
	  .after(2000, function() {
	  console.log(' lift off stop init');
		this.stop();
		console.log('liftoff stop Done');
	  });
}
exports.lander = function(client){
	client.stop();
	client.land();
}
exports.forward = function(client){
	client.forward(0.5);
}
exports.backwards = function(client){
	client
	.after(0, function() {
	  this.back(0.5);
	})
	.after(2000, function() {
	  this.stop();
	});
}
exports.left = function(client){
		client.counterClockwise(0.5);
	

}
exports.right = function(client){
	client.clockwise(0.5);
}
exports.raise = function(client){
	client
	.after(0, function() {
	  this.up(0.5);
	})
	.after(2000, function() {
	  this.stop();
	});
}
exports.lower = function(client){
	client
	.after(0, function() {
	  this.down(0.5);
	})
	.after(2000, function() {
	  this.stop();
	});
}

exports.stop = function(client) {
	client.stop();
}