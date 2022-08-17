/*
 * @Author: xiaoyang bi 
 * @Date: 2022-08-16 17:10:22 
 * @Last Modified by: xiaoyang bi
 * @Last Modified time: 2022-08-16 22:47:40
 */

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"



void find(const char* dir,  const char* dest)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if( (fd = open(dir, 0)) < 0){
        fprintf(2, "ls: cannot open %s\n", dir);
        return; 
    }

    if(fstat(fd, &st) < 0){
        fprintf(2, "ls: cannot stat %s\n", dir);
        close(fd);
        return;
    }

    if(strlen(dir) + 1 + DIRSIZ + 1 > sizeof buf){
        printf("find: path too long\n");
        exit(1);
    }

    strcpy(buf, dir);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
        if(de.inum == 0)
            continue;
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        // fprintf(1, "%s\n", de.name);
        if(!strcmp(de.name, dest))
            fprintf(1, "%s\n", buf);
        
        if(stat(buf, &st) < 0){
            printf("ls: cannot stat %s\n", buf);
            continue;
      }
      if(st.type == T_DIR && strcmp(de.name, ".") && strcmp(de.name, "..")){
        find(buf, dest);
      }

    }

    close(fd);
    return ;

}

int main(int argc, char** argv)
{
    if(argc <3){
        fprintf(2, "usage: find dir file/dir\n");
        exit(1);
    }
    find(argv[1], argv[2]);

    exit(0);

}