#include "controlDevices.h"
#include <fcntl.h> 
#include <stdio.h>


int fireIforNotInit(int pinNum)
{
    pinMode(pinNum,INPUT);
    digitalWrite(pinNum,HIGH);
}

int fireIforNotStatus(int status)
{
   return digitalRead(pinNum);
}


struct Devices fireIforNot = 
{
    /* data */
    .deviceName = "fireIforNot",
    .pinNum = 25,
    .deviceInit =  fireIforNotInit,
    .readStatus = fireIforNotStatus
};


struct InputCommander* addFireToDeviceLink(struct Devices *phead)
{
    if(phead == NULL){
        return &fireIforNot;
    }
    else{
        fireIforNot.next = phead;
        phead = &fireIforNot;
    }
}