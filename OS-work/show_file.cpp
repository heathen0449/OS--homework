#include "File.h"

void show_file(char filename[]){
    //extern dir root[640];
    //extern node i_node[640];
    int i,j,k;
    cout<<"\t\t 文件名字 \t 文件类型 \t 文件长度 \t 所属目录 \t 所属用户 \n";
    for(i=0;i<640;i++){
        k=root[i].i_numl;
        if (strcmp(filename,root[i].file_name)&&(i_node[k].file_style==1)){
            cout<<"\t"<<root[i].file_name<<"\t"<<i_node[k].file_style;
            cout<<"\t"<<i_node[k].file_length<<"\t"<<i_node[k].limit;
            cout<<"\t"<<root[i].dir_name<<"\t";
            cout<<"\t user"<<i_node[root[i].i_numl].file_UserId<<endl;
            cout<<"\t\t文件占用的物理地址"<<endl;
            for(j=0;j<i_node[k].file_length;j++){
                cout<<i_node[k].file_address<<" ";
            }
            cout<<endl;
            break;
        }

    }
    if(i==640)
        cout<<"没有这个文件或者这个文件不是正规文件";
}

//格式化函数

void format(){
     int i,j,k;
    super_block.n=50;
    for(i=0;i<50;i++){
        super_block.free[i]=i;
        super_block.empty_block[i]=50+i;//存放下一组的盘块
    }
    for(i=0;j<640;i++){
        for (j=0;j<100;j++){
            i_node[i].file_address[j]=-1;
        }
        i_node[i].limit=-1;
        i_node[i].file_style=-1;
        i_node[i].file_UserId=-1;
    }
    for (i=0;i<640;i++){
        strcpy(root[i].file_name,"");
        root[i].i_numl=-1;
        strcpy(root[i].dir_name,"");
    }
    for(i=0;i<20449;i++){
        memory[i].number=0;
        memory[i].is_use=0;
        for(j=0;j<50;j++)
            memory[i].free[j]=-1;
        for(int c=0;c<1000;c++)
            memory[i].content[c]='\0';
    }
    for(i=0;i<20449;i++){
        if((i+1)%50==0){  //成组链接法超级快初始化
            k=i+1;
            for(j=0;j<50;j++){
                if(k<20450){
                    memory[i].free[j]=k;
                    memory[i].number++;
                    k++;
                }
                else{
                    memory[i].free[j]=-1;
                }
            }
            memory[i].is_use=0;
            continue;
        }
        for (j=0;j<50;j++){
            memory[i].free[j]=-1;
        }
        memory[i].number=0;
    }
    extern int filearray[8];
    for(int l=0;l<8;l++){
            filearray[l]=-1;
    }
    extern int file_array_head;
    file_array_head=0;
    extern int physic[100];
    for(int u=0;u<100;u++)
        physic[u]=-1;
    cout<<"初始化已完毕"<<endl;
    cout<<"欢迎进入文件系统"<<endl<<endl;
}


void write_file(FILE *fp){
    int i;
    fp = fopen("system","wb");
    for(i=0;i<20449;i++){
        fwrite(&memory[i],sizeof(struct block),1,fp);
    }
    fwrite(&super_block,sizeof(struct block_super),1,fp);
    for(i=0;i<640;i++){
        fwrite(&i_node[i],sizeof(struct node),1,fp);
    }
    for(i=0;i<640;i++)
        fwrite(&root[i],sizeof(struct dir),1,fp);
    fclose(fp);
}


void read_file(FILE*fp){
    int i;
    fp = fopen("system","wb");
    for(i=0;i<20449;i++){
        fread(&memory[i],sizeof(struct block),1,fp);
    }
    fread(&super_block,sizeof(struct block_super),1,fp);
    for(i=0;i<640;i++){
        fread(&i_node[i],sizeof(struct node),1,fp);
    }
    for(i=0;i<640;i++)
        fread(&root[i],sizeof(struct dir),1,fp);
    fclose(fp);
}
