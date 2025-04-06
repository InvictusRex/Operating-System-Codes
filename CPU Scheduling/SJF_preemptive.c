#include <stdio.h>
#include <limits.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[]) {
    int remaining_time[n];
    for (int i = 0; i < n; i++)
        remaining_time[i] = bt[i];
    int complete = 0, t = 0;
    int min_time = INT_MAX, min_index = -1;
    bool found;

    while (complete < n) {
        found = false;
        min_time = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (remaining_time[j] > 0 && remaining_time[j] < min_time) {
                min_time = remaining_time[j];
                min_index = j;
                found = true;
            }
        }

        if (!found) {
            t++;
            continue;
        }

        remaining_time[min_index]--;

        if (remaining_time[min_index] == 0) {
            complete++;
            wt[min_index] = t + 1 - bt[min_index];
        }

        t++;
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

void findavgTime(int processes[], int n, int bt[]) {
    int wt[n], tat[n];
    findWaitingTime(processes, n, bt, wt);
    findTurnAroundTime(processes, n, bt, wt, tat);
    printf("Processes\tBurst Time\tWaiting Time\tTurn-Around Time\n");
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("    %d\t\t    %d\t\t    %d\t\t    %d\n", processes[i], bt[i], wt[i], tat[i]);
    }
    printf("\nAverage waiting time = %.2f\n", (float)total_wt / n);
    printf("Average turn-around time = %.2f\n", (float)total_tat / n);
}

int main() {
    int processes[] = { 1, 2, 3, 4 };
    int n = sizeof(processes) / sizeof(processes[0]);
    int burst_time[] = { 10, 5, 8, 12 };
    findavgTime(processes, n, burst_time);
    return 0;
}
