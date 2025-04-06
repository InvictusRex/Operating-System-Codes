#include <stdio.h>
#define MAX_FRAMES 3
#define MAX_PAGES 10

int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; ++i) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

void lru(int pages[], int n) {
    int frames[MAX_FRAMES], time[MAX_FRAMES];
    int count = 0, timer = 0;

    for (int i = 0; i < MAX_FRAMES; i++)
        frames[i] = -1;

    printf("\nLRU Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                time[j] = timer++;
                break;
            }
        }

        if (!found) {
            int pos = (i < MAX_FRAMES) ? i : findLRU(time, MAX_FRAMES);
            frames[pos] = pages[i];
            time[pos] = timer++;
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
    lru(pages, MAX_PAGES);
    return 0;
}
