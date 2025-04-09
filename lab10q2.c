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

// LRU 
void lru(int *pages, int num_pages, int num_frames) {
    int *frames = (int *)malloc(num_frames * sizeof(int));
    int *last_used = (int *)malloc(num_frames * sizeof(int));
    int page_faults = 0;
    
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
        last_used[i] = 0;
    }
    
    printf("\n=== LRU Replacement ===\n");
    
    for (int i = 0; i < num_pages; i++) {
        printf("Reference: %d, ", pages[i]);
        
        int page_index = is_page_present(frames, num_frames, pages[i]);
        
        if (page_index != -1) {
            
            printf("Hit, ");
            last_used[page_index] = i;
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
                last_used[empty_frame] = i;
            } else {
                int lru_index = 0;
                for (int j = 1; j < num_frames; j++) {
                    if (last_used[j] < last_used[lru_index]) {
                        lru_index = j;
                    }
                }
                
                frames[lru_index] = pages[i];
                last_used[lru_index] = i;
            }
        }
        
        print_frames(frames, num_frames);
    }
    
    printf("\nTotal Page Faults (LRU): %d\n", page_faults);
    printf("Hit Ratio (LRU): %.2f%%\n", ((float)(num_pages - page_faults) / num_pages) * 100);
    
    free(frames);
    free(last_used);
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
    
    lru(pages, num_pages, num_frames);
    
    free(pages);
    
    return 0;
}
