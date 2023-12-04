#include "MLFQ.h"

void MLFQ::execute(std::ostream& output) {
    if (list.GetLength() == 0) {
        output << "任务表为空！\n";
        return;
    }

    Job job;
    NodeList<Job> arrived;
    arrived.SetCompareFunction(jobSortArrivalTime);
    unsigned int total = 0;
    double totalWait = 0, totalTurnover = 0, totalRightTurnover = 0;
   // unsigned int timeQuantum1 = 5; // 时间片大小，根据实际需求调整
    //unsigned int timeQuantum2 = 10; // 第二级队列的时间片大小

    // 设置两个就绪队列 Q1 和 Q2，可以根据需求设置更多队列
    NodeList<Job> queue1;
    queue1.SetCompareFunction(jobSortArrivalTime);
    NodeList<Job> queue2;
    queue2.SetCompareFunction(jobSortArrivalTime);

    // 将所有作业按到达时间插入 Q1
    for (int i = 0; i < list.GetLength(); ++i) {
        
        list.Find(i, job);
        queue1.Insert(queue1.GetLength(), job, true );
    }

    unsigned int now = 0;

    while (queue1.GetLength() > 0 || queue2.GetLength() > 0) {
        // 先调度 Q1 中的作业
        while (queue1.GetLength() > 0) {
            queue1.Find(0, job);

            // 如果当前时间已经超过作业到达时间，执行作业
            if (job.arrivalTime <= now) {
                if (job.executionTime <= slice1) {
                    now += job.executionTime;
                    output << "执行完的作业：" << job
                        << "\n等待时间：" << (now - job.executionTime - job.arrivalTime)
                        << "\t周转时间：" << (now - job.arrivalTime)
                        << "\t带权周转时间：" << (double(now - job.arrivalTime) / job.executionTime)
                        << "\n";
                    total++;
                    totalWait += now - job.executionTime - job.arrivalTime;
                    totalTurnover += now - job.arrivalTime;
                    totalRightTurnover += double(now - job.arrivalTime) / job.executionTime;

                    queue1.Delete(0);
                }
                else {
                    // 如果执行时间超过时间片大小，将剩余部分移到 Q2
                    now += slice1;
                    output << "执行了时间片：" << slice1 << "，作业：" << job << "\n";
                    job.executionTime -= slice1;
                    queue2.Insert(queue2.GetLength(), job, true);
                    queue1.Delete(0);
                }
            }
            else {
                break;
            }
        }

        // 如果 Q1 队列为空，但 Q2 队列不为空，调度 Q2 中的作业
        while (queue1.GetLength() == 0 && queue2.GetLength() > 0) {
            
            queue2.Find(0, job);

            // 如果当前时间已经超过作业到达时间，执行作业
            if (job.arrivalTime <= now) {
                if (job.executionTime <= slice2) {
                    now += job.executionTime;
                    output << "执行完的作业：" << job
                        << "\n等待时间：" << (now - job.executionTime - job.arrivalTime)
                        << "\t周转时间：" << (now - job.arrivalTime)
                        << "\t带权周转时间：" << (double(now - job.arrivalTime) / job.executionTime)
                        << "\n";
                    total++;
                    totalWait += now - job.executionTime - job.arrivalTime;
                    totalTurnover += now - job.arrivalTime;
                    totalRightTurnover += double(now - job.arrivalTime) / job.executionTime;

                    queue2.Delete(0);
                }
                else {
                    // 如果执行时间超过时间片大小，将剩余部分仍然放在 Q2 中 
                    now += slice2;
                    output << "执行了时间片：" << slice2 << "，作业：" << job << "\n";
                    job.executionTime -=slice2;
                    queue2.Insert(queue2.GetLength(), job, true);
                    queue2.Delete(0);
                }
            }
            else {
                break;
            }
        }
    }

    output << "\n平均等待时间：" << (totalWait / total)
        << "\t平均周转时间：" << (totalTurnover / total)
        << "\t平均带权周转时间：" << (totalRightTurnover / total)
        << "\n";
}
