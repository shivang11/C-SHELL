#include"headers.h"

int call_setenv(char **str)
{
    ll ret=0;
    if(str[1]==NULL)
    {
        printf("Inappropriate no. of commands\n");
        return 1;
    }
    else if(str[3]!=NULL)
    {
        printf("Excess commands\n");
        return 1;
    }

    if(str[2]==NULL)
    {
        if(setenv(str[1],"",1)==-1)
        {
            perror("setenv:");
            return 1;
        }
    }
    else
    {
        if(setenv(str[1],str[2],1)==-1)
        {
            perror("setenv:");
            return 1;
        }
    }
    return ret;
}
