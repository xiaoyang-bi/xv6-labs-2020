/*
 * @Author: xiaoyang bi 
 * @Date: 2022-08-17 09:10:53 
 * @Last Modified by: xiaoyang bi
 * @Last Modified time: 2022-08-17 12:51:07
 */

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

#define ARGLEN 56


void xargs(int argc, char** argv)
{
    char in[512];  // the std output as the param in
    char** params = (char**)malloc(MAXARG*sizeof(char*));
    for(int i=0; i<MAXARG; i++){
        params[i] = (char*)malloc(ARGLEN*sizeof(char));
    }

    int status =  read(0, in, sizeof in) != 0;
    if(status == -1){
        fprintf(2, "read error\n");
        exit(1);
    }

    char bin[512] = "/";
    char* p = bin + strlen(bin);
    memmove(p, argv[1], strlen(argv[1]));
    // *++p = '\0';

    char* p_ed = in;
    char* p_st = in;
    int i = 0;
    
    while(*p_ed){
        // printf("%c ", *p_ed);
        switch (*p_ed)
        {
            case '\n':
                memmove(params[argc -1  + i], p_st, (p_ed - p_st)*sizeof(*p_ed));
                params[argc - 1 +i][(p_ed - p_st)] = '\0';
                params[argc + i] = 0;
                p_st = ++p_ed;
                i++;

                for(int j=0; j<argc-1; j++){
                    memmove(params[j], argv[j+1], sizeof argv[j+1]);
                }

                if(fork() == 0)
                    exec(bin, params);
                else;
                break;
            case ' ':
                if(argc + i > MAXARG){
                    fprintf(2, "too many args\n");
                    exit(1);
                }
                memmove(params[argc -1  + i], p_st, (p_ed - p_st)*sizeof(*p_ed));
                params[argc - 1 +i][(p_ed - p_st)] = '\0';
                p_st = ++p_ed;
                i++;
                break;
            default:
                p_ed++;
                break;
        }
    }
    wait((void *) 0);
    return ; 
}


int main(int argc, char** argv)
{
    xargs(argc, argv);
    
    exit(0);
}