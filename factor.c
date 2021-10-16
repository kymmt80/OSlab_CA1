#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define MAX_NUM 100

int
itos(int num,char* res){
    int i=0,j=0;
    int rem;
    char rnum[MAX_NUM];

    while(num>0){
        rem=num%10;
        rnum[j]=rem+'0';
        num/=10;
        j++;
    }
    rnum[j]='\0';
    j--;
    while(j>=0){
        res[i]=rnum[j];
        j--;
        i++;
    }
    res[i]='\0';
    return i;
}


void
factor_to_file(int fd,int num){
    int i,size;
    char c[MAX_NUM];
    for(i=1;i<=num;i++){
        if(num%i==0){
            size=itos(i,c);
            if(write(fd,c,size*sizeof(char))!=size*sizeof(char)){
                printf(0,"factor: writing error\n");
            }
            if(write(fd," ",sizeof(char))!=sizeof(char)){
                printf(0,"factor: writing error\n");
            }
        }
    }
    write(fd,"\n",sizeof(char));
}

int
stoi(char* cnum){
    int i=0;
    int num=0;
    while(i!=strlen(cnum)){
        num=num+(cnum[i]-'0');
        num=num*10;
        i++;
    }
    return num/10;
}


int
main(int argc, char *argv[])
{
    int fd;
    char* cnum=argv[1];
    int num=stoi(cnum);
    if(argc<=1){
        exit();
    }

    if((fd=open("factor_result.txt",O_CREATE|O_WRONLY))<0){
        printf(0,"factor: cannot open ‫‪factor_result.txt‬‬\n");
        exit();
    }
    
    factor_to_file(fd,num);
    close(fd);
    exit();
}