#include "kernel/types.h"
#include "user/user.h"
void sieve(int left_read_fd)
{
    int first_num;
    if(read(left_read_fd,&first_num,sizeof(int)) == 0)
    {
        close(left_read_fd);
        exit(0);
    }
    printf("prime %d \n",first_num);
    int p[2];
    pipe(p);

    int pid = fork();
    if(pid>0){
        close(p[0]);
        int n;
        while(read(left_read_fd,&n,sizeof(int)) > 0){
            if(n % first_num != 0)
            {
                write(p[1],&n,sizeof(int));
            }
        }
        close(left_read_fd);
        close(p[1]);
        wait((int *)0);
        exit(0);
    }else if(pid == 0)
    {
        close(p[1]);
        sieve(p[0]);

    }
    else{
        fprintf(2,"fork Error\n");
        exit(1);
    }
}
int main(){
    int p[2];
    pipe(p);
    int pid = fork();
    if(pid > 0)
    {
        close(p[0]);
        for(int i = 2;i<=35;i++)
        {
            write(p[1],&i,sizeof(int));
        }
        close(p[1]);
        wait((int * )0);
        exit(0);
    }
    else if(pid == 0){
        close(p[1]);
        sieve(p[0]);
    }
    else{
        fprintf(2,"Error");
        exit(1);
    }
    return 0;
}