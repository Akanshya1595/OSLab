#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void print_frames(int *frames, int num_frames) {
    printf("Frames: ");
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == -1)
            printf("[ ] ");
        else
            printf("[%d] ", frames[i]);
    }
    printf("\n");
}

int is_page_present(int *frames, int num_frames, int page) {
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == page)
            return i;
    }
    return -1;
}

// FIFO 
void fifo(int *pages, int num_pages, int num_frames) {
    int *frames = (int *)malloc(num_frames * sizeof(int));
    int page_faults = 0;
    int next_victim = 0; 
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
    }
    
    printf("\n=== FIFO Page Replacement ===\n");
    
    for (int i = 0; i < num_pages; i++) {
        printf("Reference: %d, ", pages[i]);
        
        int page_index = is_page_present(frames, num_frames, pages[i]);
        
        if (page_index != -1) {
            printf("Hit, ");
        } else {
            page_faults++;
            printf("Fault, ");
            
            frames[next_victim] = pages[i];
            next_victim = (next_victim + 1) % num_frames;
        }
        
        print_frames(frames, num_frames);
    }
    
    printf("\nTotal Page Faults (FIFO): %d\n", page_faults);
    printf("Hit Ratio (FIFO): %.2f%%\n", ((float)(num_pages - page_faults) / num_pages) * 100);
    
    free(frames);
}

// Optimal 
void optimal(int *pages, int num_pages, int num_frames) {
    int *frames = (int *)malloc(num_frames * sizeof(int));
    int page_faults = 0;
    
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
    }
    
    printf("\n=== Optimal Page Replacement ===\n");
    
    for (int i = 0; i < num_pages; i++) {
        printf("Reference: %d, ", pages[i]);
        
        int page_index = is_page_present(frames, num_frames, pages[i]);
        
        if (page_index != -1) {
            printf("Hit, ");
        } else {
            page_faults++;
            printf("Fault, ");
            
            int empty_frame = -1;
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1) {
                    empty_frame = j;
                    break;
                }
            }
            
            if (empty_frame != -1) {
                frames[empty_frame] = pages[i];
            } else {
                int victim_frame = -1;
                int farthest = -1;
                
                for (int j = 0; j < num_frames; j++) {
                    int next_use = INT_MAX;
                    
                    for (int k = i + 1; k < num_pages; k++) {
                        if (frames[j] == pages[k]) {
                            next_use = k;
                            break;
                        }
                    }
                    
                    if (next_use > farthest) {
                        farthest = next_use;
                        victim_frame = j;
                    }
                }
                
                if (victim_frame == -1) {
                    victim_frame = 0;
                }
                
                frames[victim_frame] = pages[i];
            }
        }
        
        print_frames(frames, num_frames);
    }
    
    printf("\nTotal Page Faults (Optimal): %d\n", page_faults);
    printf("Hit Ratio (Optimal): %.2f%%\n", ((float)(num_pages - page_faults) / num_pages) * 100);
    
    free(frames);
}

int main() {
    int num_frames, num_pages;
    
    printf("Enter the number of frames: ");
    scanf("%d", &num_frames);
    
    printf("Enter the number of page references: ");
    scanf("%d", &num_pages);
    
    int *pages = (int *)malloc(num_pages * sizeof(int));
    
    printf("Enter the page reference string: ");
    for (int i = 0; i < num_pages; i++) {
        scanf("%d", &pages[i]);
    }
    
    fifo(pages, num_pages, num_frames);
    optimal(pages, num_pages, num_frames);
    
    free(pages);
    
    return 0;
}
