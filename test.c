
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define ll volatile int
#define MAX 10000000

int main(void) 
{
    int pid = getpid();
    set_priority(pid, 0);
    for (int i = 0; i < 10; i++) 
    {
        int pid = fork();
        if (pid == 0) 
        {
            int my_pid = getpid();
            //int pls = i * 10;
            //printf(1," \n\n%d\n\n", i*10);
            set_priority(my_pid, i*10);
        
            ll x = 0;
            for (ll y = 0; y < MAX; y++) 
                x = (x + x) % MAX;

            exit();
        }
    }

    for (int i = 0; i < 10; i++) 
       wait();

    exit();
}