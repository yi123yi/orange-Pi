#include "inputcommander.h"
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <stdlib.h>


// BULETOOTH

int voiceGetCommand(struct InputCommander *voicer)
{   int nread = 0;

    read(voicer->fd,voicer->command,sizeof(voicer->command));

    if(nread == 0){
        printf("usart for voice read over time\n");
    }else{
        return nread;
    }
}

int voiceInit(struct InputCommander *voicer,char *ipAdress,char *port)
{  
    int fd;
    if((fd = serialOpen(voicer->deviceName,9600)) == -1)
    {
        exit(-1);
    }

    voicer ->fd = fd;
   return fd ;
}


struct InputCommander voiceContrl = 
{
    /* data */

    .commandName = "voice",
    .deviceName = "/dev/ttyAMA0",
    .command = {'\0'},
    .Init = voiceInit,
    .getCommand = voiceGetCommand,
    .log = {'\0'},
    .next = NULL
     
};


struct InputCommander* addvoiceContrlToInputCommandLink(struct InputCommander *phead)
{
     if(phead == NULL){
        return &voice;
    }
    else{
        voice.next = phead;
        phead = &voice;
    }
}