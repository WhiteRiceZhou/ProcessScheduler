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
    //�����ж���
    file.getline(str, 45);

    //��ҵ��
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
        cout << "�˵�: 1:FCFS �����ȷ���" << endl
            << "2:SJF ����ҵ���� " << endl
            << "3:HPF ���ȼ����� " << endl
            << "4.MLFQ �༶���з����㷨" << endl
            << "5.RR ʱ��Ƭ��ת�㷨" << endl
            <<"6.HRRN ����Ӧ��"<<endl
            <<"����0 �˳� "<<endl
            << "������: ";
        cin >> order;
        if (order == 0) {
            cout << "Exit"<<endl;
            break; // �˳�ѭ������������
        }
        switch (order) {
        case 1: {
            //�����ȷ���
            cout << "******************* ��ʼģ�� FCFS �����ȷ��� ********************\n\n";
            FCFS fcfs(jobs);
            fcfs.execute(cout);
            cout << '\n';
            cout << "*****************************************************************\n";
            break;
        }
        case 2: {
            //����ҵ����
            cout << "******************** ��ʼģ�� SJF ����ҵ���� ********************\n\n";
            SJF sjf(jobs);
            sjf.execute(cout);
            cout << '\n';
            cout << "*****************************************************************\n";

            break;
        }
        case 3: {
            //����Ȩ��������
            cout << "****************** ��ʼģ�� HPF ���ȼ����� ******************\n\n";
            HPF hpf(jobs);
            hpf.execute(cout);
            cout << '\n';
            cout << "*****************************************************************\n";

            break;
        }
        case 4: {
            cout << "********************* ׼��ģ�� MLFQ �༶���з����㷨 ********************"
                << endl << "������ʱ��Ƭ1��С��slice> 0����";
            unsigned int slice1 = 0;
            while (slice1 <= 0) {
                cin >> slice1;
            }
            cout << "������ʱ��Ƭ2��С��slice> 0����";
            unsigned int slice2 = 0;
            while (slice2 <= 0) {
                cin >> slice2;
            }
            //�༶���з����㷨
            cout << "****************** ��ʼģ�� MLFQ �༶���з����㷨 ******************\n\n";
            MLFQ mlfq(jobs, slice1, slice2);
            mlfq.execute(cout);
            cout << '\n';
            cout << "*****************************************************************\n";
            break;
        }
        case 5: {
            //ʱ��Ƭ��ת
            cout << "********************* ׼��ģ�� RR ʱ��Ƭ��ת ********************"
                << endl << "������ʱ��Ƭ��С��slice> 0����";
            unsigned int slice = 0;
            while (slice <= 0) {
                cin >> slice;
            }
            cout << "********************* ��ʼģ�� RR ʱ��Ƭ��ת ********************\n\n";
            RR rr(jobs, slice);
            rr.execute(cout);
            cout << '\n';
            cout << "*****************************************************************\n";
            break;
        }
        case 6: {
            //����Ȩ��������
            cout << "****************** ��ʼģ�� HRRN ����Ӧ�� ******************\n\n";
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
