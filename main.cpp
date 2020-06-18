#include "File.h"

//格式化
/*
void format()
{
    int i, j, k;

    super_block.n = 50;

    for (i = 0; i < 50; i++) //超级块初始化
    {
        super_block.free[i] = i; //存放进入栈中的空闲块
        //super_block.stack[i]=50+i; //存放下一组的盘块
    }

    for (i = 0; i < 640; i++) //i结点信息初始化
    {
        for (j = 0; j < 100; j++) {
            i_node[i].file_address[j] = -1; //文件地址
        }

        i_node[i].limit = -1;
        i_node[i].file_length = -1; //文件长度
        i_node[i].file_style = -1; //文件类型
        i_node[i].file_UserId = -1; //用户ID
    }

    for (i = 0; i < 640; i++) //目录项信息初始化
    {
        strcpy(root[i].file_name, "");
        root[i].i_numl = -1;
        strcpy(root[i].dir_name, "");
    }

    for (i = 0; i < 20449; i++) //存储空间初始化
    {
        memory[i].number = 0; //必须有这个
        memory[i].is_use = 0;
        for (j = 0; j < 50; j++) {
            memory[i].free[j] = -1;
        }
        for (int c = 0; c < 1000; c++) {
            memory[i].content[c] = '\0';
        }
    }

    for (i = 0; i < 20449; i++) //将空闲块的信息用成组链接的方法写进每组的最后一个块中
    {
        //存储空间初始化
        if ((i + 1) % 50 == 0) {
            k = i + 1;
            for (j = 0; j < 50; j++) {
                if (k < 20450) {
                    memory[i].free[j] = k; //下一组空闲地址
                    memory[i].number++; //下一组空闲个数 注意在memory[i].n++之前要给其赋初值
                    k++;
                } else {
                    memory[i].free[j] = -1;
                }
            }

            memory[i].is_use = 0; //标记为没有使用
            continue; //处理完用于存储下一组盘块信息的特殊盘块后，跳过本次循环
        }

        for (j = 0; j < 50; j++) {
            memory[i].free[j] = -1;
        }

        memory[i].number = 0;
    }

    for (int l = 0; l < 8; l++) {

        filearray[l] = -1;
    }

    file_array_head = 0;

    for (int u = 0; u < 100; u++) {

        physic[u] = -1;
    }

    printf("已经初始化完毕\n");

    printf("进入UNIX文件模拟............\n\n");
}
*/
void format() {
    int i, j, k;
    super_block.n = 50;
    for (i = 0; i < 50; i++) {
        super_block.free[i] = i;
        //super_block.empty_block[i] = 50 + i;//存放下一组的盘块
    }
    for (i = 0; i < 640; i++) {
        for (j = 0; j < 100; j++) {
            i_node[i].file_address[j] = -1;
        }
        i_node[i].limit = -1;
        i_node[i].file_style = -1;
        i_node[i].file_UserId = -1;
    }
    for (i = 0; i < 640; i++) {
        strcpy(root[i].file_name, "");
        root[i].i_numl = -1;
        strcpy(root[i].dir_name, "");
    }
    for (i = 0; i < 20449; i++) {
        memory[i].number = 0;
        memory[i].is_use = 0;
        for (j = 0; j < 50; j++)
            memory[i].free[j] = -1;
        for (int c = 0; c < 1000; c++)
            memory[i].content[c] = '\0';
    }
    for (i = 0; i < 20449; i++) {
        if ((i + 1) % 50 == 0) {  //成组链接法超级快初始化
            k = i + 1;
            for (j = 0; j < 50; j++) {
                if (k < 20450) {
                    memory[i].free[j] = k;
                    memory[i].number++;
                    k++;
                }
                else {
                    memory[i].free[j] = -1;
                }
            }
            memory[i].is_use = 0;
            continue;
        }
        for (j = 0; j < 50; j++) {
            memory[i].free[j] = -1;
        }
        memory[i].number = 0;
    }
    extern int filearray[8];
    for (int l = 0; l < 8; l++) {
        filearray[l] = -1;
    }
    extern int file_array_head;
    file_array_head = 0;
    extern int physic[100];
    for (int u = 0; u < 100; u++)
        physic[u] = -1;
    cout << "初始化已完毕" << endl;
    cout << "欢迎进入文件系统" << endl << endl;
}
void callback(int length);

void allot(int length) //分配空间

{

    int i, j, k, m, p;

    for (i = 0; i < length; i++) {

        k = 50 - super_block.n; //超级块中表示空闲块的指针

        m = super_block.free[k]; //栈中的相应盘块的地址

        p = super_block.free[49]; //栈中的最后一个盘块指向的地址

        if (p == -1 /*||memory[p].a==1*/) //没有剩余盘块

        {

            printf("内存不足,不能够分配空间\n");

            callback(i); //之前已分配的i个盘块回收;

            break;
        }

        if (super_block.n == 1) {

            memory[m].is_use = 1; //将最后一个盘块分配掉

            physic[i] = m;

            super_block.free[49] = -1;

            super_block.n = 0;

            for (j = 50 - memory[m].number; j < 50; j++) //从最后一个盘块中取出下一组盘块号写入栈中

            {

                super_block.free[j] = memory[m].free[j];

                super_block.n++;
            }

            continue; //要跳过这次循环，下面的语句在IF中已经执行过
        }

        physic[i] = m; //如果栈中超过一个盘，栈中的相应盘块的地址写进 文件地址缓冲区

        memory[m].is_use = 1;

        m = -1;

        super_block.n--;
    }
}

void callback(int length) //回收磁盘空间
{
    int i, j, k, m, q = 0;
    for (i = length - 1; i >= 0; i--) {
        k = physic[i];           //需要提供要回收的文件的地址
        m = 49 - super_block.n;  //回收到栈中的哪个位置
        if (super_block.n == 50) //注意 当super_block.n==50时 m=-1;的值
        {                        //super_block.n==50的时候栈满了，要将这个栈中的所有地址信息写进下一个地址中
            for (j = 0; j < 50; j++) {
                memory[k].free[j] = super_block.free[j];
            }
            int u;
            for (u = 0; u < 50; u++) {
                super_block.free[u] = -1;
                //super_block.stack[u]=memory[k].free[u];
            }
            super_block.n = 0;
            memory[k].number = 50;
        }
        memory[k].is_use = 0;
        if (m == -1) {
            m = 49; //将下一个文件地址中的盘块号回收到栈底中，这个地址中存放着刚才满栈的地址的信息
        }
        super_block.free[m] = physic[i]; //将下一个文件地址中的盘块号回收到栈中
        super_block.n++;
    }
}

void create_file(char filename[], int length, int userid, int limit) //创建文件
{

    int i, j;

    for (i = 0; i < 640; i++) {
        if (strcmp(filename, root[i].file_name) == 0) {
            printf("已经存在同名文件，不允许建立重名的文件\n");
            return;
        }
    }

    for (i = 0; i < 640; i++) {
        if (root[i].i_numl == -1) {
            root[i].i_numl = i;
            strcpy(root[i].file_name, filename);
            strcpy(root[i].dir_name, cur_dir); //把当前目录名 给新建立的文件
            i_node[i].file_style = style; //style==0 说明文件是目录文件
            i_node[i].file_length = length;
            i_node[i].limit = limit;
            i_node[i].file_UserId = userid; //printf("%s.%d\n",root[i].file_name,i_node[i].file_UserId);
            allot(length);

            for (j = 0; j < length; j++) {
                i_node[i].file_address[j] = physic[j];
            }

            int u;

            for (u = 0; u < 100; u++) //分配完清空缓冲区
            {
                physic[u] = -1;
            }

            break;
        }
    }
}

void del_file(char filename[]) //删除文件
{
    int i, j, k;

    for (i = 0; i < 640; i++) {
        if ((strcmp(filename, root[i].file_name) == 0) && (strcmp(cur_dir, root[i].dir_name) == 0) &&
            (i_node[root[i].i_numl].file_UserId == login_userid)) {
            //printf("1get here\n");
            int add, c;

            for (add = 0; add < i_node[root[i].i_numl].file_length; add++) //文件内容清空
            {
                for (c = 0; memory[i_node[root[i].i_numl].file_address[add]].content[c] != '\0'; c++) {
                    memory[i_node[root[i].i_numl].file_address[add]].content[c] = '\0';
                }
            }

            k = root[i].i_numl; //printf("2get here\n");
            i_node[k].file_UserId = -1;
            i_node[k].limit = -1;
            for (j = 0; j < i_node[k].file_length; j++) {
                physic[j] = i_node[k].file_address[j];
            } // printf("get here\n");

            callback(i_node[k].file_length); //调用 回收函数

            //回收完情空缓存区
            for (int u = 0; u < 100; u++) {
                physic[u] = -1;
            }

            for (j = 0; j < 100; j++) //删除文件后要将文件属性和目录项的各个值恢复初值
            {
                i_node[k].file_address[j] = -1; //文件占用的块号地址恢复初值
            }

            strcpy(root[i].file_name, ""); //文件名恢复初值
            root[i].i_numl = -1; //目录项的I结点信息恢复初值
            strcpy(root[i].dir_name, ""); //目录项的文件目录信息恢复初值
            i_node[k].file_length = -1; //文件长度恢复
            i_node[k].file_style = -1; //文件类型恢复初值
            break;
        }
    }

    if (i == 640) {
        printf("登录用户的该目录下不存在这个文件\n");
    }
}

void display_sys() //显示系统信息(磁盘使用情况)
{
    int i, m, k = 0;
    for (i = 0; i < 20449; i++) {
        if (memory[i].is_use == 0)
            k++;
    }

    m = 20449 - k;
    printf("空闲的盘块数是:\t");
    printf("%d\n", k);
    printf("使用的盘块数是:\t");
    printf("%d\n", m);
}

void show_file(char filename[]) //显示文件信息
{
    int i, j, k;
    printf("\t\t文件名字 文件类型 文件长度 读取权限 所属目录\t所属用户\n");
    for (i = 0; i < 640; i++) {
        k = root[i].i_numl;
        if (strcmp(filename, root[i].file_name) == 0 && (i_node[k].file_style == 1)) {
            printf("\t\t %s\t", root[i].file_name); //文件名
            printf("\t%d\t", i_node[k].file_style); //文件的类型
            printf("%d\t", i_node[k].file_length); //文件的长度
            printf("%d\t", i_node[k].limit);
            printf("%s\t", root[i].dir_name); //文件所在的目录
            printf("user%d\n", i_node[root[i].i_numl].file_UserId);
            printf("\t\t文件占用的物理地址\n");
            for (j = 0; j < i_node[k].file_length; j++) //显示物理地址
            {
                printf("%d ", i_node[k].file_address[j]); //文件具体占用的盘块号
            }
            printf("\n");

            break;
        }
    }

    if (i == 640) {
        printf("没有这个文件 或者这个文件不是正规文件\n");
    }
}
//shhch

void write_file(FILE *fp) //将信息写入系统文件中
{
    int i;
    fp = fopen("system", "wb");
    for (i = 0; i < 20449; i++) {
        fwrite(&memory[i], sizeof(struct block), 1, fp);
    }

    fwrite(&super_block, sizeof(struct block_super), 1, fp);

    for (i = 0; i < 640; i++) {
        fwrite(&i_node[i], sizeof(struct node), 1, fp);
    }

    for (i = 0; i < 640; i++) {
        fwrite(&root[i], sizeof(struct dir), 1, fp);
    }

    fclose(fp);
}

void read_file(FILE *fp) //读出系统文件的信息
{
    int i;

    fp = fopen("system", "rb");

    for (i = 0; i < 20449; i++) {
        fread(&memory[i], sizeof(struct block), 1, fp);
    }

    fread(&super_block, sizeof(struct block_super), 1, fp);

    for (i = 0; i < 640; i++) {
        fread(&i_node[i], sizeof(struct node), 1, fp);
    }

    for (i = 0; i < 640; i++) {
        fread(&root[i], sizeof(struct dir), 1, fp);
    }

    fclose(fp);
}

int login() {
    system("title 用户登录界面 ");
    printf("\n\n 用户名:");
    string tempusername;
    cin >> tempusername;
    //cout<<tempusername!!;

    int i;
    for (i = 0; i < 8; i++) {
        if (tempusername == UserName[i]) {
            printf(" 密码:");
            string temppassword;
            cin >> temppassword;

            if (temppassword == Password[i]) {

                login_userid = i;

                printf("登录成功，请稍等\n");

                for (int a = 0; a < 4; a++) {

                    Sleep(500);

                    printf(".");
                }

                return 0;
            } else {

                system("cls");

                printf("密码错误\n输入y:重新登录\n输入n:退出系统\n");

                getchar();

                char c = getchar();

                getchar();

                if (c == 'y' || c == 'Y') {

                    system("cls");

                    login();

                    return 0;
                }

                if (c == 'n' || c == 'N')

                    exit(0);
            }
        }
    }

    if (i == 8) {
        system("cls");
        printf("没有此用户\n输入y:重新登录\n输入n:退出系统\n");
        getchar();
        char c = getchar();
        getchar();
        if (c == 'y' || c == 'Y') {
            system("cls");
            //i=0;
            login();
            return 0;
        }
        if (c == 'n' || c == 'N')
            exit(0);
    }
    return 0;
}

void logout() /*退出*/

{

    printf(" \n Logouting");

    for (int a = 0; a < 4; a++) {

        Sleep(500);

        printf(".");
    }

    system("cls");
}

int open(char filename[10]) {

    int i;

    for (i = 0; i < 640; i++) {

        if (strcmp(root[i].file_name, filename) == 0 && i_node[root[i].i_numl].file_style == 1 &&
            i_node[root[i].i_numl].file_UserId == login_userid) {

            if (file_array_head < 8) {

                filearray[file_array_head] = root[i].i_numl;

                file_array_head++;
            } else {

                printf("打开的文件已达上限，无法打开本文件\n");
            }

            return root[i].i_numl;
        }
    }

    if (i == 640) {

        printf("您要打开的文件不存在或不属于该用户\n");
    }

    return 0;
}

void close(char filename[10]) {

    int i;

    for (i = 0; i < 640; i++) {

        if (strcmp(root[i].file_name, filename) == 0 && i_node[root[i].i_numl].file_style == 1 &&

            i_node[root[i].i_numl].file_UserId == login_userid) {

            int j;

            for (j = 0; j < file_array_head; j++) {

                if (root[i].i_numl == filearray[j]) {

                    int m;

                    for (m = j; m < file_array_head; m++) {

                        filearray[m] = filearray[m + 1];
                    }

                    file_array_head--;

                    return;
                }
            }

            if (j == file_array_head) {

                printf("您要关闭的文件未打开过～\n");
            }

            return;
        }
    }

    if (i == 640) {

        printf("您要关闭的文件不存在或不属于该用户\n");
    }

    return;
}

//ft

void create_dir(char filename[]) //创建目录

{

    style = 0; //0代表文件类型是目录文件

    create_file(filename, 4, login_userid, -1);

    style = 1; //用完恢复初值，因为全局变量，否则
}

void del_dir(char filename[]) //删除目录 需要判断目录下时候为空,不为空就不删除
{
    int i, j, k;
    for (i = 0; i < 640; i++) //还要加条件判断要删除的目录是不是当前目录
    {
        k = root[i].i_numl; //找到目录名字
        if (strcmp(root[i].file_name, filename) == 0 && strcmp(cur_dir, filename) != 0 && (i_node[k].file_style) == 0) {
            for (j = 0; j < 640; j++) {
                if (strcmp(filename, root[j].dir_name) == 0) {
                    printf("目录不为空不能直接删除\n");
                    break;
                }
            }
            if (j == 640 || i_node[root[i].i_numl].file_UserId == login_userid) {
                del_file(filename);
                break;
            }
            break;
        }
    }
    if (i == 640) {
        printf("这个不是目录文件 或者已登录用户不存在这个目录,或者你要删除的是当前目录\n");
    }
}

void display_curdir() //显示当前目录下的文件列表
{

    int i, k;

    cout << "用户名:" << UserName[login_userid] << endl;

    printf("\t\t文件名字 文件类型 文件长度 所属目录\n");

    for (i = 0; i < 640; i++) {

        if (strcmp(cur_dir, root[i].dir_name) == 0 && i_node[root[i].i_numl].file_UserId == login_userid)

            //查询文件中 所在目录信息和当前目录信息相同的数据

        {

            k = root[i].i_numl;

            printf("\t\t %s\t", root[i].file_name); //文件名

            printf("\t%d\t", i_node[k].file_style); //文件的类型

            printf("%d\t", i_node[k].file_length); //文件的长度

            printf("%s\n", root[i].dir_name); //文件所在的目录
        }
    }
}

void display_dir(char filename[]) //进入指定的目录

{

    int i, k;

    for (i = 0; i < 640; i++) {

        k = root[i].i_numl;

        //printf("i_node[%d].file_UserId %d,login_userid %d",k,i_node[k].file_UserId,login_userid) ; //判断文件类型是不是目录类型

        if ((strcmp(filename, root[i].file_name) == 0) && (i_node[k].file_style == 0) &&

            (i_node[k].file_UserId == login_userid)) {
            //printf("yes\n");

            strcpy(cur_dir, filename); //printf("cur_dir= %s\n",cur_dir); //将要进入的指定目录设置为当前目录 赋值不要反了strcpy(目的，源)

            return;
        }
    }

    if (i == 640) {

        printf("登录用户没有这个目录\n");
    }
}

void back_dir() //返回上一级目录

{

    int i, k;

    for (i = 0; i < 640; i++) //查询和当前目录名相同的目录文件名

    {

        k = root[i].i_numl;

        if (strcmp(cur_dir, root[i].file_name) == 0 && (i_node[k].file_style == 0)) {

            strcpy(cur_dir, root[i].dir_name); //将查询到的目录文件名 所在的目录赋值给当前目录
        }
    }
}

int read(char filename[10]) {

    int i;

    for (i = 0; i < 640; i++) {

        if (strcmp(root[i].file_name, filename) == 0 && i_node[root[i].i_numl].file_style == 1) {

            int j;

            for (j = 0; j < 8; j++) {
                //int n; for (n=0;n<8;n++) printf("%d\n",filearray[n]);

                if (root[i].i_numl == filearray[j]) {

                    if (i_node[root[i].i_numl].limit == 0 || i_node[root[i].i_numl].limit == 1) {

                        int c, add;

                        printf("\n 文件内容:");

                        for (add = 0; add < 100; add++)

                            for (c = 0; memory[i_node[root[i].i_numl].file_address[add]].content[c] != '\0'; c++)

                                printf("%c", memory[i_node[root[i].i_numl].file_address[add]].content[c]);

                        printf("\n ");
                    } else {

                        printf("你没有权限读取文件内容～～\n");
                    }

                    return 0;
                }
            }

            if (j == 8) {

                printf("\n 该文件未打开，请先打开文件再进行读写操作!!\n");
            }

            return 0;
        }
    }

    if (i == 640) {

        printf("您要读取的文件不存在\n");
    }

    return 0;
}

void write(char filename[10], char writec) {

    int i;

    for (i = 0; i < 640; i++) {

        if (strcmp(root[i].file_name, filename) == 0 && i_node[root[i].i_numl].file_style == 1) {

            int j; //for(j=0;j<8;j++) printf("%d",filearray[j]);

            for (j = 0; j < 8; j++) {

                if (root[i].i_numl == filearray[j]) {

                    if (i_node[root[i].i_numl].limit == 0 || i_node[root[i].i_numl].limit == 2) {

                        int c, add;

                        for (add = 0; add < 100; add++) {

                            for (c = 0; c < 1000; c++) {
                                //memory[i_node[root[i].i_numl].file_address[add]].content[c]='b';printf("\ns %c %d %d",memory[i_node[root[i].i_numl].file_address[add]].content[c],c);

                                if (memory[i_node[root[i].i_numl].file_address[add]].content[c] == '\0') {

                                    //printf("\n%d %d\n",add,c);

                                    memory[i_node[root[i].i_numl].file_address[add]].content[c] = writec;

                                    // memory[i_node[root[i].i_numl].file_address[add]].content[c]='b';

                                    printf("\n %c 已写入文件末尾～\n",
                                           memory[i_node[root[i].i_numl].file_address[add]].content[c]);

                                    return;
                                }
                            }
                        }

                        if (add == 100) {

                            printf("\n文件空间已满，写入失败～～\n");
                        }

                        return;
                    } else {

                        printf("你没有权限将内容写入文件～～\n");

                        return;
                    }

                    return;
                }
            }

            if (j == 8) {

                printf("\n 该文件未打开，请先打开文件再进行读写操作!!\n");
            }

            return;
        }
    }

    if (i == 640) {

        printf("您要写入的文件不存在\n");
    }
    return;
}

// 显示帮助信息
void help() {
    printf("用户名:user%d\n", login_userid);

    printf("注意:创建的文件长度 < 100\n\n"); //说明文件

    printf("0.初始化-------------------------format\n");

    printf("1.查看当前目录文件列表-----------dir\n");

    printf("2.查看文件信息-----------------------cat-----(cat + 空格 + 文件名) \n");

    printf("3.查看系统信息-------------------ls \n");

    printf("4.创建目录-----------------------md------(md + 空格 + 目录名) \n");

    printf("5.创建文件-----------------------vi-----(vi + 文件名 + 文件长度 + 权限)\n");

    printf("6.删除文件----------------------del-----(del + 空格 + 文件名) \n");

    printf("7.打开文件----------------------open----(open + 空格 + 文件名) \n");

    printf("8.关闭文件----------------------close---(close + 空格 + 文件名) \n");

    printf("9.读取文件----------------------read----(read + 空格 + 文件名) \n");

    printf("10.写入文件---------------------write--(write + 空格 + 文件名+ 空格 + 写入字符)\n");

    printf("11.删除目录----------------------deldir--(deldir + 空格 + 目录名)\n");

    printf("12.进入当前目录下的指定目录-------cd--------(cd + 空格 + 目录名)\n");

    printf("13.返回上一级目录-----------------cd.. \n");

    printf("14.显示帮助命令-----------------help \n");

    printf("15.退出文件系统------------------quit \n");

    printf("16.退出登录-------------------logout \n");
}

int main() //主函数
{
    char tmp[10], com[10], tmp1[10];
    struct command tmp2[10];
    int i, j = 0, p, len = 0;
    FILE *fp;
    login();
    //printf("loginid %d\n",login_userid);
    help();
    strcpy(cmd[0].com, "format"); //将各个命令存进命令表
    strcpy(cmd[1].com, "dir");
    strcpy(cmd[2].com, "cat");
    strcpy(cmd[3].com, "ls");
    strcpy(cmd[4].com, "md");
    strcpy(cmd[5].com, "vi");
    strcpy(cmd[6].com, "del");
    strcpy(cmd[7].com, "deldir");
    strcpy(cmd[8].com, "cd");
    strcpy(cmd[9].com, "cd..");
    strcpy(cmd[10].com, "help");
    strcpy(cmd[11].com, "quit");
    strcpy(cmd[12].com, "open");
    strcpy(cmd[13].com, "read");
    strcpy(cmd[14].com, "write");
    strcpy(cmd[15].com, "logout");
    strcpy(cmd[16].com, "close");

    if ((fp = fopen("system", "rb")) == NULL) //判断系统文件是否存在
    {
        printf("can not open file\n");
        printf("format the disk \n");
        Sleep(500);
        format();
    } else {
        read_file(fp); //读取系统文件的内容
    }

    while (1) {
        j = 0; //必须重新给恢复0否则出错
        strcpy(tmp, cur_dir);

        while (strcmp(tmp, "filesystem") != 0) {

            for (i = 0; i < 640; i++) {

                p = root[i].i_numl;

                if (strcmp(tmp, root[i].file_name) == 0 && (i_node[p].file_style == 0)) {

                    strcpy(tmp2[j].com, tmp);

                    j++;

                    strcpy(tmp, root[i].dir_name);
                }
            }
        }

        strcpy(tmp2[j].com, tmp);

        for (i = j; i >= 0; i--) {

            printf("%s/", tmp2[i].com);
        }

        scanf("%s", com); //输入命令并且查找命令的相关操作

        for (i = 0; i < 17; i++) {

            if (strcmp(com, cmd[i].com) == 0) {

                p = i;

                break;
            }
        }
        if (i == 17) //如果没有这个语句以后输入的命令都和第一次输入的效果一样
        {
            p = -1; //随便的一个值
        }
        switch (p) {
            case 0:
                format(); //初始化
                break;
            case 1:
                display_curdir(); //查看当前目录下的文件列表
                break;
            case 2:
                scanf("%s", tmp); //查看文件
                show_file(tmp);
                break;
            case 3:
                display_sys(); //查看系统信息
                break;
            case 4:
                scanf("%s", tmp); //创建目录
                create_dir(tmp);
                break;
            case 5:
                scanf("%s", tmp); //创建文件
                scanf("%d", &len);
                int limit;
                scanf("%d", &limit);
                create_file(tmp, len, login_userid, limit);
                break;
            case 6:
                scanf("%s", tmp); //删除文件
                for (i = 0; i < 640; i++) //判断文件是不是正规文件
                {
                    j = root[i].i_numl;
                    if (strcmp(tmp, root[i].file_name) == 0 && (i_node[j].file_style) == 1) {
                        del_file(tmp);
                        break;
                    }
                }
                if (i == 640) {
                    printf("这个不是正规文件文件\n");
                }
                break;
            case 7:
                scanf("%s", tmp); //删除目录
                del_dir(tmp);
                break;
            case 8:
                scanf("%s", tmp1); //进入当前目录下的指定目录 相当于进入目录 cd +目录名
                display_dir(tmp1);
                break;
            case 9:
                back_dir(); //返回上一级目录
                break;
            case 10:
                help();
                break;
            case 11:
                write_file(fp); //将磁盘利用信息写进系统文件，退出
                return 0;
            case 12:
                scanf("%s", tmp);
                open(tmp);
                break;

            case 13:
                scanf("%s", tmp);
                read(tmp);
                break;
            case 14:
                scanf("%s", tmp);
                char writec;
                getchar();
                scanf("%c", &writec);
                getchar();
                // printf("tmp=%s writec=%c\n",tmp,writec);
                write(tmp, writec);
                // printf("retuern here?");
                break;
            case 15:
                write_file(fp);

                logout();
                int l;
                for (l = 0; l < 8; l++) {
                    filearray[l] = -1;
                }
                file_array_head = 0;
                login();
                help();
                break;
            case 16:
                scanf("%s", tmp);
                close(tmp);
                break;
            default:
                printf("SORRY,没有这个命令\n");
                break;
        }
    }
    return 0;
}
