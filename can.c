#include "can.h"
#include "Speed_x57.h"

#define ip_cmd_set_can_params  "sudo ip link set can0 up type can bitrate 1000000"/* 将CAN0波特率设置为1000000 bps */
#define ip_cmd_open            "ifconfig can0 up"      /* 打开CAN0 */
#define ip_cmd_close           "ifconfig can0 down"    /* 关闭CAN0 */ 

extern uint8_t cmd[16] ;



static can_t *can_init(int name)
{
  int ret;
  struct sockaddr_can addr;
  struct ifreq ifr;
  struct can_filter rfilter[1];
  can_t *current = (can_t *)malloc(sizeof(can_t));
 
  current->fd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
  if(current->fd  < 0)
  {
      perror("socket can creat error!\n");
      exit(0);
  }

  strcpy(ifr.ifr_name, "can0"); //指定名字

  current->name = (char *)malloc(6);
  memset(current->name, 0, 6);
  strcpy(current->name, "can0");
 
  ret = ioctl(current->fd, SIOCGIFINDEX, &ifr);
 
  if(ret < 0)
  {
    exit(0);
  }
 
  addr.can_family = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;
  bind(current->fd, (struct sockaddr *)&addr, sizeof(addr));
 
  rfilter[0].can_id = 0x2;
  rfilter[0].can_mask = 0;
  setsockopt(current->fd, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));
 
  return current;
}
 
static void *can_send_thread(void *arg)
{
  int ret;
  can_t *current = arg;
  //can_frame_t frame;
  uint8_t read_ret = 0;
  ZDT_X57_Velocity_Control(1, 0, 1000, 3000.0f, 0);
  
  write(current->fd, &cmd, sizeof(cmd));

   //如果 ret 不等于帧长度，就说明发送失败 
 if(sizeof(cmd) != ret)  perror("write error");
   
  // switch (Motor)
  // {
  // case 1 /* constant-expression */:
  //   /* code */
  // ZDT_X57_Reset_CurPos_To_Zero(1);   
  //   break;
  // case 2 :
  // ZDT_X57_Reset_Clog_Pro(1);
  //   break;
  // case 3 :
  // // ZDT_X57_Read_Sys_Params(1,);
  //   break;
  // case 4 :
  //  ZDT_X57_En_Control();
  //   break;
  // case 5 :
  // ZDT_X57_Torque_Control();
  //   break;
  // case 6:
  // ZDT_X57_Velocity_Control();
  //   break;
  // default:
  //   break;
  // }
  
  while(1)
  {
    // Write(current->fd, &frame, sizeof(frame));
    // read_ret = current->send_queue->can_read(current->send_queue, &frame);
    // if(CAN_OK == read_ret)
    // {
    //   ret = Write(current->fd, &frame, sizeof(frame));
    //   usleep(1200);
    // }
    // Write(current->fd, &cmd, sizeof(cmd));
    // usleep(100);
  }
 
  return NULL;
}
 
static void *can_recv_thread(void *arg)
{
  int ret, i;
  //can_frame_t frame;
 // struct timeval tv;
  // fd_set rset;
  can_t *current = arg;
 
  while (1)
  {
    // tv.tv_sec = 0;
    // tv.tv_usec = 200;
 
    // FD_ZERO(&rset);
    // FD_SET(current->fd, &rset);
    // ret = select(current->fd + 1, &rset, NULL, NULL, NULL);

    // if (0 == ret)
    // {
    //   return NULL;
    // }

    // ret = read(current->fd, &frame, sizeof(frame));

    // if (ret < sizeof(frame))
    // {
    //   return NULL;
    // }

    // if (current->recv_queue->can_write(current->recv_queue, &frame) == CAN_ERROR)
    // {
    // }

    
  }
 
  return NULL;
}
 

void *CanInit(int arg)
{ 
 

  can_t *current = can_init(arg);


  pthread_create(&current->send_thread, NULL, can_send_thread, (void *)current);

  pthread_create(&current->recv_thread, NULL, can_recv_thread, (void *)current);
}

// test

int main()
{

 return 0;
}

// struct SockerCan Cancontrl = 
// {
//     /* data */
//     .name = "can0",
//     .can_port = CAN_PORT_0,
//     .can_set_interrput = CanInit,
//     .can_read  = can_recv_thread,
//     .can_write = can_send_thread
// };
