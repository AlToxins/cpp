#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/wait.h>

pid_t child1, child2;//两个子进程
int fd[2];
void SignalHandler1(int iSignNo);//信号处理
void SignalHandler2(int iSignNo);

int main()
{
    int Count = 1;
    char buffer[40];
    char info[40];
    pid_t getpid();
    printf("Process Parent PID:%d\n", getpid());
    //创建无名管道，只能在父子或兄弟进程间通信
    //fd[0]只能用于读,fd[1]只能用于写
    if(pipe(fd) < 0)
    {
        printf("管道创建失败！\n");
        return -1;
    }
    //设置软中断信号SIGINT，终端输入Ctrl+C，进程终止
    signal(SIGINT, SignalHandler1);
    //创建子进程1,2
    child1 = fork();
    if(child1 == 0) //子进程1
    {
        printf("Child Process 1 PID:%d\n", getpid());
        //设置忽略信号,如果不设置，在子进程运行过程直接Ctrl+C,会造成进程终止，
        //产生僵尸进程，因此需要在子进程中屏蔽，等子进程被父进程kill之后，再在
        //父进程中Ctrl+C使进程完全结束，就不会产生僵尸进程了
        signal(SIGINT, SIG_IGN);
        //设置信号SIGUSR1
        signal(SIGUSR1, SignalHandler2);
        while(1)
        {
            close(fd[0]);
            sprintf(info, "I send message %d times", Count);
            //管道长度受到限制，管道写满时写入操作将被阻塞，直到管道中的数据被读取
            write(fd[1], info, 30);//发送数据至管道数据
            ++Count;//计数器+1
            sleep(1);//睡眠1s
        }
    }
   else if(child1 > 0)//返回父进程
    {
        child2 = fork(); //父进程创建子进程2
        if(child2 == 0) //子进程2
        {
            printf("Child Process 2 PID:%d\n", getpid());
            //设置忽略信号
            signal(SIGINT, SIG_IGN);
            //设置信号SIGUSR1
            signal(SIGUSR2, SignalHandler2);
            while(1)
            {
                close(fd[1]);
                //当数据被读取后，数据将自动被管道清除
                //接受管道数据
                read(fd[0], buffer, 40);
                //显示管道数据
                printf("%s\n", buffer);
            }
        }
        else //返回父进程
        {
            //等待子进程1,2退出
            waitpid(child1, NULL, 0);
            //printf("Child Process 1 is over!\n");
            waitpid(child2, NULL, 0);
            //printf("Child Process 2 is over!\n");
            //关闭管道
            close(fd[0]);
            close(fd[1]);
            printf("Parent Process is Killed!\n");
        }

    }

    return 0;
}

void SignalHandler1(int iSignNo)
{
    printf("\nParent recive signal Ctrl+C\n");
    if(iSignNo == SIGINT)//传递SIGUSR信号给子进程
    {
        //SIGUSR1和SIGUSR2是用户自定义信号，进程终止
        kill(child1, SIGUSR1);
        kill(child2, SIGUSR2);
    }
}

void SignalHandler2(int iSignNo)
{
    close(fd[0]);
    close(fd[1]);
    if(child1 == 0 && iSignNo == SIGUSR1)
    {
        printf("Child Process 1 is killed by Parent!\n");
        exit(0);

    }
    if(child2 == 0 && iSignNo == SIGUSR2)
    {
        printf("Child Process 2 is killed by Parent!\n");
        exit(0);
    }
}

