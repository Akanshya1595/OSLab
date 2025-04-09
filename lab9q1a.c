#include <stdio.h>

#define MAX 100

typedef struct {
    int size;
    int original_size;
    int allocated;
} Hole;

typedef struct {
    int size;
    int allocated_hole;
} Process;

void first_fit_allocation(Hole holes[], int nh, Process processes[], int np) {
    for (int i = 0; i < np; i++) {
        for (int j = 0; j < nh; j++) {
            if (holes[j].size >= processes[i].size && !processes[i].allocated_hole) { 
                processes[i].allocated_hole = j + 1;
                holes[j].size -= processes[i].size;
                holes[j].allocated = 1;
                break;
            }
        }
    }
}

int main() {
    int nh, np;
    Hole holes[MAX];
    Process processes[MAX];

    printf("Enter the number of holes: ");
    scanf("%d", &nh);
    printf("Enter the size of each hole:\n");
    for (int i = 0; i < nh; i++) {
        printf("Size of hole %d: ", i + 1);
        scanf("%d", &holes[i].size);
        holes[i].original_size = holes[i].size;
        holes[i].allocated = 0;
    }

    printf("Enter the number of processes: ");
    scanf("%d", &np);

    printf("Enter the memory requirements for each process:\n");
    for (int i = 0; i < np; i++) {
        printf("Size of process %d: ", i + 1);
        scanf("%d", &processes[i].size);
        processes[i].allocated_hole = 0; 
    }

    first_fit_allocation(holes, nh, processes, np);
    printf("\nProcess Allocation:\n");
    for (int i = 0; i < np; i++) {
        if (processes[i].allocated_hole) {
            printf("Process %d allocated to hole %d\n", i + 1, processes[i].allocated_hole);
        } else {
            printf("Process %d not allocated\n", i + 1);
        }
    }

    printf("\nHole Availability:\n");
    for (int i = 0; i < nh; i++) {
        printf("Hole %d: Original size = %d, Current size = %d\n", i + 1, holes[i].original_size, holes[i].size);
    }

    return 0;
}
