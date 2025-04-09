#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void sstf(int requests[], int n, int head) {
    int total = 0, visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    printf("SSTF Order: ");
    for (int i = 0; i < n; i++) {
        int min = 1e9, index = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && abs(head - requests[j]) < min) {
                min = abs(head - requests[j]);
                index = j;
            }
        }
        total += abs(head - requests[index]);
        head = requests[index];
        visited[index] = 1;
        printf("%d ", head);
    }
    printf("\nTotal Head Movement: %d\n", total);
}

void scan(int requests[], int n, int head, int disk_size, char direction) {
    int total = 0;
    requests[n++] = head;
    requests[n++] = (direction == 'L') ? 0 : disk_size - 1;

    qsort(requests, n, sizeof(int), compare);

    int pos;
    for (pos = 0; pos < n; pos++)
        if (requests[pos] == head)
            break;

    printf("SCAN Order: ");
    if (direction == 'L') {
        for (int i = pos; i >= 0; i--) {
            printf("%d ", requests[i]);
            if (i > 0) total += abs(requests[i] - requests[i - 1]);
        }
        for (int i = pos + 1; i < n; i++) {
            printf("%d ", requests[i]);
            total += abs(requests[i] - requests[i - 1]);
        }
    } else {
        for (int i = pos; i < n; i++) {
            printf("%d ", requests[i]);
            if (i < n - 1) total += abs(requests[i] - requests[i + 1]);
        }
        for (int i = pos - 1; i >= 0; i--) {
            printf("%d ", requests[i]);
            if (i > 0) total += abs(requests[i] - requests[i - 1]);
        }
    }

    printf("\nTotal Head Movement: %d\n", total);
}

void cscan(int requests[], int n, int head, int disk_size) {
    int total = 0;
    requests[n++] = head;
    requests[n++] = 0;
    requests[n++] = disk_size - 1;

    qsort(requests, n, sizeof(int), compare);

    int pos;
    for (pos = 0; pos < n; pos++)
        if (requests[pos] == head)
            break;

    printf("C-SCAN Order: ");
    for (int i = pos; i < n; i++) {
        printf("%d ", requests[i]);
        if (i < n - 1) total += abs(requests[i] - requests[i + 1]);
    }
    for (int i = 0; i < pos; i++) {
        printf("%d ", requests[i]);
        if (i < pos - 1) total += abs(requests[i] - requests[i + 1]);
    }

    printf("\nTotal Head Movement: %d\n", total);
}

void clook(int requests[], int n, int head) {
    int total = 0;
    requests[n++] = head;

    qsort(requests, n, sizeof(int), compare);

    int pos;
    for (pos = 0; pos < n; pos++)
        if (requests[pos] == head)
            break;

    printf("C-LOOK Order: ");
    for (int i = pos; i < n; i++) {
        printf("%d ", requests[i]);
        if (i < n - 1) total += abs(requests[i] - requests[i + 1]);
    }
    for (int i = 0; i < pos; i++) {
        printf("%d ", requests[i]);
        if (i < pos - 1) total += abs(requests[i] - requests[i + 1]);
    }

    printf("\nTotal Head Movement: %d\n", total);
}

int main() {
    int choice, n, head, disk_size, requests[100];

    printf("Enter number of requests: ");
    scanf("%d", &n);
    printf("Enter request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    do {
        printf("\nDisk Scheduling Menu\n");
        printf("1. SSTF\n2. SCAN\n3. C-SCAN\n4. C-LOOK\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            sstf(requests, n, head);
            break;
        case 2: {
            char dir;
            printf("Enter direction (L for left, R for right): ");
            scanf(" %c", &dir);
            scan(requests, n, head, disk_size, dir);
            break;
        }
        case 3:
            cscan(requests, n, head, disk_size);
            break;
        case 4:
            clook(requests, n, head);
            break;
        case 5:
            printf("Exiting.\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);

    return 0;
}
