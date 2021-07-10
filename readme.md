RUNNING THE PROGRAM

1.Go to the working directory and run make
2.use ./shell to start shell

DESCRIPTION OF ALL FILES

1.main.c - main loop and also reading history file for printing it's contents
2.ls.c - ls command
3.pinfo.c - pinfo command
4.prompt.c - printing prompt 
5.shell_loop.c - calling other functions 
6.parse.c - parsing the given commands
7.pwd.c - printing the present working directory
8.history.c - printing the history
9.cd.c - running cd command
10. echo - running echo command
11. process.c - running foreground and background processes
12. bg.c- running stoped background processes
13. fg.c - running the background process 
14.jobs.c - printing all the background jobs
15. kjobs.c - sending a number signal to a job number  
16.overkill.c - kills all the background processes at once
17.quit.c - for quitting the shell
18.redirect.c - implementing the redirection in input
19. piping.c - implementing the piping in input
20 setenv.c - for setting the environment variables
21 unsetenv.c for unsetting the environment variables

ADDITIONAL 
1.history.txt file is created to save the commands that have been run.
