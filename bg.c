#include"headers.h"

int call_bg(char **str)
{
    ll i=0,tot=0,ret=0;
    while(str[i]!=NULL)
    {
        i++;
        tot++;
    }
    if(tot!=2)
    {
        printf("invalid number of commands\n");
        ret=1;
        return ret;
    }
    ll cnt=1,job_num=atoi(str[1]),fl=0;
    for(i=0;i<=10000;i++)
    {
        if(job[i]==-1)
        continue;

        if(job_num==cnt)
        {
            kill(job[i],SIGCONT);
            fl=1;
            break;
        }
        cnt++;
    }
    if(fl==0)
    {
        printf("job number not found\n");
        ret=1;
        return ret;
    }
    return ret;
}
