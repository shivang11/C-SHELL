#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include<inttypes.h>

typedef long long ll;
// global arrays
char root[200],path[200];
int job[10005];
char *hst[40],*job_name[1000];
ll store[900],flag2=0,pid2,fpid,jb=0,main_sig=0;
//process
ll fg_flag1=0,fg_pid;
// for fg command
ll fg_sig1=0,fg_sig2=0;
// for cd
char old_path[200];
ll cd_cnt=0;

// global variables
ll c1=0,c2=0,j=0;
char pro_str[100],start=0;

int call_echo(char **str);
int call_history();
int call_pwd(char **str);
int call_cd(char **str);
void showprompt();
char **command_parse(char *buffer , char ** commands);
char **rem_space(char *str);
char **removsym(char *str);
char *get_permission(char *str);
int print_ls(char *str,ll fl1,ll fl2,ll k);
int call_ls(char **str);
int call_pinfo(char **str);
int call_setenv(char **str);
int call_unsetenv(char **str);
void change_jobn(int a);
int call_jobs(char **str);
int call_fg(char **str);
int call_bg(char **str);
int call_kjob(char **str);
int call_process(char **str);
int redirect(char **str);
int piping(char **str);
void call_quit(char **str);
int overkill(char **str);
int execute(char **str);
void signalHandler(int sig);
void make_prompt();
int main();

#endif
