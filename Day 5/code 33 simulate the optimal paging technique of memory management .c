#include <stdio.h>
#include <stdlib.h>

#define NUM_PAGES 4
#define NUM_FRAMES 3

void optimalPageReplace(int pages[], int num_pages, int frames[], int num_frames) {
    int page_faults = 0;
    int i, j, k, max, page_to_replace;
    int page_in_frame[num_frames];

    for (i = 0; i < num_frames; i++)
        page_in_frame[i] = -1;

    for (i = 0; i < num_pages; i++) {
        int page = pages[i];
        int page_found = 0;
        for (j = 0; j < num_frames; j++) {
            if (page_in_frame[j] == page) {
                page_found = 1;
                break;
            }
        }

        if (!page_found) {
            page_faults++;
            if (i < num_frames) {
                page_in_frame[i] = page;
            } else {
                int found = 0;
                for (j = 0; j < num_frames; j++) {
                    int next_occurrence = -1;
                    for (k = i + 1; k < num_pages; k++) {
                        if (page_in_frame[j] == pages[k]) {
                            next_occurrence = k;
                            break;
                        }
                    }
                    if (next_occurrence == -1) {
                        page_to_replace = j;
                        found = 1;
                        break;
                    }
                    if (next_occurrence > max) {
                        max = next_occurrence;
                        page_to_replace = j;
                    }
                }
                if (!found) {
                    page_in_frame[page_to_replace] = page;
                }
            }
        }

        printf("Page %d -> [ ", page);
        for (j = 0; j < num_frames; j++) {
            printf("%d ", page_in_frame[j]);
        }
        printf("]\n");
    }

    printf("Total Page Faults: %d\n", page_faults);
}

int main() {
    int pages[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int frames[NUM_FRAMES];
    optimalPageReplace(pages, sizeof(pages)/sizeof(pages[0]), frames, NUM_FRAMES);
    return 0;
}
