/* Author: Chandan Chugani
// Date: March 24th, 2015 
// Professor: Leon King
// Description: This program reads a group from /etc/group 
//	looks it up in /etc/passwd and if it exists writes 
//	to a file called users.txt.No errors to report,however
//	if you load no argv, program will seg fault...
//	View this repository on gitHub!
//
// GitHub: https://github.com/DanChugani/unixLab4 
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
 int i=0;
 char buffer[512];
 char *pos;

 fp= fopen("idontknow.txt","r");
 while(fgets(buffer,sizeof(buffer),(FILE*)fp) != NULL)
 {
  buffer[strlen(buffer)-1]='\0'; 
  //fprintf(stdout,"\n%s",buffer);
  wordexp(buffer, &result,WRDE_SHOWERR );
   pid = fork();
 	if (pid==0)
 	{
	//printf("we_wordv[0]: %s\n",result.we_wordv[2]);
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