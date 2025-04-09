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
};

int gcd(int a, int b) {
    return (b == 0) ? a : gcd(b, a % b);
}

int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

int calcHyperPeriod(struct Task tasks[], int n) {
    int h = tasks[0].period;
    for (int i = 1; i < n; i++) {
        h = lcm(h, tasks[i].period);
    }
    return h;
}

// Rate Monotonic Scheduling
void rms(struct Task tasks[], int n) {
    int time, hyperPeriod = calcHyperPeriod(tasks, n);
    printf("\nRMS Schedule:\n");

    for (time = 0; time < hyperPeriod; time++) {
        int min_period = 9999, current = -1;

        for (int i = 0; i < n; i++) {
            if (time == tasks[i].next_arrival) {
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].next_arrival += tasks[i].period;
            }
            if (tasks[i].remaining_time > 0 && tasks[i].period < min_period) {
                min_period = tasks[i].period;
                current = i;
            }
        }

        if (current != -1) {
            printf("Time %d: Task %d\n", time, tasks[current].id);
            tasks[current].remaining_time--;
        } else {
            printf("Time %d: Idle\n", time);
        }
    }
}

// Earliest Deadline First Scheduling
void edf(struct Task tasks[], int n) {
    int time, hyperPeriod = calcHyperPeriod(tasks, n);
    printf("\nEDF Schedule:\n");

    for (time = 0; time < hyperPeriod; time++) {
        int min_deadline = 9999, current = -1;

        for (int i = 0; i < n; i++) {
            if (time == tasks[i].next_arrival) {
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].deadline = time + tasks[i].period;
                tasks[i].next_arrival += tasks[i].period;
            }
            if (tasks[i].remaining_time > 0 && tasks[i].deadline < min_deadline) {
                min_deadline = tasks[i].deadline;
                current = i;
            }
        }

        if (current != -1) {
            printf("Time %d: Task %d\n", time, tasks[current].id);
            tasks[current].remaining_time--;
        } else {
            printf("Time %d: Idle\n", time);
        }
    }
}

int main() {
    int n;
    struct Task tasks[MAX];

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("Task %d - Execution Time: ", i + 1);
        scanf("%d", &tasks[i].execution_time);
        printf("Task %d - Period: ", i + 1);
        scanf("%d", &tasks[i].period);
        tasks[i].remaining_time = 0;
        tasks[i].next_arrival = 0;
        tasks[i].deadline = tasks[i].period;  // default
    }

    int choice;
    do {
        printf("\nChoose Scheduling Algorithm:\n");
        printf("1. Rate-Monotonic Scheduling (RMS)\n");
        printf("2. Earliest-Deadline First (EDF)\n");
        printf("3. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1 || choice == 2) {
            // Reset task state
            for (int i = 0; i < n; i++) {
                tasks[i].remaining_time = 0;
                tasks[i].next_arrival = 0;
                tasks[i].deadline = tasks[i].period;
            }
        }

        switch (choice) {
        case 1:
            rms(tasks, n);
            break;
        case 2:
            edf(tasks, n);
            break;
        case 3:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 3);

    return 0;
}
