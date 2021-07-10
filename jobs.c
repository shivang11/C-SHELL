#include"headers.h"

int call_jobs(char **str)
{
    ll cnt=0,ret=0;
    char spid[200],get_path[200];

    for(int i=0;i<=10000;i++)
    {
        if(job[i]==-1)
        continue;
        cnt++;

        strcpy(get_path,"/proc/");
        sprintf(spid,"%d",job[i]);
        strcat(get_path,spid);
        strcat(get_path,"/stat");

        FILE *f=fopen(get_path,"r");
        char data[2000];

        if(f!=NULL)
        {
            ll sz=fread(data,1,2000,f);
        }
        else
        {
            change_jobn(i);
            job[jb-1]=-1;
            jb--;
            i--;
            cnt--;
           continue;
        }

        printf("[%lld] ",cnt);
        char **temp;
        char *temp2;
        ll sz=2000;
        temp=(char **)malloc(sz*sizeof(char *));

        temp2=strtok(data," \n\r\t");
        int j=0;
        while(temp2!=NULL)
        {
            temp[j]=temp2;
            j++;
            temp2=strtok(NULL," \n\t\r");
        }
        temp[j]=NULL;

        if(strcmp(temp[2],"T")==0)
        printf("Stopped   ");
        else
        {
            printf("Running   ");
        }
        printf("%s [%d]\n",job_name[i],job[i]);
    }
    return 0;
}
