#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"
int main(int argc,char *argv[])
{
    char buf[100];
    char *newargv[32];
    int i;
    if(argc < 2 )
    {
        fprintf(2,"xargs: usage: xargs command [arguments ...]\n");
        exit(1);
    }
    for(i = 1;i<argc;i++)
    {
        newargv[i - 1] = argv[i];
    }
    int n = 0;
    char c;
    while(read(0,&c,1) == 1)
    {
        if(c == '\n')
        {
            buf[n] = 0;
            newargv[i - 1] = buf;
            newargv[i] = 0;
            int pid = fork();
            if(pid == 0)
            {
                exec(newargv[0],newargv);
                fprintf(2,"xargs: exec %s failed\n",newargv[0]);
                exit(1);
            }
            else
            {
                wait(0);
            }
            n = 0;
        }
        else
        {
            buf[n++] = c;
        }
        
    }
    exit(0);
}