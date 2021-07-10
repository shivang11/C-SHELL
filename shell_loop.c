#include"headers.h"
#include"parse.c"
#include"cd.c"
#include"echo.c"
#include"pinfo.c"
#include"history.c"
#include"pwd.c"
#include"process.c"
#include"ls.c"
#include"prompt.c"
#include"piping.c"
#include"redirect.c"
#include"overkill.c"
#include"kjob.c"
#include"jobs.c"
#include"setenv.c"
#include"unsetenv.c"
#include"quit.c"
#include"fg.c"
#include"bg.c"
int execute(char **str)
{

    char *temp;
    temp=str[0];
    ll i=0,pip=0,red=0,res;
    while(str[i]!=NULL)
    {
        if(strcmp(str[i],"|")==0)
        pip++;
        if(strcmp(str[i],"<")==0 || strcmp(str[i],">>")==0 || strcmp(str[i],">")==0)
        red++;

        i++;
    }
    if(temp==NULL)
    {
        return 0;
    }
    else if(pip>0)
    {
        res=piping(str);
    }
    else if(red>0)
    {
        res=redirect(str);
    }
    else if(strcmp(temp,"history")==0)
    {
         res=call_history();
    }
    else if(strcmp(temp,"echo")==0)
    {
         res=call_echo(str);
    }
    else if(strcmp(temp,"pwd")==0)
    {
         res=call_pwd(str);
    }
    else if(temp[0]=='c' && temp[1]=='d')
    {
         res=call_cd(str);
    }
    else if(strcmp(temp,"ls")==0)
    {
         res=call_ls(str);
    }
    else if(strcmp(temp,"pinfo")==0)
    {
         res=call_pinfo(str);
    }
    else if (strcmp(temp,"setenv")==0)
    {
         res=call_setenv(str);
    }
    else if(strcmp(temp,"unsetenv")==0)
    {
         res=call_unsetenv(str);
    }
    else if (strcmp(temp,"jobs")==0)
    {
         res=call_jobs(str);
    }
    else if(strcmp(temp,"kjob")==0)
    {
         res=call_kjob(str);

    }
    else if(strcmp(temp,"quit")==0)
    {
        call_quit(str);

    }
    else if(strcmp(temp,"overkill")==0)
    {
         res=call_overkill(str);
    }
    else if(strcmp(temp,"fg")==0)
    {
         res=call_fg(str);
    }
    else if(strcmp(temp,"bg")==0)
    {
         res=call_bg(str);
    }
    else
    {
        res=call_process(str);
    }
    if(res==0)
    strcpy(pro_str,":')");
    else
    {
       strcpy(pro_str,":'(");
    }
    return res;
}
void signalHandler(int sig)
{
	return ;
}
void make_prompt()
{
    while(1)
    {
        showprompt();
        // ctrl+D
        char *commands[300];
        char **fir_command;
        char *buffer ;
        char *buffer2 ;
        int symbol[200]={0};
        size_t size =100;
        buffer =(char *)malloc(size);
        buffer2 =(char *)malloc(size);

        /////////////////////////////////

        signal(SIGINT, signalHandler);
		signal(SIGTSTP, signalHandler);

        getline(&buffer,&size,stdin);
        strcpy(buffer2,buffer);


      //  printf("%d\n",c);
      // buffer[strlen(buffer)]='\0';
        int status;
        int pid=waitpid(-1,&status,WNOHANG);

        // if(pid > 0)
        // {
        //     if(!WIFEXITED(status))
        //     {
        //         for(int i = 0;i < 800;i++)
        //         {
        //             if(store[i] == pid)
        //                 store[i] = -1;
        //         }
        //         printf("Process with pid %d exited : %d\n", pid, WEXITSTATUS(status));
        //     }
        // }

        // for(int i = 0;i < 800;i++)
        // {
        //     if(store[i]>0)
        //     {
        //         if(kill(store[i], 0) == -1)
        //         {
        //             printf("Process with pid %lld exited successfully\n",store[i]);
        //             store[i] = -1;
        //         }
        //     }
        // }

        strcpy(hst[c2],buffer2);

        c2++;

        if(c2>20)
        {
            for(int i=0;i<=19;i++)
            {
                strcpy(hst[i],hst[i+1]);
            }
            c2=20;
        }

        char temp[200];
        ll sz=1000;
        strcpy(temp,root);
        strcat(temp,"/");
        strcat(temp,"history.txt");
        temp[strlen(temp)]='\0';

         int fd=open(temp,O_WRONLY|O_CREAT | O_TRUNC,0777);

        for(int i=0;i<c2;i++)
        {
            write(fd,hst[i],strlen(hst[i]));
        }

        command_parse(buffer,commands);

        // got commands[i] after removing semicolon
        for(int i=0;commands[i]!=NULL;i++)
        {
            // parse with @ or $
            int p=0;
            for(int k=0;k<strlen(commands[i]);k++)
            {
                if(commands[i][k]=='@'){
                symbol[p]=1;
                p++;}
                else if(commands[i][k]=='$'){
                symbol[p]=2;
                p++;}

            }
            fir_command=removsym(commands[i]);
            for(int j=0;fir_command[j]!=NULL;j++)
            {
                // remove spaces
                char **get_command;
                get_command=rem_space(fir_command[j]);

                // execute get_command
                ll res=execute(get_command);
                if(symbol[j]==1 && res==1)
                j++;
                else if(symbol[j]==2 && res==0)
                j++;
            }
        }
        //  for(int i=0;i<c2;i++)
        // printf("%s\n",hst[i]);
    }
}
