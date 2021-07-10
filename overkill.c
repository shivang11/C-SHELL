#include"headers.h"

int call_overkill(char **str)
{
    ll i=0;
    for(i=0;i<=10000;i++)
    {
        if(job[i]!=-1)
        {
            kill(job[i],9);
            job[i]=-1;
        }
    }
    return 0;
}
