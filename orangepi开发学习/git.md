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



####  转化符号差异

```sh
warning: LF will be replaced by CRLF in **
```



#### ssh

```sh
git@github.com: Permission denied (publickey).
解决方式：https://blog.csdn.net/W_317/article/details/106518894
```



#### git更新文档

``` sh 
git add 测试文件夹

git commit -m 'test'

git remote add oragin (仓库地址)

git pull origin master

git push origin master
```





### 关于文件恢复和版本回退的一些总结（git 任务）

#### 文件恢复



###### 第一种方法： git reset

reset的本质是移动HEAD以及它所指向的branch

git reset 后面可以有l两个个参数：

git reset --hard <commit编号> 这个是将暂存区和工作区清空

彻底回退到上一个版本，所有变更都会消失

git reset --soft <commit编号> 这个会保留暂存区和工作区

只是撤销了commit ,上一次的更改还在，什么都没变

在实际操作中，我先创建了自己的测试空间，然后创建了一个test.sh的文档，输入：你好呀，然后add,commit，提交了第一次修改，然后我再修改了test.sh，进行了第二次提交，这时候我用git log 得到对应的commit编号，git reset --hard 编号 就回到了第一次的版本，若使用git reset --soft 文件内容就没有对应改变。

###### 第二种方法： git checkout 文件名



这种方法可以直接将commit的文件直接回到未修改前

我将test.sh add,commit后，用git checkout test.sh就直接回到了未修改前



### 版本回退

- git reset HEAD~

-  git reset HEAD^ 

- 创建一个新的文档test.txt，进行两次add，commit ,之后git log 查看是否体交了两次版本，再使用git 

#### 第二种方法: git revert <commit编号>
   git log 找到对应的编号，当使用这个编号作为参数传入git revert时，本地文件就会回到这个编号之前的版本，然后这个操作也会作为历史记录在git log里。

   在本地操作中两个方法都可以，但若是已经将本地仓库push到远程后，最好使用git revert 这个操作
合并分支的两种方法

#### 第一种方法git merge

git checkout branch_name #用来切换到某个分支(如要合并到master分支，就切换到master分支下)
git pull
git branch -a #查看是否所有分支都pull下来了
git merge branch_name #合并某个分支
git branch -d branch_name #删除某个分支



#### 第二种方法git rebase
git checkout branch_name_1  #切换到某个分支
git rebase branch_name_2  #但这么操作容易使在git status中造成冲突

# 多人合作尽量用merge 
