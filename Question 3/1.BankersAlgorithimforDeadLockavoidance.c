#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

// Function prototypes
void calculateNeed();
bool isSafe();
void requestResources(int process_id);
void releaseResources(int process_id);

int processes[MAX_PROCESSES]; // Process IDs
int maxResources[MAX_PROCESSES][MAX_RESOURCES]; // Maximum resources required by each process
int allocation[MAX_PROCESSES][MAX_RESOURCES]; // Resources currently allocated to each process
int need[MAX_PROCESSES][MAX_RESOURCES]; // Resources needed by each process
int available[MAX_RESOURCES]; // Available instances of resources

int main() {
    int n, m; // Number of processes and resources

    // Input the number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    // Input maximum resource matrix
    printf("Enter the maximum resources required by each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i] = i;
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &maxResources[i][j]);
        }
    }

    // Input allocation matrix
    printf("Enter the resources currently allocated to each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input available resources
    printf("Enter the available resources:\n");
    for (int j = 0; j < m; j++) {
        scanf("%d", &available[j]);
    }

    // Calculate the need matrix
    calculateNeed(n, m);

    // Display the available, maximum, allocation, and need matrices
    printf("\nAvailable resources: ");
    for (int j = 0; j < m; j++) {
        printf("%d ", available[j]);
    }

    printf("\nMaximum resources:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++) {
            printf("%d ", maxResources[i][j]);
        }
        printf("\n");
    }

    printf("Allocated resources:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }

    printf("Need resources:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Check for a safe state
    if (isSafe(n, m)) {
        printf("\nThe system is in a safe state.\n");
    } else {
        printf("\nThe system is not in a safe state.\n");
    }

    // Request resources for a process
    int process_id;
    printf("\nRequest resources for a process (enter process ID): ");
    scanf("%d", &process_id);
    requestResources(process_id);

    return 0;
}

void calculateNeed(int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = maxResources[i][j] - allocation[i][j];
        }
    }
}

bool isSafe(int n, int m) {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = { false };
    
    for (int j = 0; j < m; j++) {
        work[j] = available[j];
    }

    int safeSequence[MAX_PROCESSES];
    int count = 0;

    while (count < n) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[p][j] > work[j]) {
                        break;
                    }
                }
                if (j == m) { // If all resources can be allocated
                    for (int k = 0; k < m; k++) {
                        work[k] += allocation[p][k];
                    }
                    safeSequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            break;
        }
    }

    if (count < n) {
        return false; // Not in a safe state
    }

    printf("Safe sequence is: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", safeSequence[i]);
    }
    printf("\n");
    
    return true;
}

void requestResources(int process_id) {
    int request[MAX_RESOURCES];
    int n = sizeof(processes) / sizeof(processes[0]); // Assuming the size of processes is the number of processes
    int m; // Number of resources (assumed globally for simplicity)

    printf("Enter request for process %d:\n", process_id);
    for (int j = 0; j < m; j++) {
        scanf("%d", &request[j]);
    }

    // Check if request is less than or equal to the need
    for (int j = 0; j < m; j++) {
        if (request[j] > need[process_id][j]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return;
        }
    }

    // Check if request is less than or equal to available resources
    for (int j = 0; j < m; j++) {
        if (request[j] > available[j]) {
            printf("Process is waiting (resources not available).\n");
            return;
        }
    }

    // Temporarily allocate resources
    for (int j = 0; j < m; j++) {
        available[j] -= request[j];
        allocation[process_id][j] += request[j];
        need[process_id][j] -= request[j];
    }

    // Check for safe state after allocation
    if (isSafe(n, m)) {
        printf("Resources allocated to process %d.\n", process_id);
    } else {
        // Rollback
        for (int j = 0; j < m; j++) {
            available[j] += request[j];
            allocation[process_id][j] -= request[j];
            need[process_id][j] += request[j];
        }
        printf("Resources cannot be allocated, system would enter unsafe state.\n");
    }
}