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
#include "memlayout.h"

extern char trampoline[], userret[];

/**
 * @brief 
 * clear the alarm_ticks so that the alarm fn can be called periodically
 * restore the saved register before alarm and return to user space
 * 
 * @return int 
 */

int sigreturn(void)
{
   struct proc *p = myproc();
   memmove(p->trapframe, &p->trapframe_saved, TRAPFRAME_SIZE);
   p->alarm_last_isfinished = 1;
   p->alarm_ticks = 0;
   usertrapret();
   return 0;
}

