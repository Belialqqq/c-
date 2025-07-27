#include<iostream>
#include<cstdio>
#include<string>
#include<unistd.h>
#include<vector>
#include<sys/types.h>
#include<sys/wait.h>
#include<ctime>


enum{
    PROCESSCREATERROR=-1,
    PROCESSSSUCESS,
    SUBPROCESSEXIT,
    FILEOPENERROR
};

std::vector<int> vi;

const std ::  string fgf("  ");

void Copyfunction()
{
    std:: string name("datacopy.");
    std::time_t rawtime;
    std::time(&rawtime);
    std::tm* timeinfo=std::localtime(&rawtime);
    char buffer[80];
     std::strftime(buffer, sizeof(buffer), "datacopy.%Y%m%d_%H%M%S", timeinfo);
     name+=std::string(buffer);
    FILE*fp=fopen(name.c_str(),"w");
    if(!fp)
    {
        perror("打开文件失败");
        exit(FILEOPENERROR);
    }
    std::string context;
    for(const auto& e: vi)
    {
        context+=e;
        context+=fgf;
    }
    
    fputs(context.c_str(),fp);

}

void datacopy()
{
       
    pid_t id=fork();
    if(id<0)
    {
        perror("进程创建失败");
        exit(PROCESSCREATERROR);
    }
    else if(id==0){
        
        Copyfunction();
        exit(SUBPROCESSEXIT);
    }
 //else{
 //       int status;
 //      int  rid=waitpid(id,&status,0);
 //      // if(rid>0)
 //       {
 //           
 //           if(WIFEXITED(status))
 //           {
 //               printf("父进程等待子进程成功，子进程pid为%d,子进程进程退出码%d\n",rid,WEXITSTATUS(status));
 //           }
 //           else{
 //               printf("子进程运行时退出，退出信号为%d\n",WIFEXITED(status));
 //           }
 //       }
//}//
}


int main()
{
    pid_t id=fork();
    if(id<0)
    {
        perror("进程创建失败");
        exit(PROCESSCREATERROR);
    }
    else if(id==0){
        
        exit(SUBPROCESSEXIT);
    }
   int cnt=1;
   while(1)
   {
        vi.push_back(cnt++);
        sleep(1);
        if(cnt%10==0)
        {
            datacopy();
        }
   }
}

