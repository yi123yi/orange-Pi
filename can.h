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

 
#ifndef AF_CAN
#define AF_CAN 29
#endif
#ifndef PF_CAN
#define PF_CAN AF_CAN
#endif


#define 	FIFO_SIZE   1024

/* CAN通信抽象结构体定义*/
// struct SockerCan
// {
//     /* CAN硬件名称 */
//     char *name;
//  /* CAN端口号，裸机里为端口号;linux应用里作为socket套接口 */
//     int  can_port;                                
//     /* CAN控制器配置函数，返回端口号赋值给can_port */
//      int  (*can_set_controller)( void );                  
//     /* CAN接口中断创建，在linux中对应创建接收线程 */
//     // void (*can_set_interrput)( int can_port , pCanInterrupt callback );             
//     /* CAN读取报文接口 */
//      void (*can_read)( int can_port , CanRxMsg* recv_msg);   
//     /* CAN发送报文接口*/
//     void (*can_write)( int can_port , CanTxMsg send_msg);   
//  };

typedef enum
{
  CAN_PORT_0 = 0, // can0
  CAN_PORT_1,     // can1
}can_port_t ;
 
typedef struct {
	uint16_t buffer[FIFO_SIZE];
	uint8_t ptrWrite;
	uint8_t ptrRead;
}can_queue_t;

typedef struct
{
  char *name;
  int fd;
  //fd_set fdsr;
 
  pthread_t send_thread;
  pthread_t recv_thread;
  pthread_t time_thread;  
 
  can_queue_t *send_queue; // 接受和发送的队列
  can_queue_t *recv_queue;
} can_t;
 
// void *CanInit(int arg);
 
#endif /* _CAN_H_ */