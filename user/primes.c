/*
 * @Author: xiaoyang bi 
 * @Date: 2022-08-16 17:10:50 
 * @Last Modified by:   xiaoyang bi 
 * @Last Modified time: 2022-08-16 17:10:50 
 */

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void one_process(int* p_in)
{
    int p_out[2];
    pipe(p_out);
    int num, n, status;
    close(p_in[1]);

    status = read(p_in[0], &num, sizeof(num));
    if(status == 0 )
        exit(0);
    else if(status == -1){
        fprintf(2, "Read Error");
        exit(1);
    }

    fprintf(1, "prime %d\n", num);     

    if(fork() != 0){

        while(read(p_in[0], &n, sizeof(n)) != 0)
            if(n/num * num != n)
                write(p_out[1], &n, sizeof(n));

        close(p_in[0]);
        close(p_out[1]);
        close(p_out[0]);

        wait((int *) 0);
        exit(0);
    }else{
        close(p_in[0]);
        one_process(p_out);
        exit(0);
    }

}

int main(int argc, char **argv)
{
    
    int i, p[2];
    pipe(p);  

    if(fork() == 0){

        one_process(p);
        exit(0);   

    }else{
        close(p[0]);
        for(i = 2; i<=35; i++)
        {
            write(p[1], &i, sizeof(i));
        }
        close(p[1]);

        wait((int *) 0);
        exit(0);
    }
    exit(0);

}
