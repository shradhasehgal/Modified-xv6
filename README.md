# Modifications to the xv6 operating system

## By Shradha Sehgal

## Overview

Various improvements have been made to the xv6 operating system such as the waitx and getpinfo syscall. Scheduling techniques such as FCFS, PBS, and MLFQ have also been implemented.

## Run the shell

1. Run the command `make qemu`.
2. Add the flag `SCHEDULER` to choose between RR, FCFS, PBS, and MLFQ 

# Task 1 

## Waitx Syscall

### Adding System Call 

The files that have been modified are:

1. user.h
2. usys.S
3. syscall.h
4. syscall.c
5. sysproc.c
6. defs.h
7. proc.c
8. proc.h

- The fields ctime (CREATION TIME), etime (END TIME), rtime (calculates RUN TIME) & iotime (IO TIME) fields have been added to proc structure of proc.h file

- proc.c contains the actual waitx() system call:

    Code is same as wait() and does the following: 
    - Search for a zombie child of parent in the proc table. 
    - When the child was found , following pointers were updated : 
        - *wtime= p->etime - p->ctime - p->rtime - p->iotime; 
        - *rtime=p->rtime; 
    - sysproc.c is just used to call waitx() which is present in proc.c. The sys_waitx() function in sysproc.c passes the parameters (rtime,wtime) to the waitx() of proc.c, just as other system calls do.

### Calculating ctime, etime and rtime

- ctime is recoreded in allocproc() function of proc.c (When process is born). It is set to ticks.
- etime is recorded in exit() function (i.e when child exists, ticks are recorded) of proc.c.
- rtime is updated in trap() function of trap.c. IF STATE IS RUNNING , THEN UPDATE rtime.
- iotime is updated in trap() function of trap.c.(IF STATE IS SLEEPING , THEN UPDATE iotime.

### Tester file - time command 

- time inputs a command and exec it normally
- Uses waitx instead of normal wait
- Displays wtime and rtime along with status that is the same as that returned by wait() syscall


## Getpinfo Sys Call

A separate header file pstat.h has been created for struct proc_stat. 

Along with this the files modified are:

1. user.h
2. usys.S
3. syscall.h
4. syscall.c
5. sysproc.c
6. defs.h
7. proc.c

- `getpinfo(struct proc_stat*, int pid)`​ has been declared in proc.c and `sys_getpinfo(void)` in sysproc.c just passes arguments to it. 
- pid is assigned according to the parameter passed.
- For runtime we traverse through the process table to find a process with the same pid and assign proc_stat's run time as that process' `rtime`.
- `num_run` is incremented in al scheduler whenever a process is run. 
- Current_queue is assigned only in case of MLFQ.
- `p->ticks[5]` is copied into the proc_stat objects ticks[5] in case of MLFQ

The code where all this assigning takes place is as follows: 

```c
int getpinfo(struct proc_stat *p_proc, int pid) 
{
	struct proc *p;
	int ret = -1;
	for (p = ptable.proc; p < &ptable.proc[NPROC]; p++)
	{
		if(p -> pid == pid)
		{
			p_proc -> pid = pid;
			p_proc->runtime = p->rtime;  
			p_proc->num_run = p->num_run;
			#ifdef MLFQ
			p_proc -> current_queue = p->queue;
			for(int i=0; i < 5;i++)
				p_proc->ticks[i] = p->ticks[i];
			#endif
			ret = 1;
			//cprintf("")
			break;   
		}
	}

	return ret;
}
```

The code for sys_getpinfo() is as follows: 
```c
int sys_getpinfo(void)
{
  int pid; struct proc_stat *p;

  if(argptr(0,(char**)&p,sizeof(p)) < 0)
    return -1;

  if(argint(1, &pid) < 0)
    return -1;

  return getpinfo(p, pid);
}
```

# Task 2 - Scheduling techniques

All scheduling techiniques have been added to the `scheduler` function in `proc.c`. Add the flag `SCHEDULER` to choose between RR, FCFS, PBS, and MLFQ. This has been implemented in `Makefile`. 

## First come - First Served (FCFS)

- Non preemptive ​policy so we removed the the `yield()` call in trap.c in case of FCFS as shown:

```c
#ifndef FCFS
    yield();
#endif
```

- Set