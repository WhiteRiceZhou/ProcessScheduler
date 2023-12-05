#include <iostream>
#include <fstream>
#include "Job.h"
#include "LinkList.h"
#include "FCFS.h"
#include "SJF.h"
#include "HPF.h"
#include "RR.h"
#include"MLFQ.h"
#include"HRRF.h"
using namespace std;
int order=0;
int main() {
    ifstream file("data.txt", ios::in);
    if(!file.is_open()) {
        cout << "data.txt can't open for read!" << endl;
        system("pause");
        exit(1);
    }
    char str[45];
    //将首行读出
    file.getline(str, 45);

    //作业表
    NodeList<Job> jobs;
    jobs.SetCompareFunction(jobSortArrivalTime);

    Job job;
    while(file >> job.jobId) {
        file >> job.arrivalTime;
        file >> job.executionTime;
        file >> job.priority;
        jobs.Insert(jobs.GetLength(), job, true);
    }
    file.close();
    while (true) {
        cout << "菜单: 1:FCFS 先来先服务" << endl
            << "2:SJF 短作业优先 " << endl
            << "3:HPF 优先级调度 " << endl
            << "4.MLFQ 多级队列反馈算法" << endl
            << "5.RR 时间片轮转算法" << endl
            <<"6.HRRN 高响应比"<<endl
            <<"输入0 退出 "<<endl
            << "请输入: ";
        cin >> order;
        if (order == 0) {
            cout << "Exit"<<endl;
            break; // 退出循环，结束程序
        }
        switch (order) {
        case 1: {
            //先来先服务
            cout << "******************* 开始模拟 FCFS 先来先服务 ********************\n\n";
            FCFS fcfs(jobs);
            fcfs.execute(cout);
            cout << '\n';
            cout << "*****************************************************************\n";
            break;
        }
        case 2: {
            //短作业优先
            cout << "******************** 开始模拟 SJF 短作业优先 ********************\n\n";
            SJF sjf(jobs);
            sjf.execute(cout);
            cout << '\n';
            cout << "*****************************************************************\n";

            break;
        }
        case 3: {
            //优先权高者优先
            cout << "****************** 开始模拟 HPF 优先级调度 ******************\n\n";
            HPF hpf(jobs);
            hpf.execute(cout);
            cout << '\n';
            cout << "*****************************************************************\n";

            break;
        }
        case 4: {
            cout << "********************* 准备模拟 MLFQ 多级队列反馈算法 ********************"
                << endl << "请输入时间片1大小（slice> 0）：";
            unsigned int slice1 = 0;
            while (slice1 <= 0) {
                cin >> slice1;
            }
            cout << "请输入时间片2大小（slice> 0）：";
            unsigned int slice2 = 0;
            while (slice2 <= 0) {
                cin >> slice2;
            }
            //多级队列反馈算法
            cout << "****************** 开始模拟 MLFQ 多级队列反馈算法 ******************\n\n";
            MLFQ mlfq(jobs, slice1, slice2);
            mlfq.execute(cout);
            cout << '\n';
            cout << "*****************************************************************\n";
            break;
        }
        case 5: {
            //时间片轮转
            cout << "********************* 准备模拟 RR 时间片轮转 ********************"
                << endl << "请输入时间片大小（slice> 0）：";
            unsigned int slice = 0;
            while (slice <= 0) {
                cin >> slice;
            }
            cout << "********************* 开始模拟 RR 时间片轮转 ********************\n\n";
            RR rr(jobs, slice);
            rr.execute(cout);
            cout << '\n';
            cout << "*****************************************************************\n";
            break;
        }
        case 6: {
            //优先权高者优先
            cout << "****************** 开始模拟 HRRN 高响应比 ******************\n\n";
            HRRF hrrf(jobs);
            hrrf.execute(cout);
            cout << '\n';
            cout << "*****************************************************************\n";

            break;
        }
        }
    }
    system("pause");
    return 0;
}
