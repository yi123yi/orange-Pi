#ifndef _CAN_H_
#define _CAN_H_
 
#include <stdio.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <linux/socket.h>
#include <linux/can.h>
#include <linux/can/error.h>
#include <linux/can/raw.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>
#include "can_queue.h"
#include "type.h"
 
#ifndef AF_CAN
#define AF_CAN 29
#endif
#ifndef PF_CAN
#define PF_CAN AF_CAN
#endif
 
typedef enum
{
  CAN_PORT_0 = 0, // can0
  CAN_PORT_1,     // can1
}can_port_t ;
 
typedef struct
{
  char *name;
  int fd;
  fd_set fdsr;
 
  pthread_t send_thread;
  pthread_t recv_thread;
  pthread_t time_thread;  
 
  can_queue_t *send_queue; // 接受和发送的队列
  can_queue_t *recv_queue;
} can_t;
 
void *CanInit(int arg);
 
#endif /* _CAN_H_ */