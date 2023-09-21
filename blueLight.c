#include "controlDevices.h"
#include <fcntl.h> 
#include <stdio.h>

int  blueLightOpen(int pinNum)
{
      digitalWrite(pinNum,HIGH);
}

int blueLightClose( int pinNum)
{
    digitalWrite(pinNum,LOW);
}

int blueLightCloseInit(int pinNum)
{
    pinMode(pinNum,OUTPUT);
    digitalWrite(pinNum,HIGH);
}

int blueLightStatus(int status)
{
   
}


struct Devices upstairLight = 
{
    /* data */
    .deviceName = "blueLight",
    .pinNum = 21,
    .open = blueLightOpen ,
    .close = blueLightClose ,
    .deviceInit =  blueLightCloseInit,
    .changeStatus = blueLightStatus
};


struct Devices* addblueLightToDeviceLink(struct Devices *phead)
{
    if(phead == NULL){
        return &upstairLight;
    }
    else{
        upstairLight.next = phead;
        phead = &upstairLight;
    }
}