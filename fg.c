#include"headers.h"

void change_jobn(int a)
{
    while(a<jb-1)
    {
        job[a]=job[a+1];
        strcpy(job_name[a],job_name[a+1]);
        a++;
    }
}

int call_fg(char **str)
{
    ll tot=0,i=0,cnt=1,ret=0;
    while(str[i]!=NULL)
    {
        tot++;
        i++;
    }
    if(tot!=2)
    {
        printf("invalid number of commands\n");
        ret=1;
        return ret;
    }
    else
    {
        ll job_num=atoi(str[1]);
        int fl=0;
        for(i=0;i<=10000;i++)
        {
            if(job[i]==-1)
            continue;
            if(cnt==job_num)
            {
                int pid=job[i];
                job[i]=-1;
                char temp[200];
                strcpy(temp,job_name[i]);
                change_jobn(i);
                jb--;
                signal(SIGTTIN, SIG_IGN);
                signal(SIGTTOU, SIG_IGN);
                tcsetpgrp(STDIN_FILENO, pid);
                // signal(SIGINT,sig1);
                // signal(SIGTSTP,sig2);
                kill(pid,SIGCONT);
                int status;
                waitpid(pid,&status,WUNTRACED);
                tcsetpgrp(STDIN_FILENO, getpgrp());
                signal(SIGTTIN, SIG_DFL);
                signal(SIGTTOU, SIG_DFL);

                if(WIFSTOPPED(status))
                {
                    ret=1;
                    job[jb]=pid;
                    ll sz=300;
                    job_name[jb]=(char *)malloc(sz);
                    strcpy(job_name[jb],temp);
                }
                // if(fl==0)
                // job[i]=-1;
                // fl=1;
                fl=1;
                break;
            }
            cnt++;
        }
        if(fl==0)
        {
            printf("invalid job number\n");
            ret=1;
            return ret;
        }
    }
    return ret;
}
