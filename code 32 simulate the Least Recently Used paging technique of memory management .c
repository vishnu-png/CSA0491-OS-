#include <stdio.h>

#define MAX_FRAMES 3
#define MAX_PAGES 20

void displayFrames(int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1)
            printf(" - ");
        else
            printf("%2d ", frames[i]);
    }
    printf("\n");
}

int findLRUIndex(int frames[], int n, int page, int index[]) {
    int lru = index[0];
    for (int i = 1; i < n; i++) {
        if (index[i] < lru)
            lru = index[i];
    }
    return lru;
}

void lruPageReplacement(int pages[], int n, int frames[], int frameCount) {
    int index[MAX_FRAMES];
    for (int i = 0; i < frameCount; i++)
        index[i] = -1;
    
    int page_faults = 0;
    
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int flag = 0;
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == page) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            int lru_index = findLRUIndex(frames, frameCount, page, index);
            frames[lru_index] = page;
            index[lru_index] = i;
            page_faults++;
            printf("Page %d inserted at Frame[%d]: ", page, lru_index);
            displayFrames(frames, frameCount);
        } else {
            printf("Page %d already present: ", page);
            displayFrames(frames, frameCount);
        }
    }
    
    printf("\nTotal Page Faults: %d\n", page_faults);
}

int main() {
    int pages[MAX_PAGES], frames[MAX_FRAMES];
    int n, frameCount;
    
    printf("Enter number of pages: ");
    scanf("%d", &n);
    
    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    
    printf("Enter number of frames: ");
    scanf("%d", &frameCount);
    
    printf("\n");

    for (int i = 0; i < frameCount; i++)
        frames[i] = -1;
    
    lruPageReplacement(pages, n, frames, frameCount);
    
    return 0;
}
