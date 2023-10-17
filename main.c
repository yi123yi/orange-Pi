#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h> 
#include "controlDevices.h"
#include "inputcommander.h"
struct Devices          *pdeviceHead = NULL;
struct InputCommander   *pCommandHead = NULL;

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



struct InputCommander* findCommandByName(char *name,struct InputCommander *phead)
{
   struct InputCommander *tmp = phead;

   if(phead = NULL)
   {
     return NULL;
   }else{
     while(tmp != NULL){
        if(strcmp(tmp -> commandName,name) == 0){
            return tmp;
        }
        tmp = tmp->next;
     }
    return NULL;
   }

}

void *Imu_thread(void *dates)
{  
   int nread;
   struct InputCommander *Imu;
   Imu = findCommandByName("Imu",pCommandHead);
   printf("thread...\n");
   if(Imu == NULL)
   {
     printf("find Imu error\n");

    //  return NULL
   }else{
     if(Imu -> Init(Imu,NULL,NULL) < 0)
     {
      printf("Init init\n");
     }
     while(1){
    nread = Imu ->getCommand(Imu); 
    if(nread == 0)
    {
      printf("nodata from Imu\n");
    }else{
      printf("Imu get data : %s \n",Imu->command);
    }
   }
   }


}

void *socket_thread(void *dates)
{

}

int main()
{
//   初始化
//   char *name = "bathroomLight";
 int pthread; 
 char name [128];
 struct Devices *tmp = NULL;

 pthread_t ImuThread;
 pthread_t socketThread;

  if( -1 == wiringPiSetup())
  {
    printf("error\n");
    return -1 ;
  }
//   基础控制灯
printf("try...\n");
//    pdeviceHead = addredLightToDeviceLink(pdeviceHead);

   pCommandHead = addimuContrlToInputCommandLink(pCommandHead);

// 线程
 pthread = pthread_create(&ImuThread,NULL,Imu_thread,NULL);
  //pthread_create(&socketThread,NULL,socket_thread,NULL);
 if(pthread == 0) {  printf("create thread successful\n");}
 else{printf("create thread error\n");}
   
// 线程创立
  pthread_join(ImuThread,NULL);
 return 0;
}