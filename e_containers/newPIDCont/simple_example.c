#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
 
static char child_stack[5000];
 
 
void grchild(int num)
{
  printf("child(%d) in ns my PID: %d Parent ID=%d\n", num, getpid(),getppid());
  sleep(5);
  puts("end child");
}
 
int child_fn(int ppid) {
  int i;
  printf("PID: %ld Parent:%ld\n", (long)getpid(), getppid());
  // Creates 3 new child processes..
  for(i=0;i<3;i++)
  {
   	if(fork() == 0)
  	{
  		grchild(i+1);  
  		exit(0);
  	}
	// tries to kill a child process outside of its namespace...
  	kill(ppid,SIGKILL); // no effect 
  }
  sleep(2);
  kill(2,SIGKILL); // kill the first child
  // Should kill the child process in its own namespace...
  sleep(10);
  return 0;
}
 
int main() {
  // Creates a child process in a new PID namespace...
  pid_t pid = clone(child_fn, child_stack+5000, CLONE_NEWPID , getpid());
  printf("clone() = %d\n", pid);
 
  waitpid(pid, NULL, 0);
  return 0;
}
