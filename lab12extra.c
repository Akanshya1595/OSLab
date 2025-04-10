#include <stdio.h>
#include <stdlib.h>

#define MAX 10

struct Task {
    int id;
    int execution_time;
    int period;
    int deadline;
    int remaining_time;
    int next_arrival;
    int absolute_deadline;
};

// Utility functions
int gcd(int a, int b) { return (b == 0) ? a : gcd(b, a % b); }
int lcm(int a, int b) { return a * b / gcd(a, b); }

int calcHyperPeriod(struct Task tasks[], int n) {
    int h = tasks[0].period;
    for (int i = 1; i < n; i++) h = lcm(h, tasks[i].period);
    return h;
}

// Rate Monotonic Scheduling
void rms(struct Task tasks[], int n) {
    int hyper = calcHyperPeriod(tasks, n);
    printf("\nRMS Schedule:\n");
    for (int t = 0; t < hyper; t++) {
        int curr = -1, min_period = 9999;
        for (int i = 0; i < n; i++) {
            if (t == tasks[i].next_arrival) {
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].next_arrival += tasks[i].period;
            }
            if (tasks[i].remaining_time > 0 && tasks[i].period < min_period) {
                min_period = tasks[i].period;
                curr = i;
            }
        }
        if (curr != -1) {
            printf("Time %d: Task %d\n", t, tasks[curr].id);
            tasks[curr].remaining_time--;
        } else printf("Time %d: Idle\n", t);
    }
}

// Earliest Deadline First
void edf(struct Task tasks[], int n) {
    int hyper = calcHyperPeriod(tasks, n);
    printf("\nEDF Schedule:\n");
    for (int t = 0; t < hyper; t++) {
        int curr = -1, min_deadline = 9999;
        for (int i = 0; i < n; i++) {
            if (t == tasks[i].next_arrival) {
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].absolute_deadline = t + tasks[i].deadline;
                tasks[i].next_arrival += tasks[i].period;
            }
            if (tasks[i].remaining_time > 0 && tasks[i].absolute_deadline < min_deadline) {
                min_deadline = tasks[i].absolute_deadline;
                curr = i;
            }
        }
        if (curr != -1) {
            printf("Time %d: Task %d\n", t, tasks[curr].id);
            tasks[curr].remaining_time--;
        } else printf("Time %d: Idle\n", t);
    }
}

// Least Laxity First
void llf(struct Task tasks[], int n) {
    int hyper = calcHyperPeriod(tasks, n);
    printf("\nLLF Schedule:\n");
    for (int t = 0; t < hyper; t++) {
        int curr = -1, min_laxity = 9999;
        for (int i = 0; i < n; i++) {
            if (t == tasks[i].next_arrival) {
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].absolute_deadline = t + tasks[i].deadline;
                tasks[i].next_arrival += tasks[i].period;
            }
            int laxity = tasks[i].absolute_deadline - t - tasks[i].remaining_time;
            if (tasks[i].remaining_time > 0 && laxity < min_laxity) {
                min_laxity = laxity;
                curr = i;
            }
        }
        if (curr != -1) {
            printf("Time %d: Task %d\n", t, tasks[curr].id);
            tasks[curr].remaining_time--;
        } else printf("Time %d: Idle\n", t);
    }
}

// Deadline Monotonic Scheduling
void dms(struct Task tasks[], int n) {
    int hyper = calcHyperPeriod(tasks, n);
    printf("\nDMS Schedule:\n");
    for (int t = 0; t < hyper; t++) {
        int curr = -1, min_deadline = 9999;
        for (int i = 0; i < n; i++) {
            if (t == tasks[i].next_arrival) {
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].next_arrival += tasks[i].period;
            }
            if (tasks[i].remaining_time > 0 && tasks[i].deadline < min_deadline) {
                min_deadline = tasks[i].deadline;
                curr = i;
            }
        }
        if (curr != -1) {
            printf("Time %d: Task %d\n", t, tasks[curr].id);
            tasks[curr].remaining_time--;
        } else printf("Time %d: Idle\n", t);
    }
}

// Main Program
int main() {
    int n, choice;
    struct Task tasks[MAX];

    printf("Enter number of tasks: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("Task %d - Execution Time: ", i + 1);
        scanf("%d", &tasks[i].execution_time);
        printf("Task %d - Period: ", i + 1);
        scanf("%d", &tasks[i].period);
        tasks[i].deadline = tasks[i].period; // Default deadline = period
    }

    do {
        for (int i = 0; i < n; i++) {
            tasks[i].remaining_time = 0;
            tasks[i].next_arrival = 0;
            tasks[i].absolute_deadline = tasks[i].period;
        }

        printf("\nChoose Scheduler:\n");
        printf("1. RMS\n2. EDF\n3. LLF\n4. DMS\n5. Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: rms(tasks, n); break;
            case 2: edf(tasks, n); break;
            case 3: llf(tasks, n); break;
            case 4: dms(tasks, n); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
