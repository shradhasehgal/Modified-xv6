#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

#define ll long long int
#define MAX 100000000

int main (int argc,char *argv[])
{
  int pid;
	int status = 0, a, b;
	pid = fork();
	if (pid == 0)
	{
		long long int z, x = 0;
		printf(1, "I'm Child Process\n");
		for (z = 0; z < 2147483648; z += 1)
			x = x + x; // useless calculations to consume CPU time
		exit();
	}
	else
	{
		status = waitx(&a, &b);
		printf(1, "Wait Time = %d\nRun Time = %d with Status %d \n", a, b, status);
	}

	exit();
  // int pid, status = 0, a = 0 ,b = 0;
  	

  // pid = fork();
  // if (pid == 0)
  // {	
  //     ll x = 0, y;
  //     for (y = 0; y < MAX; y++)
  //       x = 1 ^ x; 
  //     exit();
  //     // exec(argv[1], argv);
  //     // printf(1, "exec %s failed\n", argv[1]);
  //     // exit();
  // }

  // else
  // {
  //   status = waitx(&a,&b);
  // }  
  // printf(1, "Wait Time = %d\nRun Time = %d with Status %d \n",a,b,status); 
  // exit();
}