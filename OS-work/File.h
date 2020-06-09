#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
#include<string>
//用户定义
using namespace std;


string UserName[8]={"user1","user2","user3","user4",
"user5","user6","user7","user8"
};

string Password[8] ={"12345","12345","12345","12345",
"12345","12345","12345","12345"
};

int login_userid=-1; //目前登陆用户编号
int filearray[8]={-1,-1,-1,-1,-1,-1,-1,-1,};
int physic[100]; //文件地址缓冲区     ?我觉得这个地方可以改改
int style=1; //文件类型  ?我觉得这个地方可以改改
string cur_dir[10]="filestem"; //当前目录
//输入的指令
struct command{
    char com[10];
}cmd[17];

//文件块 1个1KB
struct block{
    int number; //存放空闲盘块的个数
    int free[50];//存放空闲盘块的地址
    int is_use;//怕你快是否被占用标志
    char content[1000];//块上每个每个字节存放的符号

}memory[20449];

//超级块
struct block_super{
    int n;//空闲盘块的个数
    int free[50];//存放进入栈中的空闲块
    int empty_block[50];//存放下一组空闲盘块的地址
}super_block;

//i结点信息
struct node{
    int file_style;
    int file_length;
    int file_address[100];
    int limit ; //3个等级 --做出更改依据unix rwx--r:4 w:2 x:1 可读，可写，可执行 r+w+x
    int file_UserId;
}i_node[640];


//目录
struct dir{
    char file_name[10];
    int i_numl; //文件i结点编号
    char dir_name[10];
}root[640];



