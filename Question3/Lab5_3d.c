/* Author: Chandan Chugani
** Date: April 8th, 2015 
** Professor: Leon King
** Description:	This program allows a user
**		to input a filename and launch 
**		that process. It uses a function called
**		execvpe( const char *file, char *const argv[], char *const envp[])
**		this is how i think it will work
**		currently limted to 3 arguments
**		by an other program...Amazing I know.
**
**	View this repository on gitHub!
**
** GitHub: https://github.com/DanChugani/unixLab5
*/


#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <wordexp.h>
#include <sys/stat.h>
#include <sys/wait.h>

void execvpe(const char * file, char * const argv[], char * const envp[])
{
  char * arglist[] = {file,argv[2],argv[3],argv[4],envp[0],NULL};
  pid_t childPID=fork();
  if(childPID==0)
  {
    execvp(file,arglist);
    perror("Failed to run execvp");
    exit(1);
  }
}

int main(int argc, char * argv[], char * envp[])
{
  char * fileName = argv[1];
  char * newEnv[]= {"PROG1","arg1","arg2","arg3",NULL};
  execvpe(fileName,argv,envp);

  return 0;
}
