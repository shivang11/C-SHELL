#include"headers.h"

int call_cd(char **str)
{
    ll ret=0;
    if(str[1]==NULL)
    {
        if(strlen(str[0])==2)
        {
            strcpy(old_path,path);
            strcpy(path,root);
            j=strlen(path);
            path[j]='\0';
            chdir(path);
        }
        else
        {
            printf("%s : command not found\n",str[0]);
            ret=1;
            return ret;
        }

    }
    else if(str[1][0]=='~')
    {
        strcpy(old_path,path);
        strcpy(path,root);
        if(strlen(str[1])>1)
        {
            strcat(path,"/");
        }
        j=strlen(path);
        for(int i=1;i<strlen(str[1]);i++)
        {
            path[j]=str[1][i];
            j++;
        }
        path[j]='\0';
        chdir(path);
    }
    else if(strcmp(str[1],"-")==0)
    {
        if(cd_cnt==0)
        {
            printf("%s\n",path);
            return 0;
        }
        else
        {
            char temp[200];
            if(chdir(old_path)==-1)
            {
                printf("unable to switch directory\n");
                return 1;
            }
            printf("%s\n",old_path);
            strcpy(old_path,path);
            getcwd(temp,sizeof(temp));
            strcpy(path,temp);
            j=strlen(path);
            path[j]='\0';
        }
    }
    else
    {
        char temp[200];
        strcpy(old_path,path);
        if(chdir(str[1])==-1)
        {
            printf("%s:No such file or directory\n",str[1]);
            return 1;
        }
        else{
       getcwd(temp,sizeof(temp));
       strcpy(path,temp);
       j=strlen(path);
       path[j]='\0';}
    }
    cd_cnt=1;
    return ret;
}
