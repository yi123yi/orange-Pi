### git



```sh
warning:LF will be replaced by CRLF the next time Git touches  it 
```

CR/LF是不同操作系统上使用的换行符

- Dos和Windows平台： 使用回车（CR）和换行（LF）两个字符来结束一行，回车+换行(CR+LF),即“\r\n”；
- Mac 和 Linux平台：只使用换行（LF）一个字符来结束一行，即“\n”；

#### 解决问题

##### 情况一

```sh
#提交时转换为LF，检出时转换为CRLF
$ git config --global core.autocrlf true
```

##### 情况二

```sh
#提交时转换为LF，检出时不转换
$ git config --global core.autocrlf input
```



#### 

```sh
warning: LF will be replaced by CRLF in **
```

