#include <stdio.h>

void findWaitingTime(int processes[], int n, int burstTime[], int waitingTime[], int quantum) {
    int remainingBurstTime[n];
    for (int i = 0; i < n; i++) remainingBurstTime[i] = burstTime[i];

    int time = 0;
    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (remainingBurstTime[i] > 0) {
                done = 0;
                if (remainingBurstTime[i] > quantum) {
                    time += quantum;
                    remainingBurstTime[i] -= quantum;
                } else {
                    time += remainingBurstTime[i];
                    waitingTime[i] = time - burstTime[i];
                    remainingBurstTime[i] = 0;
                }
            }
        }
        if (done) break;
    }
}

void findTurnAroundTime(int processes[], int n, int burstTime[], int waitingTime[], int turnAroundTime[]) {
    for (int i = 0; i < n; i++) {
        turnAroundTime[i] = burstTime[i] + waitingTime[i];
    }
}

void findAverageTime(int processes[], int n, int burstTime[], int quantum) {
    int waitingTime[n], turnAroundTime[n], totalWaitingTime = 0, totalTurnAroundTime = 0;

    findWaitingTime(processes, n, burstTime, waitingTime, quantum);
    findTurnAroundTime(processes, n, burstTime, waitingTime, turnAroundTime);

    printf("Processes\tBurst Time\tWaiting Time\tTurn Around Time\n");
    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnAroundTime += turnAroundTime[i];
        printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, burstTime[i], waitingTime[i], turnAroundTime[i]);
    }

    printf("Average waiting time = %.2f\n", (float)totalWaitingTime / n);
    printf("Average turn around time = %.2f\n", (float)totalTurnAroundTime / n);
}

int main() {
    int processes[] = {1, 2, 3};
    int n = sizeof(processes) / sizeof(processes[0]);
    int burstTime[] = {10, 5, 8};
    int quantum = 2;

    findAverageTime(processes, n, burstTime, quantum);
    return 0;
}
