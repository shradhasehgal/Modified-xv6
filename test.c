
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define ll volatile int
#define MAX 10000000

int main(void) 
{
    // set_priority(0);
    for (int i = 0; i < 10; i++) 
    {
        int pid = fork();
        if (pid == 0) 
        {
            // if (i % 3 == 0) {
            //     set_priority(i+10);
            // }
            
            // #ifndef DEBUG
            //     int my_pid = getpid();
            //     for (int g = 0; g < 5; g++)
            //     printf(1, "i: %d pid: %d\n", i, my_pid);
            // #endif

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