#include <stdio.h>
#define MAX_FRAMES 3
#define MAX_PAGES 10

void fifo(int pages[], int n) {
    int frames[MAX_FRAMES], front = 0, count = 0;

    for (int i = 0; i < MAX_FRAMES; i++)
        frames[i] = -1; // Initialize frames as empty

    printf("\nFIFO Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frames[front] = pages[i];
            front = (front + 1) % MAX_FRAMES;
            count++;
        }

        printf("Page: %d | Frames: ", pages[i]);
        for (int j = 0; j < MAX_FRAMES; j++)
            printf("%d ", frames[j]);
        printf("\n");
    }

    printf("Total Page Faults: %d\n", count);
}

int main() {
    int pages[MAX_PAGES] = {1, 3, 0, 3, 5, 6, 3, 5, 0, 3};
    fifo(pages, MAX_PAGES);
    return 0;
}
