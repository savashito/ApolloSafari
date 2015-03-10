
//  Hello World server

#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

void* initZMQ(){
	 //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    // listen to requests
    int rc = zmq_bind (responder, "tcp://*:5555");
    assert (rc == 0);
    return responder;
}

void listenForData(void* responder,char*buffer,int n){
	zmq_recv (responder, buffer, n, 0);
	printf ("Received %s %d\n",buffer,i++);
    zmq_send (responder, "World", 5, 0);
}

int main (void)
{
    //  Socket to talk to clients
    /*
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:5555");
    assert (rc == 0);
    */
    void *responder = initZMQ();
    int i =0;
    while (1) {
    	char buffer [100];
    	listenForData(responder,buffer,100);

        /*
        zmq_recv (responder, buffer, 10, 0);
        printf ("Received %s %d\n",buffer,i++);
        // sleep (1);          //  Do some 'work'
        zmq_send (responder, "World", 5, 0);
        */
    }
    return 0;
}
/*
#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

void* initZMQ(){
	 //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    // listen to requests
    int rc = zmq_bind (responder, "tcp://*:5555");
    assert (rc == 0);
    return responder;
}

int main (void)
{
   
    while (1) {
        char buffer [10];
        void* responder = initZMQ();
        zmq_recv (responder, buffer, 10, 0);
        printf ("Received Hello %s\n",buffer);
        sleep (1);          //  Do some 'work'
      	zmq_send (responder, "World", 5, 0);
    }
    return 0;
}

*/