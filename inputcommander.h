#include <wiringPi.h>
#include <stdlib.h>

struct  InputCommander
{
    /* data */
   char commandName[128];
   char deviceName[128];
   char command[32];
   int (*Init)(char *name,char *ipAdress,char *port);
   int (*getCommand)(char *cmd);
   char log[1024];
    int fd;
    char port[12];
    char ipAddress[32];
    int sfd;
   struct inputcommander *next;


};

struct InputCommander* addvoiceContrlToInputCommandLink(struct InputCommander *phead);
struct InputCommander* addsocketContrlToInputCommandLink(struct InputCommander *phead);
struct InputCommander* addSpeechContrlToInputCommandLink(struct InputCommander *phead);