/*
 * @Author: xiaoyang bi 
 * @Date: 2022-08-16 17:10:56 
 * @Last Modified by:   xiaoyang bi 
 * @Last Modified time: 2022-08-16 17:10:56 
 */

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char **argv)
{

  if(argc < 2){
    fprintf(2, "usage: sleep seconds...\n");
    exit(1);
  }
    sleep(atoi(argv[1]));
    exit(0);
}
