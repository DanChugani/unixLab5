/* Author: Chandan Chugani
// Date: April 8th, 2015 
// Professor: Leon King
// Description: This program shows the use of execle	
//	View this repository on gitHub!
//
// GitHub: https://github.com/DanChugani/unixLab5
*/
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>

int main(int argc,char *argv[],char *envp[])
{
  char *newEnv[] = {"PROG1","arg1","arg2","arg3",NULL};
  pid_t childpid;
    
  //Demostrating execle
  //Runs example c code with no arguments
  childpid=fork();
  if(childpid==0) 
     {  
	execle("./example","prog","argA","ARGB",NULL,newEnv);
        perror("Failed to run execle");
        exit(1);
     }
  return 0;
}
