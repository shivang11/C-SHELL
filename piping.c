#include"headers.h"

int piping(char **str)
{
    ll i=0,last=0,p=0,ret=0;
    char *comm[200];
    ll store_out,store_in;
    while(str[i]!=NULL)
    {
        ll k=0;
        ret=0;
        p++;

        int pipfd[2];
        while(strcmp(str[i],"|")!=0)
        {
            comm[k]=str[i];
            k++;
            i++;
            if(str[i]==NULL)
            {
                last=1;
                i--;
                break;
            }
        }

        comm[k]=NULL;
        i++;
        ll flag=0,rd4=0;
        char *command[200];
        char out[200],inp[200];
        if(p==1)
        {
            if(pipe(pipfd)==-1)
            {
                printf("piping error\n");
                return 1;
            }
            store_out=dup(1);
            store_in=dup(0);

            k=0;
            ll redir=0;
            while(comm[k]!=NULL)
            {
                ///////// middle file handling should be done here
                if(strcmp(comm[k],"<")==0)
                {
                    redir++;
                    strcpy(inp,comm[k+1]);

                    command[k]=NULL;
                }
                else
                {
                    command[k]=comm[k];
                }
                k++;
            }
            command[k]=NULL;

            if(redir>0)
            {
                int fd1=open(inp,O_RDONLY);
                if(fd1==-1)
                {
                    printf("file doesn't exist\n");
                    return 1;
                }
                dup2(fd1,0);
            }
            dup2(pipfd[1],1);
            close(pipfd[1]);
        }
        else if(last==0)
        {
            k=0;
             store_in=dup(0);
             dup2(pipfd[0],0);
            while(comm[k]!=NULL)
            {
                command[k]=comm[k];
                k++;
            }
            command[k]=NULL;
            if(pipe(pipfd)==-1)
            {
                perror("piping error");
                return 1;
            }

            store_out=dup(1);
            dup2(pipfd[1],1);

            close(pipfd[1]);
        }
        else
        {
            k=0;
            flag=0;
            store_in=dup(0);
            store_out=dup(1);

            while(comm[k]!=NULL)
            {
                if(strcmp(comm[k],">")==0 || strcmp(comm[k],">>")==0)
                {
                    strcpy(out,comm[k+1]);
                    if(strcmp(comm[k],">")==0)
                    rd4=1;
                    else
                    {
                        rd4=2;
                    }
                    command[k]=NULL;
                }
                else
                {
                    command[k]=comm[k];
                }
                k++;
            }
            command[k]=NULL;
            if(rd4==1)
            {
                dup2(pipfd[0],0);
                int fd1=open(out,O_WRONLY|O_CREAT|O_TRUNC,0644);
                dup2(fd1,1);
            }
            else if(rd4==2)
            {
                dup2(pipfd[0],0);
                int fd1=open(out,O_WRONLY|O_CREAT|O_APPEND,0644);
                dup2(fd1,1);
            }
            else
            {
                dup2(pipfd[0],0);

            }
            close(pipfd[0]);

        }
        int pip[2];
        pip[0]=0;
        pip[1]=0;
        pipe(pip);
        int pid=fork();
        if(pid==-1)
        {
            printf("error\n");
            return 1;
        }
        else if(pid==0)
        {
            if(execvp(command[0],command)==-1)
            {
                close(pip[0]);
                write(pip[1],"1",2);
                close(pip[1]);
                perror("command not found :");
                exit(EXIT_FAILURE);
            }
           // exit(0);
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

            dup2(store_in,0);
            dup2(store_out,1);

        }
    }
    return ret;
}
