#include "HRRF.h"

// 执行
void HRRF::execute(std::ostream& output) {
    if (list.GetLength() == 0) {
        output << "任务表为空！\n";
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

    // 复制作业到一个临时列表，按到达时间排序
    NodeList<Job> tempJobs(list);
    tempJobs.SetCompareFunction(jobSortArrivalTime);
    
   
    while (queue.GetLength() > 0 || tempJobs.GetLength() > 0) {
        // 将到达时间小于等于当前时间的作业插入队列
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
            // 计算每个作业的响应比
            for (int i = 0; i < queue.GetLength(); ++i) {
                if (queue.Find(i, job)) {
                    job.responseRatio = 1.0 + (double(now - job.arrivalTime) / job.executionTime);
                    queue_new.Insert(i, job, false);
                }
            }
        
            for (int i = 0; i < queue_new.GetLength(); ++i) {
                if (queue_new.Find(i, job)) {
                    // 添加调试输出
                    cout << "Job " << job.jobId << " Response Ratio: " << job.responseRatio << endl;
                }
            }

            // 找到响应比最高的作业
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
            output<<"响应比最高的作业是: " << executingJob.jobId << "响应比是: "<<executingJob.responseRatio<<endl;
            // 使用响应比最高的作业进行后续操作
            if (highestPriorityIndex != -1) {

                // 输出当前的作业排序和响应比
                output << "当前作业各自的响应比为: ";
                for (int i = 0; i < queue_new.GetLength(); ++i) {
                    queue_new.Find(i, job);
                    output << job.jobId << "(" << job.responseRatio << ") ";
                }
                output << "\n";

                // 执行作业
                now += executingJob.executionTime;
                output << "执行完的作业：" << executingJob
                    << "\n等待时间：" << (now - executingJob.executionTime - executingJob.arrivalTime)
                    << "\t周转时间：" << (now - executingJob.arrivalTime)
                    << "\t带权周转时间：" << (double(now - executingJob.arrivalTime) / executingJob.executionTime)
                    << "\n";

                total++;
                totalWait += now - executingJob.executionTime - executingJob.arrivalTime;
                totalTurnover += now - executingJob.arrivalTime;
                totalRightTurnover += double(now - executingJob.arrivalTime) / executingJob.executionTime;

                queue.Delete(highestPriorityIndex);
            }
        }
        else {
            // 队列为空，时间向前推进到下一个作业的到达时间
            
            if (tempJobs.GetLength() > 0 && tempJobs.Find(0, nextJob)) {
                now = nextJob.arrivalTime;
            }
        }
    }

    output << "\n平均等待时间：" << (totalWait / total)
        << "\t平均周转时间：" << (totalTurnover / total)
        << "\t平均带权周转时间：" << (totalRightTurnover / total)
        << "\n";
}
