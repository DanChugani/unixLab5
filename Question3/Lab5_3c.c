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

#include <sys/wait.h>
#include <sys/times.h>
#include <sys/time.h>
#include <math.h>
#include <stdio.h>
#define _XOPEN_SOURCE
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

/*Define some variables*/
long clockTicksPerSecond;
struct timeval clockTime1,clockTime2;
struct tms startTime, endTime;

void showElapsed()/* Function to show elapsed time */
{
    times(&endTime);
    gettimeofday(&clockTime2,NULL);

    //Present the timing info
    time_t secs=clockTime2.tv_sec-clockTime1.tv_sec;
    time_t usecs=clockTime2.tv_usec-clockTime1.tv_usec;
    if(usecs<0) /*Adjust the time*/
    {
	usecs+=1000000;  /*Add one second*/
	secs--;          /*Subtract one second*/
    }
    fprintf(stdout,"Elapsed (real) time: %ld.%06ld seconds.\n",
	    secs, usecs);

    fprintf(stdout,"Elapsed user process time: %8.4lf seconds. \n",
	    (endTime.tms_utime-startTime.tms_utime)/
	    (double) clockTicksPerSecond);      

    fprintf(stdout,"Elapsed system process time: %8.4lf seconds. \n",
	    (endTime.tms_stime-startTime.tms_stime)/
	    (double) clockTicksPerSecond);      

 }

void wasteTime()/* Function to waste some time */
{
    /* Some more variables */
    int i;
    long double sum=0;
    struct timeval dummy;
            
    for(int k=1;k<20;k++)
    {  
	for(i=1;i<2000;i++)
	{   
	    for(int j=1;j<1000;j++)
		sum+=sqrt(sqrt(sqrt((double)i)));  /* add user CPU time*/
	    for(int m=1;m<10;m++) gettimeofday(&dummy,NULL);
	}
    }
    fprintf(stdout, "Sum: %Lf\n",sum);
    usleep(1500000);
}

int main(int argc, char * argv[],char * envp[]) /* Start of main */
{
  
  int status;
  char * arglist[] = {argv[1],argv[2],argv[3],argv[4],NULL}; /*The List of Arguments*/

  clockTicksPerSecond=sysconf(_SC_CLK_TCK);
  gettimeofday(&clockTime1,NULL);
  times(&startTime);
 
  pid_t child = fork();
  if(child==0) /* If there is a child process  */
  {
	fprintf(stdout,"Child process ID is: %d\n",getpid());
	wasteTime();
	showElapsed();
	exit(17);
  }
  else if(child==-1) /* Error in forking, not my fault I promise*/
	fprintf(stderr,"Error in Fork");
  else /* Wait for Child to finish process */
  {
	child = wait(&status); /* Waiting... */
	fprintf(stdout,"Parent process ID is: %d\n",getpid());
	wasteTime();
	showElapsed();
  } 
  return 0;
}/* End of main */
