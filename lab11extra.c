#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void fcfs(int requests[], int n, int head) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += abs(requests[i] - head);
        head = requests[i];
    }
    printf("FCFS Total Head Movement: %d\n", total);
}

void sstf(int requests[], int n, int head) {
    int total = 0, completed = 0;
    int done[n];
    for (int i = 0; i < n; i++) done[i] = 0;

    while (completed < n) {
        int idx = -1, min = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!done[i] && abs(requests[i] - head) < min) {
                min = abs(requests[i] - head);
                idx = i;
            }
        }
        total += abs(requests[idx] - head);
        head = requests[idx];
        done[idx] = 1;
        completed++;
    }
    printf("SSTF Total Head Movement: %d\n", total);
}

void scan(int requests[], int n, int head, int disk_size) {
    int total = 0;
    int temp[n+1];
    for (int i = 0; i < n; i++) temp[i] = requests[i];
    temp[n] = head;
    n++;

    // Sort
    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if (temp[i] > temp[j]) {
                int t = temp[i]; temp[i] = temp[j]; temp[j] = t;
            }

    int pos = 0;
    while (pos < n && temp[pos] != head) pos++;

    for (int i = pos; i < n-1; i++)
        total += abs(temp[i+1] - temp[i]);
    total += abs(disk_size - 1 - temp[n-1]);
    total += abs(temp[pos - 1] - 0);
    for (int i = pos - 1; i > 0; i--)
        total += abs(temp[i] - temp[i-1]);

    printf("SCAN Total Head Movement: %d\n", total);
}

void cscan(int requests[], int n, int head, int disk_size) {
    int total = 0;
    int temp[n+1];
    for (int i = 0; i < n; i++) temp[i] = requests[i];
    temp[n] = head;
    n++;

    // Sort
    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if (temp[i] > temp[j]) {
                int t = temp[i]; temp[i] = temp[j]; temp[j] = t;
            }

    int pos = 0;
    while (pos < n && temp[pos] != head) pos++;

    for (int i = pos; i < n - 1; i++)
        total += abs(temp[i+1] - temp[i]);

    total += abs(disk_size - 1 - temp[n - 1]);  // Go to end
    total += disk_size - 1; // Jump to beginning
    total += temp[0];

    for (int i = 0; i < pos - 1; i++)
        total += abs(temp[i+1] - temp[i]);

    printf("C-SCAN Total Head Movement: %d\n", total);
}

void look(int requests[], int n, int head) {
    int total = 0;
    int temp[n+1];
    for (int i = 0; i < n; i++) temp[i] = requests[i];
    temp[n] = head;
    n++;

    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if (temp[i] > temp[j]) {
                int t = temp[i]; temp[i] = temp[j]; temp[j] = t;
            }

    int pos = 0;
    while (pos < n && temp[pos] != head) pos++;

    for (int i = pos; i < n - 1; i++)
        total += abs(temp[i+1] - temp[i]);
    for (int i = pos - 1; i >= 0; i--)
        total += abs(temp[i+1] - temp[i]);

    printf("LOOK Total Head Movement: %d\n", total);
}

void clook(int requests[], int n, int head) {
    int total = 0;
    int temp[n+1];
    for (int i = 0; i < n; i++) temp[i] = requests[i];
    temp[n] = head;
    n++;

    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if (temp[i] > temp[j]) {
                int t = temp[i]; temp[i] = temp[j]; temp[j] = t;
            }

    int pos = 0;
    while (pos < n && temp[pos] != head) pos++;

    for (int i = pos; i < n - 1; i++)
        total += abs(temp[i+1] - temp[i]);
    total += abs(temp[n-1] - temp[0]);
    for (int i = 0; i < pos - 1; i++)
        total += abs(temp[i+1] - temp[i]);

    printf("C-LOOK Total Head Movement: %d\n", total);
}

int main() {
    int n, disk_size, head;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);
    int requests[n];

    printf("Enter disk requests:\n");
    for (int i = 0; i < n; i++) {
        printf("Request %d: ", i+1);
        scanf("%d", &requests[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter total disk size: ");
    scanf("%d", &disk_size);

    printf("\n--- Disk Scheduling Results ---\n");
    fcfs(requests, n, head);
    sstf(requests, n, head);
    scan(requests, n, head, disk_size);
    cscan(requests, n, head, disk_size);
    look(requests, n, head);
    clook(requests, n, head);

    return 0;
}
