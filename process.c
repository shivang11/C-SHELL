#include"headers.h"

int call_process(char **str)
{

    ll i=0,flag=0,ret=0;

    char **st;
    ll sz=100;
    st=(char **)malloc(sz*sizeof(char *));

    while(str[i]!=NULL)
    {
        if(str[i][0]!='&')
        st[i]=str[i];
        else
        {
            flag=1;
            break;
        }
        ll l=strlen(st[i]);
       i++;
    }

    if(flag==0)
    {
         int pip[2];
        // foreground process
        pipe(pip);
        int pid=fork();
        if(pid==-1)
        {
            ret=1;
            return ret;
        }
        store[c1]=pid;
        c1++;

        if(pid==0)
        {
            setpgid(0,0);
            if(execvp(st[0],st)==-1)
            {
                int orig1,orig2;

                printf("command doesn't exist\n");
                close(pip[0]);
                write(pip[1],"1",2);
                close(pip[1]);
            }
            exit(0);
        }
        else
        {
            int status,ch;
            fg_pid=pid;
        //    signal(SIGTSTP,fg_handle1);
        //    signal(SIGINT,fg_handle2);
            signal(SIGTTIN, SIG_IGN);

               signal(SIGTTOU, SIG_IGN);
               tcsetpgrp(STDIN_FILENO, pid);
            waitpid(pid,&status,WUNTRACED);
            
            int p;
            char buff[10];
            


            if(strcmp(buff,"1")==0)
            ret=1;

            tcsetpgrp(STDIN_FILENO, getpgrp());
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);
            if(WIFSTOPPED(status))
            {
                ret=1;
                job[jb]=fg_pid;
                ll sz=300;
                job_name[jb]=(char *)malloc(sz);
                strcpy(job_name[jb],str[0]);
                ll k=1;
              //  printf("%s\n",str[k]);
                while(str[k]!=NULL)
                {
                    strcat(job_name[jb]," ");
                    strcat(job_name[jb],str[k]);
                    k++;
                }
                jb++;
                fg_flag1=0;
		return ret;
            }
		if(status>0)
            ret=1;

		close(pip[1]);
            ll sz=read(pip[0],&buff,2);
            close(pip[0]);
        }
    }
    else
    {
        // background process
         int pip[2];
        pipe(pip);
        int pid=fork();
        if(pid==-1)
        {
            ret=1;
            return ret;
        }
        store[c1]=pid;
        c1++;
        if(pid==0)
        {
            setpgid(0,0);
            if(execvp(st[0],st)==-1){
            printf("command doesn't exist\n");
            }

            exit(0);

        }
        else
        {
            ll sz=200;
            job_name[jb]=(char *)malloc(sz);
            strcpy(job_name[jb],str[0]);
            ll k=1;
            while(str[k]!=NULL && strcmp(str[k],"&")!=0)
            {
                strcat(job_name[jb]," ");
                strcat(job_name[jb],str[k]);
                k++;
            }
            job[jb]=pid;
            jb++;
        }

    }
    return ret;
}
