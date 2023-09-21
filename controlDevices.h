#include <wiringPi.h>
#include <stdlib.h>
struct Devices
{
    /* data */
   char deviceName[128];
   int status;
   int pinNum;


   int (*open)(int pinNum);
   int (*close)(int pinNum);
   int (*deviceInit)(int pinNum);

   int (*readStatus)(int pinNum);
   int (*changeStatus)(int status);

   struct Devices *next;


};

struct Devices* addblueLightToDeviceLink(struct Devices *phead);
struct Devices* addredLightToDeviceLink(struct Devices *phead);
struct Devices* addFireToDeviceLink(struct Devices *phead);