#include"headers.h"
#include"shell_loop.c"

int main()
{
    getcwd(root,sizeof(root));
    strcpy(path,root);

    for(int i=0;i<800;i++)
    {
        store[i]=-1;
    }
    for(int i=0;i<=10000;i++)
    {
        job[i]=-1;
    }
  //  printf("%s\n",path);
      char temp[200],buff[2000];
        ll sz=1000;
        strcpy(temp,root);
        strcat(temp,"/");
        strcat(temp,"history.txt");
        temp[strlen(temp)]='\0';

        int fd=open(temp,O_RDONLY);

        // int c=lseek(fd,0,SEEK_END);
        // lseek(fd,0,SEEK_SET);

        read(fd,buff,sz);
        ll len=strlen(buff);


        // printf("%d\n",c);

         char *prv;
        prv=(char *)malloc(sz);



        prv=strtok(buff,"\n");
        for(int i=0;i<=39;i++)
        {
            ll si=200;
            hst[i]=(char *)malloc(si);
        }
        while(prv!=NULL)
        {
            strcpy(hst[c2],prv);
            strcat(hst[c2],"\n");
            c2++;
            prv=strtok(NULL,"\n");
        }

        // check for process execution

        // for(int i=0;i<c2;i++)
        // {
        //     printf("%s",hst[i]);
        // }
        close(fd);
        make_prompt();
}
