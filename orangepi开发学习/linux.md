## Linux 应用开发命令

### 关键命令说明

* [系统关机说明](#系统关机命令)
* [系统关机命令](#系统关机命令)
* [linux查看文本的指令](#linux查看文本的指令)
* [mount](#mount指令)
* [dmesg](#dmesg)
* [grep](#grep)
* [find](#find)
* [lsusb](#lsusb)
* [lsof](#lsof)



### 系统关机命令
|指令|说明|
|:-:|----|
|shutdown | 命令安全地将系统关机。|
|halt     | 就是调用shutdown -h。|
|reboot   | 工作过程差不多跟halt一样﹐不过它是引发主机重启|
|poweroff | 就是halt的软链接而已|
|init     | 所有进程的祖先﹐它的进程号始终为1﹐init 0为关机﹐init1为重启。|



### linux查看文本的指令
<table style="text-align:center">
   <tr>
      <td>cat</td>
      <td>tac</td>
      <td>sed</td>
      <td>head</td>
      <td>tail</td>
      <td>more</td>
      <td>less</td>
      <td>nl</td>
   </tr>
</table>

\> <strong>tac</strong>： cat的反向指令，从最后一行倒序显示全部内容

\> <strong>head</strong>： 只显示头几行

\> <strong>tail</strong>： 只显示最后几行 tail -f 可以实时显示log文件的更新

\> <strong>nl</strong>： 类似于cat -n，显示时输出行号



### mount
命令格式：
```sh
mount [-t vfstype] [-o options] device dir
```
挂载nfs
```sh
mount -t nfs 192.168.0.1:/tmp /mnt/nfs 
```
### 

### dmesg

```sh
cat /var/log/messages
```



###  grep

选项

```sh
-c：只输出匹配行的计数。

-C：匹配的上下文分别显示[number]行。

-I：不区分大小写(只适用于单字符)。

-i：不区分大小写。

-h：查询多文件时不显示文件名。

-l：查询多文件时只输出包含匹配字符的文件名。

-L：列出不匹配的文件名。

-n：显示匹配行及 行号。

-s：不显示不存在或无匹配文本的错误信息。

-v：显示不包含匹配文本的所有行。

-w：只匹配整个单词。

-E：扩展的正则表达式

-R：递归搜寻

--exclude=FILE：跳过FILE
```



正则表达式主要参数：

  \：忽略正则表达式中特殊字符的原有含义。

  ^：匹配正则表达式的开始行。

  $：匹配正则表达式的结束行。

  \<：从匹配正则表达式的行开始。

  \>：到匹配正则表达式的行结束。

  []：单个字符，如[A]即A符合要求 。

  [-]：范围，如[A-Z]，即A、B、C一直到Z都符合要求 。

  .：所有的单个字符。

  *：有字符，长度可以为0。




使用方法
```sh
#所有以d开头的文件，包含test的匹配行
grep "test" d*
#包含test或者yi 不区分大小写 显示行号 扩展正则表达式
grep -inE "test|zephyr" d*
#包含test和yi 不区分大小写 显示行号 扩展正则表达式
grep -in "test" d* | grep 'yi'
```

主要参数：

  －c：只输出匹配行的计数。

  －I：不区分大小写(只适用于单字符)。

  －h：查询多文件时不显示文件名。

  －l：查询多文件时只输出包含匹配字符的文件名。

  －L：列出不匹配的文件名

  －n：显示匹配行及行号。

  －s：不显示不存在或无匹配文本的错误信息。

  －v：显示不包含匹配文本的所有行。

  －R：递归搜寻

  －d skip：不递归搜寻

  －w：匹配整个单词

正则表达式主要参数：

  \：忽略正则表达式中特殊字符的原有含义。

  ^：匹配正则表达式的开始行。

  $：匹配正则表达式的结束行。

  \<：从匹配正则表达式的行开始。

  \>：到匹配正则表达式的行结束。

  []：单个字符，如[A]即A符合要求 。

  [-]：范围，如[A-Z]，即A、B、C一直到Z都符合要求 。

  .：所有的单个字符。

  *：有字符，长度可以为0。





``` sh
grep 'test' d*    显示以d开头的文件中包含的test行

grep 'test' aa bb cc   查找文件aa bb cc 中匹配的test行

grep 'test'|'hello' files 匹配test或者hello

grep '\<man' files  匹配manic 和man 不匹配batman

grep '\<man\>'    只匹配man 不匹配batman和manic

grep '^man' files  匹配的字符行首

grep '$man' files  匹配的字符串仔行尾
```



### find

用法

```sh
find [-path ..] [expression]
```



选项

```sh
-name   按照文件名

-iname   按照文件名 忽略大小写

-perm   按照文件权限

-user   按照文件拥有者

-group   按照文件所属的组

-mtime -n +n 按照文件的更改时间来查找文件， -n：n天以内，+n：n天以前

-type   查找某一类型：文件类型有：普通文件(f)，目录(d)，字符设备文件(c)，块设备文件(b)，符号链接文件(l)，套接字文件(s)，管道文件(p)

-size n  查找文件长度为n块（一块等于512字节）的文件，带有c时表示文件长度以字节计。 

-mount   不跨越文件系统

-follow  遇到符号链接文件，就跟踪至链接所指向的文件

-path   匹配文件路径或者文件

-exec   执行后续命令操作

-a     and 与操作

-o     or  或操作

-not    not 非操作
```



##### 查询所有mk文件中的date文本

```sh
find ./build/ -name "*.mk" -print -exec grep -rwn "date" --color=auto {} \;
```



###  lsusb

显示系统中以及连接到系统的USB总线信息的工具。

```sh
$ lsusb



Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub

Bus 002 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub

Bus 003 Device 001: ID 1d6b:0001 Linux Foundation 1.1 root hub

Bus 004 Device 001: ID 1d6b:0001 Linux Foundation 1.1 root hub

Bus 005 Device 001: ID 1d6b:0001 Linux Foundation 1.1 root hub

Bus 006 Device 001: ID 1d6b:0001 Linux Foundation 1.1 root hub

Bus 007 Device 001: ID 1d6b:0001 Linux Foundation 1.1 root hub

Bus 008 Device 001: ID 1d6b:0001 Linux Foundation 1.1 root hub

Bus 002 Device 003: ID 17ef:4811 Lenovo Integrated Webcam [R5U877]

Bus 008 Device 002: ID 0a5c:217f Broadcom Corp. Bluetooth Controller
```



> Bus 008 : 指明设备连接到哪（总线）

> Device 002 : 表明这是连接到总线上的第二台设备

> ID : 设备的ID

> Broadcom Corp. Bluetooth Controller :生产商名字和设备名



列出USB详细信息
```sh
$ lsusb -v
```
列出有多少USB设备
```sh
$ find /dev/bus
```
打印特定设备的详细信息
```sh
$ lsusb -D /dev/bus/usb/008/002
```



###  lsof

列出当前系统打开文件的工具

```sh
$ sudo lsof

COMMAND   PID    USER  FD    TYPE   DEVICE   SIZE    NODE    NAME

init    1     root  cwd    DIR    3,3    1024    2     /

init    1     root  rtd    DIR    3,3    1024    2     /

init    1     root  txt    REG    3,3    38432    1763452  /sbin/init

init    1     root  mem    REG    3,3    106114   1091620  /lib/libdl-2.6.so

init    1     root  mem    REG    3,3    7560696   1091614  /lib/libc-2.6.so

init    1     root  mem    REG    3,3    79460    1091669  /lib/libselinux.so.1

init    1     root  mem    REG    3,3    223280   1091668  /lib/libsepol.so.1

init    1     root  mem    REG    3,3    564136   1091607  /lib/ld-2.6.so

init    1     root  10u    FIFO    0,15          1309   /dev/initctl
```



<table style="text-align:center">
   <tr>
      <td>COMMAND</td>
      <td>进程的名称</td>
      <td></td>
   </tr>
   <tr>
      <td>PID</td>
      <td>进程标识符</td>
      <td></td>
   </tr>
   <tr>
      <td>USER</td>
      <td>进程所有者</td>
      <td></td>
   </tr>
   <tr>
      <td>FD</td>
      <td>文件描述符</td>
      <td>应用程序通过文件描述符识别该文件。如cwd、txt、mem等</td>
   </tr>
   <tr>
      <td>TYPE</td>
      <td>文件类型</td>
      <td>REG(文件) DIR(目录) CHR(字符) BLK(块设备) FIFO(管道) UNIX(UNIX 域套接字) IPv4(IP套接字)</td>
   </tr>
   <tr>
      <td>DEVICE</td>
      <td>指定磁盘的名称</td>
      <td></td>
   </tr>
   <tr>
      <td>SIZE</td>
      <td>文件大小</td>
      <td></td>
   </tr>
   <tr>
      <td>NODE</td>
      <td>文件inode</td>
      <td>每个文件都有一个唯一的inode</td>
   </tr>
   <tr>
      <td>NAME</td>
      <td>文件名称</td>
      <td></td>
   </tr>
</table>


参数列表

```sh
lsof  filename    显示打开指定文件的所有进程

lsof -a       表示两个参数都必须满足时才显示结果

lsof -c string    显示COMMAND列中包含指定字符的进程所有打开的文件

lsof -u username   显示所属user进程打开的文件

lsof -g gid     显示归属gid的进程情况

lsof +d /DIR/    显示目录下被进程打开的文件

lsof +D /DIR/    同上，但是会搜索目录下的所有目录，时间相对较长

lsof -d FD      显示指定文件描述符的进程

lsof -n       不将IP转换为hostname，缺省是不加上-n参数

lsof -i       用以显示符合条件的进程情况

lsof -i[46] [protocol][@hostname|hostaddr][:service|port]

​          46 --> IPv4 or IPv6

​          protocol --> TCP or UDP

​          hostname --> Internet host name

​          hostaddr --> IPv4地址

​          service --> /etc/service中的 service name (可以不只一个)

​          port --> 端口号 (可以不只一个)


```

查找应用程序打开的文件的名称和数目
```sh
#显示打开指定文件的所有进程
$ lsof  filename
#例如:打开所有使用/dev/urandom的进程
$ lsof /dev/urandom
#查看22端口现在运行的情况 
$ lsof -i :22
#查看所属xiaxiaowen用户进程所打开的文件类型为txt的文件
$ lsof -a -u xiaxiaowen -d txt
#查找谁在使用文件系统
$ lsof /media/xiaxiaowen/机械硬盘
COMMAND  PID       USER   FD   TYPE DEVICE SIZE/OFF NODE NAME
zsh     8465 xiaxiaowen  cwd    DIR   8,17     8192    5 /media/xiaxiaowen/机械硬盘
```