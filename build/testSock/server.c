/*Required Headers*/
 
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
 

 // thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
 

 /*
void foo() 
{
  // do stuff...
}

void bar(int x)
{
  // do stuff...
}
);
int main() 
{
  //std::thread first (foo);     // spawn new thread that calls foo()
  std::thread second (bar,accept,listen_fd, (struct sockaddr*) NULL, NULL);  // spawn new thread that calls bar(0)

  std::cout << "main, foo and bar now execute concurrently...\n";

  // synchronize threads:
  first.join();                // pauses until first finishes
  second.join();               // pauses until second finishes

  std::cout << "foo and bar completed.\n";

  return 0;
}
*/


int main()
{

   // printf("Running server\n");
   // fflush(stdout);

    
    char str[100];
    int listen_fd, comm_fd;
 
    struct sockaddr_in servaddr;
 
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
 
    bzero( &servaddr, sizeof(servaddr));
 
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(22000);
 
    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
 
    listen(listen_fd, 10);

 
    printf("Running server\n");
    // fflush(stdout);
    // lisen for connections
    // blocks untils someone conects
    comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
    fflush(stdout);
     printf("Acepto %d server\n",comm_fd);
     fflush(stdout);
     shutdown(comm_fd,0);
    // std::thread second (accept,listen_fd, (struct sockaddr*) NULL, NULL);  // spawn new thread that calls bar(0)

    // printf("Running server\n");
    // fflush(stdout);
    // while(1){

    // }

   /*
    while(1)
    {
 
        bzero( str, 100);
        // 
        read(comm_fd,str,100);
 
        printf("Echoing back - %s",str);
 
     //   write(comm_fd, str, strlen(str)+1);
 
    }
    */
 //   write(comm_fd, "str", strlen("str")+1);


}