/* Author: Chandan Chugani
** Date: April 8th, 2015 
** Professor: Leon King
** Description:	This little program runs as wrapper
**		program by using the shell times,
**		it records real,user and system times.
**		than creates a child process, which than
**		shifts all arguments over by 1. than terminates
**		This program can measure the amount of time spent
**		by an other program...Amazing I know.
**
**	View this repository on gitHub!
**
** GitHub: https://github.com/DanChugani/unixLab5
*/

#include <stdio.h>
#include <stdlib.h>
#include <wordexp.h>
#include <unistd.h>
#include <fcntl.h>
#include <strings.h>
#include <string.h>

int main()
{
 FILE *fp;
 wordexp_t result;
 pid_t pid;
 int status; 
 char buffer[512];

 fp= fopen("idontknow.txt","r");
 while(fgets(buffer,sizeof(buffer),(FILE*)fp) != NULL)
 {
  buffer[strlen(buffer)-1]='\0'; 
  wordexp(buffer, &result,WRDE_SHOWERR );
   pid = fork();
 	if (pid==0)
 	{
	fprintf(stdout,"\n"); 
	execvp(result.we_wordv[0],result.we_wordv);
	}
	else if(pid<0){
	 status= -1;
	}
	else{
	 if (waitpid (pid,&status,0) !=pid)
	 {
	  status -1;
	 }  
 	} 
  wordfree(&result);
  }
 fclose(fp);
}
