#include "headers.h"

void showprompt()
{
    char *user;
    char sys[300];

    if(start==0)
    {
        user=getenv("USER");
        ll z=gethostname(sys,200);
        if(strcmp(path,root)==0)
        printf("%s@%s:~>",user,sys);
        else if(strlen(path)<strlen(root))
        {
            printf("%s@%s:%s>",user,sys,path);
        }
        else
        {
            char temp[200];
            ll j=0,y=0;
        ll sz=strlen(root);
            while(path[j]==root[j])
            {
                if(j==strlen(root)-1)
                {
                    y=1;
                    break;
                }
                j++;
            }
            if(y==0)
            {
                printf("%s@%s:%s>",user,sys,path);
            }
            else{
            temp[0]='~';
            temp[1]='/';
            ll sz=strlen(root),k=1,i=2;
            while(1)
            {
                if(sz+k>=strlen(path))
                break;
                temp[i]=path[sz+k];
                i++;
                k++;
            }
            temp[i]='\0';
            strcpy(path,temp);
            printf("%s@%s:%s>",user,sys,path);}
        }
        start=1;
    }
    else
    {
        user=getenv("USER");
        ll z=gethostname(sys,200);
        if(strcmp(path,root)==0)
        printf("%s%s@%s:~>",pro_str,user,sys);
        else if(strlen(path)<strlen(root))
        {
            printf("%s%s@%s:%s>",pro_str,user,sys,path);
        }
        else
        {
            char temp[200];
            ll j=0,y=0;
        ll sz=strlen(root);
            while(path[j]==root[j])
            {
                if(j==strlen(root)-1)
                {
                    y=1;
                    break;
                }
                j++;
            }
            if(y==0)
            {
                printf("%s%s@%s:%s>",pro_str,user,sys,path);
            }
            else{
            temp[0]='~';
            temp[1]='/';
            ll sz=strlen(root),k=1,i=2;
            while(1)
            {
                if(sz+k>=strlen(path))
                break;
                temp[i]=path[sz+k];
                i++;
                k++;
            }
            temp[i]='\0';
            strcpy(path,temp);
            printf("%s%s@%s:%s>",pro_str,user,sys,path);}
        }
    }
}
