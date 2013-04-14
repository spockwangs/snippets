/* 
 * sin.c - Manipulate shape of the wave of system monitor, and make
 *     the shape look like an sine wave.
 *
 * Author: wbb
 *
 * Compile
 *   gcc -W -Wall -std=c99 -pedantic sin.c -lm
 */

#define _GNU_SOURCE
#include <sys/time.h>
#include <math.h>
#include <unistd.h>
#include <sched.h>

const double PI = 3.14159265;
const int count = 500;
const int interval = 100;

unsigned long getTickCount(void)
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    return tv.tv_sec*1000 + tv.tv_usec/1000;
}

int main()
{
    /* 
     * Set this process running on some CPU.
     */
    cpu_set_t cpu_set;
    CPU_ZERO(&cpu_set);
    CPU_SET(3, &cpu_set);
    sched_setaffinity(0, sizeof(cpu_set_t), &cpu_set);

    int sinarr[count];
    for (int i = 0; i < count; i++) {
        sinarr[i] = (interval/2) * sin(i*2*PI/(count)) + interval/2;
    }

    int i = 0;
    for (;;) {
        unsigned long start_time = getTickCount();
        while (getTickCount() - start_time <= (unsigned) sinarr[i])
            ;
        usleep((interval-sinarr[i])*1000);
        
        i++;
        if (i == count)
            i = 0;
    }

    return 0;
}
