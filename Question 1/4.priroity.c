#include <stdio.h>

void findWaitingTime(int processes[], int n, int burstTime[], int waitingTime[], int priority[]) {
    int completed[n], min, time = 0, count = 0, highestPriority;
    for (int i = 0; i < n; i++) completed[i] = 0;

    while (count < n) {
        highestPriority = -1;
        min = 1e9; // Large value for comparison

        for (int i = 0; i < n; i++) {
            if (completed[i] == 0 && priority[i] < min) {
                min = priority[i];
                highestPriority = i;
            }
        }

        time += burstTime[highestPriority];
        waitingTime[highestPriority] = time - burstTime[highestPriority];
        completed[highestPriority] = 1;
        count++;
    }
}

void findTurnAroundTime(int processes[], int n, int burstTime[], int waitingTime[], int turnAroundTime[]) {
    for (int i = 0; i < n; i++) {
        turnAroundTime[i] = burstTime[i] + waitingTime[i];
    }
}

void findAverageTime(int processes[], int n, int burstTime[], int priority[]) {
    int waitingTime[n], turnAroundTime[n], totalWaitingTime = 0, totalTurnAroundTime = 0;

    findWaitingTime(processes, n, burstTime, waitingTime, priority);
    findTurnAroundTime(processes, n, burstTime, waitingTime, turnAroundTime);

    printf("Processes\tBurst Time\tPriority\tWaiting Time\tTurn Around Time\n");
    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnAroundTime += turnAroundTime[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, burstTime[i], priority[i], waitingTime[i], turnAroundTime[i]);
    }

    printf("Average waiting time = %.2f\n", (float)totalWaitingTime / n);
    printf("Average turn around time = %.2f\n", (float)totalTurnAroundTime / n);
}

int main() {
    int processes[] = {1, 2, 3};
    int n = sizeof(processes) / sizeof(processes[0]);
    int burstTime[] = {10, 5, 8};
    int priority[] = {2, 1, 3};

    findAverageTime(processes, n, burstTime, priority);
    return 0;
}
