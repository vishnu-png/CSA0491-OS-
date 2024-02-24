#include<stdio.h>
#include<stdlib.h>

int main() {
    int frames, pages, i, j, hit = 0, fault = 0, pointer = 0, found;
    
    printf("Enter the number of frames: ");
    scanf("%d", &frames);
    
    printf("Enter the number of pages: ");
    scanf("%d", &pages);
    
    int *frameArray = (int*)malloc(frames * sizeof(int));
    int *pageArray = (int*)malloc(pages * sizeof(int));
    
    printf("Enter the reference string: ");
    for(i = 0; i < pages; ++i)
        scanf("%d", &pageArray[i]);
    
    for(i = 0; i < frames; ++i)
        frameArray[i] = -1;
    
    printf("\n");
    for(i = 0; i < pages; ++i) {
        printf("Reference string: %d\n", pageArray[i]);
        found = 0;
        for(j = 0; j < frames; ++j) {
            if(frameArray[j] == pageArray[i]) {
                found = 1;
                hit++;
                break;
            }
        }
        
        if(found == 0) {
            frameArray[pointer] = pageArray[i];
            pointer = (pointer + 1) % frames;
            fault++;
        }
        
        for(j = 0; j < frames; ++j)
            printf("%d\t", frameArray[j]);
        
        printf("\n\n");
    }
    
    printf("Number of page faults: %d\n", fault);
    printf("Number of page hits: %d\n", hit);
    printf("Hit ratio: %.2f\n", (float)hit/pages);
    printf("Miss ratio: %.2f\n", (float)fault/pages);
    
    free(frameArray);
    free(pageArray);
    return 0;
}
