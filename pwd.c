#include"headers.h"

int call_pwd(char **str)
{
    char temp[200];
    getcwd(temp,sizeof(temp));
    printf("%s\n",temp);
    return 0;
}
