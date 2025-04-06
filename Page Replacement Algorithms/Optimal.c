#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 3
#define MAX_PAGES 10

int findOptimal(int pages[], int frames[], int n, int index) {
    int farthest = -1, pos = -1;

    for (int i = 0; i < MAX_FRAMES; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == n) return i; // Page not found in future, best to replace
    }
    return (pos == -1) ? 0 : pos;
}

void optimal(int pages[], int n) {
    int frames[MAX_FRAMES], count = 0;

    for (int i = 0; i < MAX_FRAMES; i++)
        frames[i] = -1;

    printf("\nOptimal Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        bool found = false;

        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == pages[i]) {
                found = true;
                break;
            }
        }

        if (!found) {
            int pos = (i < MAX_FRAMES) ? i : findOptimal(pages, frames, n, i);
            frames[pos] = pages[i];
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
    optimal(pages, MAX_PAGES);
    return 0;
}
