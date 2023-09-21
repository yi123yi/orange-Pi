#include "controlDevices.h"
#include <fcntl.h> 
#include <stdio.h>

int  redLightOpen(int pinNum)
{
      digitalWrite(pinNum,HIGH);
}

int redLightClose( int pinNum)
{
    digitalWrite(pinNum,LOW);
}

int redLightCloseInit(int pinNum)
{
    pinMode(pinNum,OUTPUT);
    digitalWrite(pinNum,HIGH);
}

int redLightStatus(int status)
{
   
}


struct Devices bathroomLight = 
{
    /* data */
    .deviceName = "redLightOpen",
    .pinNum = 22,
    .open = redLightOpen ,
    .close = redLightClose ,
    .deviceInit =  redLightCloseInit,
    .changeStatus = redLightStatus
};


struct Devices* addredLightToDeviceLink(struct Devices *phead)
{
    if(phead == NULL){
        return &redLight;
    }
    else{
        redLight.next = phead;
        phead = &redLight;
    }
}