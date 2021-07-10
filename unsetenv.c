#include"headers.h"

int call_unsetenv(char **str)
{
    ll ret=0;
    if(str[1]==NULL || str[2]!=NULL)
    {
        printf("Invalid number of commands\n");
        ret=1;
    }
    else
    {
        if(unsetenv(str[1])==-1)
        {
            printf("unsetenv failed:");
            return 1;
        }
    }
    return ret;
}
