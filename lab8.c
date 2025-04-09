#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 3 // Number of resource types

int available[R]; // Available resources
int max[P][R];    // Max demand of each process
int allocation[P][R]; // Resources allocated to each process
int need[P][R];   // Remaining need of each process

bool isSafe() {
    int work[R];
    bool finish[P] = {false};

    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < R; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }

        if (!found) {
            return false;
        }
    }
    return true;
}

bool requestResources(int process, int request[R]) {
    for (int i = 0; i < R; i++) {
        if (request[i] > need[process][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
        if (request[i] > available[i]) {
            printf("Resources not available, process must wait.\n");
            return false;
        }
    }

    // Tentatively allocate resources
    for (int i = 0; i < R; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    if (!isSafe()) {
        // Rollback
        for (int i = 0; i < R; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
        printf("Request denied to keep the system in a safe state.\n");
        return false;
    }

    printf("Request granted. System remains in a safe state.\n");
    return true;
}

int main() {
    printf("Enter available resources (%d types):\n", R);
    for (int i = 0; i < R; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter maximum demand matrix (%d x %d):\n", P, R);
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter allocation matrix (%d x %d):\n", P, R);
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    if (isSafe()) {
        printf("System is in a safe state.\n");
    } else {
        printf("System is NOT in a safe state.\n");
    }

    int process, request[R];
    printf("Enter process number (0 to %d) requesting resources: ", P - 1);
    scanf("%d", &process);

    if (process < 0 || process >= P) {
        printf("Invalid process number.\n");
        return 1;
    }

    printf("Enter request vector for process %d (%d values):\n", process, R);
    for (int i = 0; i < R; i++) {
        scanf("%d", &request[i]);
    }

    requestResources(process, request);

    return 0;
}
