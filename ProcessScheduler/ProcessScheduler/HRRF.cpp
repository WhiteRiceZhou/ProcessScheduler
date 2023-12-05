#include "HRRF.h"

// ִ��
void HRRF::execute(std::ostream& output) {
    if (list.GetLength() == 0) {
        output << "�����Ϊ�գ�\n";
        return;
    }

    Job job;
    Job executingJob;
    Job nextJob;
    NodeList<Job> queue;
    queue.SetCompareFunction(jobSortArrivalTime);
   
    unsigned int total = 0;
    double totalWait = 0, totalTurnover = 0, totalRightTurnover = 0;

    unsigned int now = 0;

    // ������ҵ��һ����ʱ�б�������ʱ������
    NodeList<Job> tempJobs(list);
    tempJobs.SetCompareFunction(jobSortArrivalTime);
    
   
    while (queue.GetLength() > 0 || tempJobs.GetLength() > 0) {
        // ������ʱ��С�ڵ��ڵ�ǰʱ�����ҵ�������
        while (tempJobs.GetLength() > 0) {
            if (tempJobs.Find(0, job)) {
                if (job.arrivalTime <= now) {
                    queue.Insert(queue.GetLength(), job, true);
                    tempJobs.Delete(0);
                }
                else {
                    break;
                }
            }
        }
        if (queue.GetLength() > 0) {
            NodeList<Job> queue_new;
            queue_new.SetCompareFunction(jobSortArrivalTime);
            // ����ÿ����ҵ����Ӧ��
            for (int i = 0; i < queue.GetLength(); ++i) {
                if (queue.Find(i, job)) {
                    job.responseRatio = 1.0 + (double(now - job.arrivalTime) / job.executionTime);
                    queue_new.Insert(i, job, false);
                }
            }
        
            for (int i = 0; i < queue_new.GetLength(); ++i) {
                if (queue_new.Find(i, job)) {
                    // ��ӵ������
                    cout << "Job " << job.jobId << " Response Ratio: " << job.responseRatio << endl;
                }
            }

            // �ҵ���Ӧ����ߵ���ҵ
            int highestPriorityIndex = -1;
            executingJob.responseRatio = -1;
            for (int i = 0,j=0; i < queue_new.GetLength(); ++i) {
                if (queue_new.Find(i, job)) {
                    if (highestPriorityIndex == -1 ||  job.responseRatio> executingJob.responseRatio)
                    {
                        executingJob = job;
                        highestPriorityIndex = i;
                    }
                }
            }
            output<<"��Ӧ����ߵ���ҵ��: " << executingJob.jobId << "��Ӧ����: "<<executingJob.responseRatio<<endl;
            // ʹ����Ӧ����ߵ���ҵ���к�������
            if (highestPriorityIndex != -1) {

                // �����ǰ����ҵ�������Ӧ��
                output << "��ǰ��ҵ���Ե���Ӧ��Ϊ: ";
                for (int i = 0; i < queue_new.GetLength(); ++i) {
                    queue_new.Find(i, job);
                    output << job.jobId << "(" << job.responseRatio << ") ";
                }
                output << "\n";

                // ִ����ҵ
                now += executingJob.executionTime;
                output << "ִ�������ҵ��" << executingJob
                    << "\n�ȴ�ʱ�䣺" << (now - executingJob.executionTime - executingJob.arrivalTime)
                    << "\t��תʱ�䣺" << (now - executingJob.arrivalTime)
                    << "\t��Ȩ��תʱ�䣺" << (double(now - executingJob.arrivalTime) / executingJob.executionTime)
                    << "\n";

                total++;
                totalWait += now - executingJob.executionTime - executingJob.arrivalTime;
                totalTurnover += now - executingJob.arrivalTime;
                totalRightTurnover += double(now - executingJob.arrivalTime) / executingJob.executionTime;

                queue.Delete(highestPriorityIndex);
            }
        }
        else {
            // ����Ϊ�գ�ʱ����ǰ�ƽ�����һ����ҵ�ĵ���ʱ��
            
            if (tempJobs.GetLength() > 0 && tempJobs.Find(0, nextJob)) {
                now = nextJob.arrivalTime;
            }
        }
    }

    output << "\nƽ���ȴ�ʱ�䣺" << (totalWait / total)
        << "\tƽ����תʱ�䣺" << (totalTurnover / total)
        << "\tƽ����Ȩ��תʱ�䣺" << (totalRightTurnover / total)
        << "\n";
}
