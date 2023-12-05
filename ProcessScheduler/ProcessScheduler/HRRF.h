#pragma once
#include "LinkList.h"
#include "Job.h"
#include<Vector>
class HRRF {
public:
    //���캯�� 
    HRRF(NodeList<Job> jobs) : list(jobs) {
        list.SetCompareFunction(jobSortArrivalTime);
        list.Sort();
    }
    //ִ��
    void execute(std::ostream&);
private:
    NodeList<Job> list;
    std::vector<double> responseRatios;
};