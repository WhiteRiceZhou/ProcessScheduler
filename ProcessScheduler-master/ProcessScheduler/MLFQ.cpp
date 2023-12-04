#include "MLFQ.h"

void MLFQ::execute(std::ostream& output) {
    if (list.GetLength() == 0) {
        output << "�����Ϊ�գ�\n";
        return;
    }

    Job job;
    NodeList<Job> arrived;
    arrived.SetCompareFunction(jobSortArrivalTime);
    unsigned int total = 0;
    double totalWait = 0, totalTurnover = 0, totalRightTurnover = 0;
   // unsigned int timeQuantum1 = 5; // ʱ��Ƭ��С������ʵ���������
    //unsigned int timeQuantum2 = 10; // �ڶ������е�ʱ��Ƭ��С

    // ���������������� Q1 �� Q2�����Ը����������ø������
    NodeList<Job> queue1;
    queue1.SetCompareFunction(jobSortArrivalTime);
    NodeList<Job> queue2;
    queue2.SetCompareFunction(jobSortArrivalTime);

    // ��������ҵ������ʱ����� Q1
    for (int i = 0; i < list.GetLength(); ++i) {
        
        list.Find(i, job);
        queue1.Insert(queue1.GetLength(), job, true );
    }

    unsigned int now = 0;

    while (queue1.GetLength() > 0 || queue2.GetLength() > 0) {
        // �ȵ��� Q1 �е���ҵ
        while (queue1.GetLength() > 0) {
            queue1.Find(0, job);

            // �����ǰʱ���Ѿ�������ҵ����ʱ�䣬ִ����ҵ
            if (job.arrivalTime <= now) {
                if (job.executionTime <= slice1) {
                    now += job.executionTime;
                    output << "ִ�������ҵ��" << job
                        << "\n�ȴ�ʱ�䣺" << (now - job.executionTime - job.arrivalTime)
                        << "\t��תʱ�䣺" << (now - job.arrivalTime)
                        << "\t��Ȩ��תʱ�䣺" << (double(now - job.arrivalTime) / job.executionTime)
                        << "\n";
                    total++;
                    totalWait += now - job.executionTime - job.arrivalTime;
                    totalTurnover += now - job.arrivalTime;
                    totalRightTurnover += double(now - job.arrivalTime) / job.executionTime;

                    queue1.Delete(0);
                }
                else {
                    // ���ִ��ʱ�䳬��ʱ��Ƭ��С����ʣ�ಿ���Ƶ� Q2
                    now += slice1;
                    output << "ִ����ʱ��Ƭ��" << slice1 << "����ҵ��" << job << "\n";
                    job.executionTime -= slice1;
                    queue2.Insert(queue2.GetLength(), job, true);
                    queue1.Delete(0);
                }
            }
            else {
                break;
            }
        }

        // ��� Q1 ����Ϊ�գ��� Q2 ���в�Ϊ�գ����� Q2 �е���ҵ
        while (queue1.GetLength() == 0 && queue2.GetLength() > 0) {
            
            queue2.Find(0, job);

            // �����ǰʱ���Ѿ�������ҵ����ʱ�䣬ִ����ҵ
            if (job.arrivalTime <= now) {
                if (job.executionTime <= slice2) {
                    now += job.executionTime;
                    output << "ִ�������ҵ��" << job
                        << "\n�ȴ�ʱ�䣺" << (now - job.executionTime - job.arrivalTime)
                        << "\t��תʱ�䣺" << (now - job.arrivalTime)
                        << "\t��Ȩ��תʱ�䣺" << (double(now - job.arrivalTime) / job.executionTime)
                        << "\n";
                    total++;
                    totalWait += now - job.executionTime - job.arrivalTime;
                    totalTurnover += now - job.arrivalTime;
                    totalRightTurnover += double(now - job.arrivalTime) / job.executionTime;

                    queue2.Delete(0);
                }
                else {
                    // ���ִ��ʱ�䳬��ʱ��Ƭ��С����ʣ�ಿ����Ȼ���� Q2 �� 
                    now += slice2;
                    output << "ִ����ʱ��Ƭ��" << slice2 << "����ҵ��" << job << "\n";
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

    output << "\nƽ���ȴ�ʱ�䣺" << (totalWait / total)
        << "\tƽ����תʱ�䣺" << (totalTurnover / total)
        << "\tƽ����Ȩ��תʱ�䣺" << (totalRightTurnover / total)
        << "\n";
}
