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


}

