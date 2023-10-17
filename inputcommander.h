#include <wiringPi.h>
#include <stdlib.h>


#include "IMU.h"
struct  InputCommander
{
    /* data */
   char commandName[128];
   char deviceName[128];
   char command[32];
   int (*Init)(struct InputCommander *Imu,char *ipAdress,char *port);
   int (*getCommand)(struct InputCommander *Imu);
   int (*sendCommand)(int I_fd , U8 *buf,int longth);
   char log[1024];
    int fd;
    char port[12];
    char ipAddress[32];
    int sfd;
   struct InputCommander *next;


};
// 线程
struct InputCommander* addimuContrlToInputCommandLink(struct InputCommander *phead);
struct InputCommander* addvoiceContrlToInputCommandLink(struct InputCommander *phead);
struct InputCommander* addsocketContrlToInputCommandLink(struct InputCommander *phead);
struct InputCommander* addSpeechContrlToInputCommandLink(struct InputCommander *phead);