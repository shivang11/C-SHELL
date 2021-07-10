#include"headers.h"

int call_pinfo(char **str)
{
    ll ret=0;
    char pid[200];
    if(str[1]!=NULL)
    {
        strcpy(pid,str[1]);
       // pid[strlen(pid)]='\0';
    }
    else
    {
        sprintf(pid, "%d", getpid());
      // pid[i]='\0';
    }
    printf("pid -- %s\n",pid);

    char get_path[200];
    strcpy(get_path,"/proc/");
    strcat(get_path,pid);
    strcat(get_path,"/stat");

    FILE *f=fopen(get_path,"r");
    char data[2000];

    if(f!=NULL)
    {
        ll sz=fread(data,1,2000,f);
    }
    else
    {
        printf("File couldn't be opened\n");
        return 1;
    }

    char **temp;
    char *temp2;
    ll sz=2000;
    temp=(char **)malloc(sz*sizeof(char *));

    temp2=strtok(data," \n\r\t");
    int i=0;
    while(temp2!=NULL)
    {
        temp[i]=temp2;
        i++;
        temp2=strtok(NULL," \n\t\r");
    }
    temp[i]=NULL;

    printf("Process Status -- %s\n",temp[2]);
    printf("memory -- %s\n",temp[22]);

    strcpy(get_path,"/proc/");
    strcat(get_path,pid);
    strcat(get_path,"/exe");

    char *buff;
    buff = (char *)malloc(sz);
    if(readlink(get_path,buff,2000)==-1)
    {
        printf("executable path doesn't exist\n");
        return 1;
    }
    else
    {
        buff[strlen(buff)]='\0';
    }
    printf("Executable Path -- %s\n",buff);

    return ret;
}
