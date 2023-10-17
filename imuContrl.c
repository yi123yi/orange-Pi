#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <wiringPi.h>
#include <wiringSerial.h>

#include "IMU.h"
#include "inputcommander.h"
// Imu
//------------------------------------------------------------------------------
// 描述: 串口发送数据给设备
// 输入: buf[Len]=要发送的内容
// 返回: 返回发送字节数
//------------------------------------------------------------------------------
int IMU_FD;


// 获取imu信息
int ImuGetCommand(struct InputCommander *Imu)
{   int nread = 0;
  //  memset();
    read(Imu->fd,Imu->command,sizeof(Imu->command));

    if(nread == 0){
        printf("usart for Imu read over time\n");
    }else{
        return nread;
    }
}


// 发送imu信息
int ImuSendCommand(int I_fd , U8 *buf,int longth)
{   
    int n_write;
    n_write = write(I_fd,buf,longth);
    printf("%d\n",I_fd);
    if(n_write < 0)
        {
         printf("write error\n");
        }
   else{
    printf("write successful\n");
   }
}

void UART_Write(U8 *buf, int Len)
{  
    ImuSendCommand(IMU_FD ,buf, Len); //发送串口数据 

}
// 初始化
int ImuInit(struct InputCommander *Imu,char *ipAdress,char *port)
{  
    int fd;
    if((fd = serialOpen(Imu->deviceName,115200)) == -1)
    {   
        printf("error \n");
        exit(-1);
        
    }
    Imu ->fd = fd;
    IMU_FD = fd;
        /**
     * 设置设备参数
     * @param accStill    惯导-静止状态加速度阀值 单位dm/s?
     * @param stillToZero 惯导-静止归零速度(单位cm/s) 0:不归零 255:立即归零
     * @param moveToZero  惯导-动态归零速度(单位cm/s) 0:不归零
     * @param isCompassOn 1=需融合磁场 0=不融合磁场
     * @param barometerFilter 气压计的滤波等级[取值0-3],数值越大越平稳但实时性越差
     * @param reportHz 数据主动上报的传输帧率[取值0-250HZ], 0表示0.5HZ
     * @param gyroFilter    陀螺仪滤波系数[取值0-2],数值越大越平稳但实时性越差
     * @param accFilter     加速计滤波系数[取值0-4],数值越大越平稳但实时性越差
     * @param compassFilter 磁力计滤波系数[取值0-9],数值越大越平稳但实时性越差
     * @param Cmd_ReportTag 功能订阅标识
     */
    Cmd_03();//2.唤醒传感器
    Cmd_12(5, 255, 0,  0, 2, 60, 1, 3, 5, 0x0026); // 1.设置参数
    
    Cmd_19();//3.开启数据主动上报
    printf("init ....\n");
   return fd ;
}

// 定义imu基本信息
struct InputCommander ImuContrl = 
{
    /* data */

    .commandName = "Imu",
    .deviceName = "/dev/ttyS2",
    .command = {'\0'},
    .Init = ImuInit,
    .getCommand = ImuGetCommand,
    .sendCommand = ImuSendCommand ,
    .log = {'\0'},
    .next = NULL
     
};

// 线程
struct InputCommander* addimuContrlToInputCommandLink(struct InputCommander *phead)
{
     if(phead == NULL){
        return &ImuContrl;
    }
    else{
        ImuContrl.next = phead;
        phead = &ImuContrl;
    }
}