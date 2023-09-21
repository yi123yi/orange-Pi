#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include "inputcommander.h"
int socketGetCommand(struct InputCommander *Socket)
{   int c_fd;
    int n_read = 0;

    struct sockaddr_in c_addr;
    memset(&c_addr,0,sizeof( struct sockaddr_in));
    
    int clen = sizeof(struct sockaddr_in);

    c_fd = accept(Socket->sfd,(struct sockaddr *)&c_addr,&clen); 

    n_read =  read(c_fd,Socket->command,sizeof(Socket->command));
    if(n_read == -1)
    {
        perror("read");
    }else if(n_read > 0 )
    {
        printf(" \nget:%d\n",n_read);
    }else{
        printf("client quit\n");
        
    }
  

  return n_read;
}

int socketInit(struct InputCommander *Socket,char *ipAdress,char *port)
{  
   
    int s_fd;
    struct sockaddr_in s_addr;
;
    memset(&s_addr,0,sizeof(struct sockaddr_in));
   


//    socket
   s_fd = socket(AF_INET,SOCK_STREAM,0);
   if(s_fd == -1)
   {
    perror("socket");
    exit(-1);
   }
  

   s_addr.sin_family = AF_INET;
   s_addr.sin_port = htons(atoi(Socket->port));
   inet_aton(Socket->ipAddress,&s_addr.sin_addr);
   
//    bind
  bind(s_fd,(struct sockaddr *)*s_addr,sizeof(struct sockeaddr_in));

// listen
  listen(s_fd,10);

   Socket->sfd = s_fd

 return s_fd;

}


struct InputCommander socketContrl = 
{
    /* data */

    .commandName = "socketServer",
    .command = {'\0'},
    .port = "8088",
    .ipAddress = "192.168.0.123",
    .Init = socketInit,
    .getCommand = socketGetCommand,
    .log = {'\0'},
    .next = NULL
     
};


struct Devices* addsocketContrlToInputCommandLink(struct InputCommander *phead)
{
     if(phead == NULL){
        return &socketContrl;
    }
    else{
        socketContrl.next = phead;
        phead = &socketContrl;
    }
}