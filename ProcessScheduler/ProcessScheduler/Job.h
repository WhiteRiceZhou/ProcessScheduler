#pragma once
#include <iostream>
struct Job {
    //��ҵID 
    unsigned int jobId;
    //����ʱ��
    unsigned int arrivalTime;
    //ִ��ʱ��
    unsigned int executionTime;
    //����Ȩ
    unsigned int priority;
    //��Ӧ��
    double responseRatio=0;
};

//���������
std::ostream& operator<<(std::ostream &, Job&);

//������ʱ��������
int jobSortArrivalTime(Job&, Job&);

//��ִ��ʱ�䳤��������
int jobSortExecutionTime(Job&, Job&);

//�����ȼ�������
int jobSortPriority(Job&, Job&);
