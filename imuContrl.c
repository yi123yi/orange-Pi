#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>
#include <wiringSerial.h>


#include "inputcommander.h"
// Imu


// 获取imu信息
int ImuGetCommand(struct InputCommander *Imu)
{   int nread = 0;

    read(Imu->fd,Imu->command,sizeof(Imu->command));

    if(nread == 0){
        printf("usart for Imu read over time\n");
    }else{
        return nread;
    }
}

// 初始化
int ImuInit(struct InputCommander *Imu,char *ipAdress,char *port)
{  
    int fd;
    if((fd = serialOpen(Imu->deviceName,9600)) == -1)
    {
        exit(-1);
    }

    Imu ->fd = fd;
   return fd ;
}

// 定义imu基本信息
struct InputCommander ImuContrl = 
{
    /* data */

    .commandName = "Imu",
    .deviceName = "/dev/ttySa4",
    .command = {'\0'},
    .Init = ImuInit,
    .getCommand = ImuGetCommand,
    .log = {'\0'},
    .next = NULL
     
};

// 线程
struct InputCommander* addimuContrlToInputCommandLink(struct InputCommander *phead)
{
     if(phead == NULL){
        return &Imu;
    }
    else{
        Imu.next = phead;
        phead = &Imu;
    }
}