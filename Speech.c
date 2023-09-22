#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>
#include <wiringSerial.h>


#include "inputcommander.h"
// Speech


// 获取Speech信息
int SpeechGetCommand(struct InputCommander *Speech)
{   int nread = 0;

    read(Speech->fd,Speech->command,sizeof(Speech->command));

    if(nread == 0){
        printf("usart for Speech read over time\n");
    }else{
        return nread;
    }
}

// 初始化
int SpeechInit(struct InputCommander *Speech,char *ipAdress,char *port)
{  
    int fd;
    if((fd = serialOpen(Speech->deviceName,9600)) == -1)
    {
        exit(-1);
    }

    Imu ->fd = fd;
   return fd ;
}

// 定义imu基本信息
struct InputCommander SpeechContrl = 
{
    /* data */

    .commandName = "Speech",
    .deviceName = "/dev/ttySa4",
    .command = {'\0'},
    .Init = SpeechInit,
    .getCommand = SpeechGetCommand,
    .log = {'\0'},
    .next = NULL
     
};

// 线程
struct InputCommander* addSpeechContrlToInputCommandLink(struct InputCommander *phead)
{
     if(phead == NULL){
        return &Speech;
    }
    else{
        Speech.next = phead;
        phead = &Speech;
    }
}