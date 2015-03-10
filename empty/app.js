var Myo = require('myo');
var myMyo = Myo.create();
var parrot = require('./parrot.js');

myMyo.on('connected', function () {
    myMyo.setLockingPolicy('none');
});
myMyo.on('fist', function(edge){
	parrot.liftoff();
});
myMyo.on('wave_out', function(edge){
	parrot.right();
});
myMyo.on('wave_in', function(edge){
	parrot.left();
});
myMyo.on('fingers_spread', function(edge){
    parrot.lander();
});
myMyo.on('rest', function(edge){
	parrot.stop();
});
