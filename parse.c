#include"headers.h"

char **command_parse(char *buffer , char ** commands)
{
    char *command;
    command=strtok(buffer,";");
    ll i=0;
    while(command!=NULL)
    {
        commands[i]=command;
        i++;
        command=strtok(NULL,";");
    }
    commands[i]=NULL;
    return commands;
}
char **rem_space(char *str)
{
    char **temp;
    char *temp2;
    ll sz=500;
    temp=(char **)malloc(sz*sizeof(char *));

    temp2=strtok(str," \n\t\r");
    int i=0;
    while(temp2!=NULL)
    {
        temp[i]=temp2;
        i++;
        temp2=strtok(NULL," \n\t\r");
    }
    temp[i]=NULL;
    return temp;
}

char **removsym(char *str)
{
    char **temp;
    char *temp2;
    ll sz=500;
    temp=(char **)malloc(sz*sizeof(char *));

    temp2=strtok(str,"$@");
    int i=0;
    while(temp2!=NULL)
    {
        temp[i]=temp2;
        i++;
        temp2=strtok(NULL,"$@");
    }
    temp[i]=NULL;
    return temp;
}
