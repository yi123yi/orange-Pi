#include "can.h"
 
static can_t *can_init(int name)
{
  int ret;
  struct sockaddr_can addr;
  struct ifreq ifr;
  struct can_filter rfilter[1];
  can_t *current = (can_t *)malloc(sizeof(can_t));
 
  current->fd = Socket(PF_CAN, SOCK_RAW, CAN_RAW);
  sprintf(ifr.ifr_name, "can%d", name);
  current->name = (char *)malloc(6);
  memset(current->name, 0, 6);
  sprintf(current->name, "can%d", name);
 
  ret = ioctl(current->fd, SIOCGIFINDEX, &ifr);
 
  if(ret < 0)
  {
    exit(0);
  }
 
  addr.can_family = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;
  Bind(current->fd, (struct sockaddr *)&addr, sizeof(addr));
 
  rfilter[0].can_id = 0x2;
  rfilter[0].can_mask = 0;
  Setsockopt(current->fd, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));
 
  return current;
}
 
static void *can_send_thread(void *arg)
{
  int ret;
  can_t *current = arg;
  can_frame_t frame;
  uint8_t read_ret = 0;
 
  while(1)
  {
    Write(current->fd, &frame, sizeof(frame));
    read_ret = current->send_queue->can_read(current->send_queue, &frame);
    if(CAN_OK == read_ret)
    {
      ret = Write(current->fd, &frame, sizeof(frame));
      usleep(1200);
    }
    usleep(100);
  }
 
  return NULL;
}
 
static void *can_recv_thread(void *arg)
{
  int ret, i;
  can_frame_t frame;
  struct timeval tv;
  fd_set rset;
  can_t *current = arg;
 
  while (1)
  {
    tv.tv_sec = 0;
    tv.tv_usec = 200;
 
    FD_ZERO(&rset);
    FD_SET(current->fd, &rset);
    ret = select(current->fd + 1, &rset, NULL, NULL, NULL);
 
    if (0 == ret)
    {
      return NULL;
    }
 
    ret = read(current->fd, &frame, sizeof(frame));
 
    if (ret < sizeof(frame))
    {
      return NULL;
    }
 
    if (current->recv_queue->can_write(current->recv_queue, &frame) == CAN_ERROR)
    {
     
    }
  }
 
  return NULL;
}
 
void *CanInit(int arg)
{
  can_t *current = can_init(arg);
 
  current->recv_queue = CanQueueInit(CAN_RECV_QUEUE_SIZE);
  current->send_queue = CanQueueInit(CAN_SEND_QUEUE_SIZE);
 
  pthread_create(&current->send_thread, NULL, can_send_thread, (void *)current);
  pthread_create(&current->recv_thread, NULL, can_recv_thread, (void *)current);
}