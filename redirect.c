#include"headers.h"

int redirect(char **str)
{

    ll i=0,rd1=0,rd2=0,rd3=0,rd4=0,org,org2,ret=0;
    while(str[i]!=NULL)
    {
        if(strcmp(str[i],"<")==0)
        rd1=1;
        if(strcmp(str[i],">")==0)
        rd2=1;
        if(strcmp(str[i],">>")==0)
        rd3=1;
        i++;
    }
    // get input file
    i=0;
    char inp[200],out[200];
    char *comm[200];
    ll flag=0;
    while(rd1==1 && str[i]!=NULL)
    {
        if(strcmp(str[i],"<")==0)
        {
            strcpy(inp,str[i+1]);
            if(flag==0)
            {
                comm[i]=NULL;
                flag=1;
            }
        }
        else if(flag==0)
        {
            comm[i]=str[i];
        }
        i++;

    }

    //printf("d  %lld %lld\n",rd2,rd3);
    // get output file
    i=0;
    while((rd2==1 || rd3==1) && str[i]!=NULL)
    {
        if(strcmp(str[i],">")==0 || strcmp(str[i],">>")==0)
        {
            strcpy(out,str[i+1]);
            if(strcmp(str[i],">")==0)
            rd4=1;
            else
            {
                rd4=2;
            }
            if(flag==0 && rd1==0)
            {
                comm[i]=NULL;
                flag=1;
            }
        }
        else if(flag==0 && rd1==0)
        {
            comm[i]=str[i];
        }
        i++;
    }
     org=dup(0);
    // change stdin to inp
    int fd1;
    if(rd1==1)
    {
        fd1=open(inp,O_RDONLY,0644);
        if(fd1==-1)
        {
            perror(inp);
            return 1;
        } org=dup(0);
        dup2(fd1,0);
    }

     org2=dup(1);
    // change stdout to out
    if(rd2 || rd3)
    {
        int fd2;
        if(rd4==1)
        {
            fd2=open(out,O_WRONLY|O_CREAT|O_TRUNC,0644);
        }
        else
        {
            fd2=open(out,O_WRONLY|O_CREAT|O_APPEND,0644);
        }
        if(fd2==-1)
        {
            perror("failed to create file\n");
            return 1;
        }
        dup2(fd2,1);

    }
    int pip[2];
    pipe(pip);
    int pid=fork();
    if(pid==-1)
    {
        printf("error in redirection");
        return 1;
    }
    if(pid==0)
    {
        if(execvp(comm[0],comm)==-1)
        {
                close(pip[0]);
                write(pip[1],"1",2);
                close(pip[1]);
                perror("command not found :");
                exit(EXIT_FAILURE);

        }
    }
    else
    {
        int status=0;
        waitpid(pid,&status,WUNTRACED);

        if(status>0)
        ret=1;
        char buff[10];
            close(pip[1]);
            ll sz=read(pip[0],&buff,2);
            close(pip[0]);

        if(strcmp(buff,"1")==0)
        ret=1;
        dup2(org,0);
        dup2(org2,1);
    }
    return ret;
}
