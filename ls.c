#include"headers.h"

char *get_permission(char *str)
{
    struct stat seek;
    stat(str,&seek);

    char *temp;
    ll sz=200;
    temp=(char *)malloc(sz);

    if(S_ISDIR(seek.st_mode))
    {temp[0]='d';}
    else temp[0]='-';

    if(seek.st_mode & S_IRUSR)
    {temp[1]='r';}
    else temp[1]='-';
    if(seek.st_mode & S_IWUSR)
    {temp[2]='w';}
    else temp[2]='-';
    if(seek.st_mode & S_IXUSR)
    {temp[3]='x';}
    else temp[3]='-';


    if(seek.st_mode & S_IRGRP)
    temp[4]='r';
    else temp[4]='-';
    if(seek.st_mode & S_IWGRP)
    temp[5]='w';
    else temp[5]='-';
    if(seek.st_mode & S_IXGRP)
    temp[6]='x';
    else temp[6]='-';


    if(seek.st_mode & S_IROTH)
    temp[7]='r';
    else temp[7]='-';
    if(seek.st_mode & S_IWOTH)
    temp[8]='w';
    else temp[8]='-';
    if(seek.st_mode & S_IXOTH)
    temp[9]='x';
    else temp[9]='-';

    temp[10]='\0';
    return temp;
}

int print_ls(char *str,ll fl1,ll fl2,ll k)
{
    ll ret=0;
    if(k>1)
    printf("%s:\n",str);
    if(fl1 && fl2)
    {
       DIR *direct=opendir(str);
       if(direct==NULL)
       {
           printf("Directory Not Found\n");
           return 1;
       }
       struct dirent *dr;
       while((dr=readdir(direct))!=NULL)
       {
           // permissions
           // get dir absolute path

           char temp[2000],*temp1;
           struct stat buff;
           strcpy(temp,str);
           strcat(temp,"/");
           strcat(temp,dr->d_name);
           stat(temp,&buff);
           temp1=get_permission(temp);
           printf("%s ",temp1);

            // hardlink number
            printf("%ld ",buff.st_nlink);

            //user
            char *user=getpwuid(buff.st_uid)->pw_name;
            printf("%s  ",user);
            // group
            char *group=getgrgid(buff.st_gid)->gr_name;
            printf("%s  ",group);

            printf("%ld  ",buff.st_size);

            char tm[200];
            strftime(tm, 200, "%b %d %H:%M" , localtime(&(buff.st_ctime)));
            printf("%s  ",tm);

            printf("%s",dr->d_name);
            printf("\n");
       }
    }
    else if(fl1)
    {
        DIR *direct=opendir(str);
        if(direct==NULL)
       {
           printf("Directory Not Found\n");
           return 1;
       }
       struct dirent *dr;
       while((dr=readdir(direct))!=NULL)
       {
           if(strcmp(dr->d_name,".")==0 || strcmp(dr->d_name,"..")==0)
           continue;
           // permissions
           // get dir absolute path

           char temp[2000],*temp1;
           struct stat buff;
           strcpy(temp,str);
           strcat(temp,"/");
           strcat(temp,dr->d_name);

           stat(temp,&buff);
           temp1=get_permission(temp);

           printf("%s ",temp1);

            // hardlink number
            printf("%ld ",buff.st_nlink);

            //user
            char *user=getpwuid(buff.st_uid)->pw_name;
            printf("%s  ",user);
            // group
            char *group=getgrgid(buff.st_gid)->gr_name;
            printf("%s  ",group);

            printf("%ld  ",buff.st_size);

            char tm[200];
            strftime(tm, 200, "%b %d %H:%M" , localtime(&(buff.st_ctime)));
            printf("%s  ",tm);

            printf("%s",dr->d_name);
            printf("\n");
       }
    }
    else if(fl2)
    {
          DIR *direct=opendir(str);
          if(direct==NULL)
       {
           printf("Directory Not Found\n");
           return 1;
       }
       struct dirent *dr;
       while((dr=readdir(direct))!=NULL)
       {

            printf("%s  ",dr->d_name);
       }
       printf("\n");
    }
    else
    {
          DIR *direct=opendir(str);
        if(direct==NULL)
        {
            printf("Directory Not Found\n");
            return 1;
        }
       struct dirent *dr;
       while((dr=readdir(direct))!=NULL)
       {
           if(strcmp(dr->d_name,".")==0 || strcmp(dr->d_name,"..")==0)
           continue;
            printf("%s   ",dr->d_name);
       }
       printf("\n");
    }
    return ret;
}
int call_ls(char **str)
{
    // check for l and a;
    // path is cwd
    char *dir[200];
    dir[0]=".";
    ll i=1,pr_a=0,pr_l=0,k=0;
    while(str[i]!=NULL)
    {
        if(str[i][0]=='-')
        {
            ll st=strlen(str[i]);
            for(int j=0;j<st;j++)
            {
                if(str[i][j]=='l')
                pr_l=1;
                else if(str[i][j]=='a')
                pr_a=1;
            }
        }
        else if(str[i][0]=='~')
        {
            char temp[200];
            strcpy(temp,root);
     //       printf("%s\n",temp);
            ll sz=strlen(root);
            for(int j=1;j<strlen(str[i]);j++)
            {
                temp[sz]=str[i][j];
                sz++;
            }

            temp[sz]='\0';
            dir[k]=temp;
            k++;
        }
        else
        {
            dir[k]=str[i];
            k++;
        }
        i++;
    }

  // printf("%s\n",dir[0]);
    i=0;
    ll ret=0;
    while(dir[i]!=NULL)
    {
        ll b=print_ls(dir[i],pr_l,pr_a,k);
        if(b==1)
        ret=1;
        i++;
        if(i>=k)
        break;
    }

    return ret;

}
