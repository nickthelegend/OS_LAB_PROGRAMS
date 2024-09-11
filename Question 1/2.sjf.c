/// Shortest Job First



#include <stdio.h>

void findWaitingTime(int processes[], int n, int burstTime[], int waitingTime[]) {
    int completed[n], min, time = 0, count = 0, shortest;
    for (int i = 0; i < n; i++) completed[i] = 0;

    while (count < n) {
        shortest = -1;
        min = 1e9; // Large value for comparison

        for (int i = 0; i < n; i++) {
            if (completed[i] == 0 && burstTime[i] < min) {
                min = burstTime[i];
                shortest = i;
            }
        }

        time += burstTime[shortest];
        waitingTime[shortest] = time - burstTime[shortest];
        completed[shortest] = 1;
        count++;
    }
}

void findTurnAroundTime(int processes[], int n, int burstTime[], int waitingTime[], int turnAroundTime[]) {
    for (int i = 0; i < n; i++) {
        turnAroundTime[i] = burstTime[i] + waitingTime[i];
    }
}

void findAverageTime(int processes[], int n, int burstTime[]) {
    int waitingTime[n], turnAroundTime[n], totalWaitingTime = 0, totalTurnAroundTime = 0;

    findWaitingTime(processes, n, burstTime, waitingTime);
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

    findAverageTime(processes, n, burstTime);
    return 0;
}
