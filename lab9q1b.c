#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int size;
    int original_size;
    int allocated;
} Hole;

typedef struct {
    int id;
    int size;
    int allocated_hole;
} Process;

void best_fit_allocation(Hole holes[], int nh, Process processes[], int np) {
    for (int i = 0; i < np; i++) {
        int best_fit_index = -1;
        int smallest_hole_size = __INT_MAX__;

        for (int j = 0; j < nh; j++) {
            if (holes[j].size >= processes[i].size && holes[j].size < smallest_hole_size) {
                best_fit_index = j;
                smallest_hole_size = holes[j].size;
            }
        }

        if (best_fit_index != -1) {
            processes[i].allocated_hole = holes[best_fit_index].id;
            holes[best_fit_index].size -= processes[i].size;
            holes[best_fit_index].allocated = 1;
        }
    }
}

int main() {
    int nh, np;
    
    printf("Enter the number of holes: ");
    scanf("%d", &nh);

    Hole *holes = (Hole *)malloc(nh * sizeof(Hole));
    
    printf("Enter the size of each hole:\n");
    for (int i = 0; i < nh; i++) {
        printf("Size of hole %d: ", i + 1);
        scanf("%d", &holes[i].size);
        holes[i].original_size = holes[i].size;
        holes[i].id = i + 1;
        holes[i].allocated = 0;
    }

    printf("Enter the number of processes: ");
    scanf("%d", &np);

    Process *processes = (Process *)malloc(np * sizeof(Process));
    
    printf("Enter the memory requirements for each process:\n");
    for (int i = 0; i < np; i++) {
        printf("Size of process %d: ", i + 1);
        scanf("%d", &processes[i].size);
        processes[i].id = i + 1;
        processes[i].allocated_hole = 0;
    }

    best_fit_allocation(holes, nh, processes, np);

    printf("\nProcess Allocation:\n");
    for (int i = 0; i < np; i++) {
        if (processes[i].allocated_hole) {
            printf("Process %d allocated to hole %d\n", 
                   processes[i].id, processes[i].allocated_hole);
        } else {
            printf("Process %d not allocated\n", processes[i].id);
        }
    }

    printf("\nHole Availability:\n");
    for (int i = 0; i < nh; i++) {
        printf("Hole %d: Original size = %d, Current size = %d\n", 
               holes[i].id, holes[i].original_size, holes[i].size);
    }

    free(holes);
    free(processes);
    
    return 0;
}
