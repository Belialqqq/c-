#include<unistd.h>
#include<cstdio>
#include<sys/wait.h>
#include<sys/types.h>
#include<cstdlib>


int main()
{
    pid_t id=fork();
    if(id==0)
    {
        sleep(3);
        execl("/bin/ls","ls","-l","--color",nullptr);
        exit(1);
    }
    int status=1;
    pid_t rid=waitpid(id,&status,0);
    if(rid>0)
    {
        printf("等待子进程成功，子进程退出码为%d\n",WEXITSTATUS(status));
    }
    return 0;
}
