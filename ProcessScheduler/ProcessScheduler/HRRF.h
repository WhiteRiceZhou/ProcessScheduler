#pragma once
#include "LinkList.h"
#include "Job.h"
#include<Vector>
class HRRF {
public:
    //构造函数 
    HRRF(NodeList<Job> jobs) : list(jobs) {
        list.SetCompareFunction(jobSortArrivalTime);
        list.Sort();
    }
    //执行
    void execute(std::ostream&);
private:
    NodeList<Job> list;
    std::vector<double> responseRatios;
};