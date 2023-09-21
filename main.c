#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "controlDevices.h"
#include "inputcommander.h"
struct Devices* findDeviceByName(char *name,struct Devices *phead)
{
   struct Devices *tmp = phead;

   if(phead = NULL)
   {
     return NULL;
   }else{
     while(tmp != NULL){
        if(strcmp(tmp -> deviceName,name) == 0){
            return tmp;
        }
        tmp = tmp->next;
     }
    return NULL;
   }

}

void *voice_thread(void *dates)
{

}

void *socket_thread(void *dates)
{

}

int main()
{
//   初始化
//   char *name = "bathroomLight";
 char name [128];
 struct Devices *tmp = NULL
 pthread_t voiceThread;
 pthread_t socketThread;

  if( -1 == wiringPiSetup)
  {
    return -1 ;
  }
//   基础控制灯
//    struct Devices          *pdeviceHead = NULL;
//     struct InputCommander *pCommandHead = NULL;
//    pdeviceHead = addredLightToDeviceLink(pdeviceHead);

//    pCommandHead = addvoiceContrlToInputCommandLink(pCommandHead);

// 线程
   phread_create(&voiceThread,NULL,voice_thread,NULL);
    phread_create(&socketThread,NULL,socket_thread,NULL);
   while(1){
     printf("Input:\n");
     scanf("%s",name);

    tmp = findDeviceByName(name,pdeviceHead);
   if(tmp != NULL){
       tmp->deviceInit(tmp->pinNum);
       tmp->open(tmp->pinNum);
      
   }
  
   }
   
 
   
// 线程创立
  
 return 0;
}