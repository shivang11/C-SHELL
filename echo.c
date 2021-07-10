#include"headers.h"

int call_echo(char **str)
{
    ll i=1;
    while(str[i]!=NULL)
    {
        printf("%s ",str[i]);
        i++;
    }
    printf("\n");
    return 0;
}
