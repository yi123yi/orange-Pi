## orangepi 开发事项



#### 蓝牙

``` sh
sudo apt-get install bluez
sudo apt-get install libbluetooth-dev
sudo pip install gatt
```



> 运行hciconfig查看对于节点

> 运行hcitool dev可以看到我们的蓝牙设备的硬件地址

> 运行hcitoo --help 可以查看更多相关命令

``` sh
sudo hciconfig hci0 up 激活
```



#### 串口

串口设备节点：ls /dev/ttyS*

> 打开串口 ： open

``` sh
O_NOCTTY ：告诉内核这个程序不想作为控制终端。如果不指定该标志，任何输入都会影响程序（比如键盘中止信号等）。
O_NDELAY ：告诉内核这个程序不关注DCD信号线的状态。如果不指定该标志，当DCD信号线是空电压值的时候，程序将会进入睡眠
```

> 发送数据  write

``` sh
write函数写完后会返回发送的字节数，如果发生错误会返回-1.
```

> 接受数据  read



## Shell

### 获取串口号:

```sh
配置串口属性（stty命令）:比如我们设置串口/dev/ttyS0波特率为57600和odd parity，命令如下stty -F /dev/ttyS0 57600 parodd
```

 

### 串口数据读写操作：

``` sh
使用echo向串口发送数据，如echo “command” > /dev/ttyUSB0
可以使用cat来读取串口中的数据，如cat /dev/ttyUSB0
读取数据并保存到txt文本文件中，如cat /dev/ttyUSB0 > file.txt
```



### can通信

#### 设置波特率

```sh
sudo ip link set can0 up type can bitrate 1000000
```

#### 查看设备

```sh
ifconfig  
```



#### 注意事项

电机固件版本不一致导致代码命令不同



### 激光雷达

#### 连接雷达

```sh
cd /dev
ls ttyUSB*
sudo chmod 777 ttyUSB0
```



### 项目搭建

```sh
cd unitree_lidar_sdk
mkdir build
cd build
cmake .. && make -j2
```

### 运行

```sh
../bin/example_lidar
```



### System load

#### 僵尸进程

```sh 
top                   查看
ps -A -ostat,ppid,pid,cmd | grep -e '^[Zz]'
kill -9 id
```

 [linux top命令详解（看这一篇就够了）_Steven.1的博客-CSDN博客](https://blog.csdn.net/weixin_45465395/article/details/115728520)



### 查看系统日志

``` sh
dmesg命令: 查看内核日志，包括系统启动信息和硬件信息等.

journalctl命令: 查看systemd日志，包括系统服务的启动和停止信息等.

tail命令: 查看指定日志文件的末尾内容，可以用于查看系统日志文件var/log/messages、/var/og/syslog等

grep命令: 用于过滤日志文件中的内容，可以根据关键字查找特定的日志信息5.less命令: 用于查看大型日志文件，可以进行分页和搜索等操作
```



#### 查看最近的系统日志信息:

```sh
dmesg | tail
```



#### 查看systemd的日志信息:

``` sh
journalctl
```



#### 查找/var/log/messages日志文件中包含“error”的行:

``` sh
grep"error" /var/log/messages
```





### PCA9685

#### i2c

```sh
sudo i2cdetect -y -r -a 1          查看硬件地址
```

