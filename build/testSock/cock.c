//  Hello World client
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main (void)
{
    printf ("Connecting to hello world server…\n");
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    // conect to server
    zmq_connect (requester, "tcp://localhost:5555");

    int request_nbr;
    
    for (request_nbr = 0; request_nbr != 1000; request_nbr++) {
        char buffer [10];
        printf ("Sending Hello %d…\n", request_nbr);
        zmq_send (requester, "TeQuiero", 10, 0);
        zmq_recv (requester, buffer, 10, 0);
       // printf ("Received World %d\n", request_nbr);
    }
    zmq_send (requester, "Cock!", 5, 0);
    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}