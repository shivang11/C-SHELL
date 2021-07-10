#include"headers.h"

int call_history()
{
    char temp[200],buff[200];
    ll sz=1000,ret=0;
    strcpy(temp,root);
    strcat(temp,"/");
    strcat(temp,"history.txt");
    temp[strlen(temp)]='\0';

    int fd=open(temp,O_RDONLY);

    // int c=lseek(fd,0,SEEK_END);
    // lseek(fd,0,SEEK_SET);

    read(fd,buff,sz);
    ll len=strlen(buff);

    for(int i=0;i<len;i++)
    {
        printf("%c",buff[i]);
    }
    return ret;

}
