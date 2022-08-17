/*
 * @Author: xiaoyang bi 
 * @Date: 2022-08-16 17:10:42 
 * @Last Modified by:   xiaoyang bi 
 * @Last Modified time: 2022-08-16 17:10:42 
 */

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define BUFFER_SIZE 1

int
main(int argc, char **argv)
{
    int p[2];
    char buf[BUFFER_SIZE] = "";

    pipe(p);

    if(fork() == 0){
        //child
        read(p[1], buf, BUFFER_SIZE);
        fprintf(1, "%d: received ping\n", getpid());
        write(p[1], buf, BUFFER_SIZE);
        close(p[1]);
        close(p[0]);
        exit(0);

    }else{
        //parent
        write(p[0], buf, BUFFER_SIZE);
        read(p[0], buf, BUFFER_SIZE);
        fprintf(1, "%d: received pong\n", getpid());
        close(p[1]);
        close(p[0]);
        exit(0);
    }


}
