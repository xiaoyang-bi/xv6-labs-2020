/*
* author: xiaoyang-bi
*/

#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "spinlock.h"
#include "proc.h"
#include "fs.h"
#include "sleeplock.h"
#include "file.h"

/**
 * @brief init sigalarm mechanism
 * 
 * @param ticks 
 * @param handler 
 * @return int 
 */

int sigalarm(int ticks, void (*handler)())
{
    struct proc *p = myproc();
    p->alarm_fn = handler;
    p->alarm_interval = ticks;
    p->alarm_ticks = 0;
    p->alarm_last_isfinished = 1; 
    p->is_alarm = ( ticks !=0 ) ;

    return 1;
}

