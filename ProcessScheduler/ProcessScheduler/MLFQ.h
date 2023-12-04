#pragma once
#include "LinkList.h"
#include "Job.h"
class MLFQ {
public:
	MLFQ(NodeList<Job> jobs,  unsigned int slice1, unsigned int slice2) : list(jobs), slice1(slice1),slice2(slice2) {
		list.SetCompareFunction(jobSortArrivalTime);
		list.Sort();
	}


	void execute(std::ostream&);
private:
		NodeList<Job> list;
		//时间片1 
		unsigned int slice1;
		//时间片2
		unsigned int slice2;
};