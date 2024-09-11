#include <stdio.h>
#include <unistd.h> // For sleep function

void findWaitingTime(int processes[], int n, int burstTime[], int waitingTime[]) {
    int completed[n], min, time = 0, count = 0, shortest;
    for (int i = 0; i < n; i++) completed[i] = 0; // Initialize all processes as incomplete

    while (count < n) {
        shortest = -1;
        min = 1e9; // Large value for comparison

        // Find the shortest job that is not yet completed
        for (int i = 0; i < n; i++) {
            if (completed[i] == 0 && burstTime[i] < min) {
                min = burstTime[i];
                shortest = i;
            }
        }

        // If a valid shortest job is found
        if (shortest != -1) {
            time += burstTime[shortest]; // Increment the current time by the burst time of the selected process
            waitingTime[shortest] = time - burstTime[shortest]; // Calculate the waiting time
            completed[shortest] = 1; // Mark the process as completed
            count++; // Increment count of completed processes

            // Simulate the execution of the current process
            printf("Process %d is executing for %d seconds...\n", shortest + 1, burstTime[shortest]);
            sleep(burstTime[shortest]); // Sleep for burst time duration
            printf("Process %d has finished execution.\n", shortest + 1);
        }
    }
}

void findTurnAroundTime(int processes[], int n, int burstTime[], int waitingTime[], int turnAroundTime[]) {
    for (int i = 0; i < n; i++) {
        turnAroundTime[i] = burstTime[i] + waitingTime[i]; // Calculate turn around time for each process
    }
}

void findAverageTime(int processes[], int n, int burstTime[]) {
    int waitingTime[n], turnAroundTime[n], totalWaitingTime = 0, totalTurnAroundTime = 0;

    findWaitingTime(processes, n, burstTime, waitingTime); // Find the waiting time for each process
    findTurnAroundTime(processes, n, burstTime, waitingTime, turnAroundTime); // Find the turn around time for each process

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
    int processes[] = {1, 2, 3}; // Process IDs
    int n = sizeof(processes) / sizeof(processes[0]);
    int burstTime[] = {6, 2, 8}; // Burst times in seconds for each process

    findAverageTime(processes, n, burstTime);
    return 0;
}
