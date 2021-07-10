#include"headers.h"

int call_kjob(char **str)
{
    ll tot=0,i=0,cnt=1,fl=0,ret;

    while(str[i]!=NULL)
    {
        i++;
        tot++;
    }
    if(tot!=3)
    {
        printf("invalid number of commands\n");
        ret=1;
        return ret;
    }
    ll job_num=atoi(str[1]);
    ll sig_num=atoi(str[2]);
    for(i=0;i<=10000;i++)
    {
        if(job[i]==-1)
        continue;
        if(cnt==job_num)
        {
            int kl=kill(job[i],sig_num);
            if(kl==-1)
            {
                printf("signal not valid\n");
                ret=1;
                return ret;
            }
            fl=1;
            job[i]=-1;
            break;
        }
        cnt++;
    }
    if(fl==0)
    {
        printf("No such job number\n");
        ret=1;
        return ret;
    }
    return ret;
}
