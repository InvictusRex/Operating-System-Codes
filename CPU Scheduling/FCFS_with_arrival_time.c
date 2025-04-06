#include <stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int at[], int wt[]) {
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
        if (wt[i] < at[i])
            wt[i] = at[i];
        wt[i] -= at[i];
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

void findavgTime(int processes[], int n, int bt[], int at[]) {
    int wt[n], tat[n];
    findWaitingTime(processes, n, bt, at, wt);
    findTurnAroundTime(processes, n, bt, wt, tat);

    printf("Processes\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time\n");
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("    %d\t\t    %d\t\t    %d\t\t    %d\t\t    %d\n", processes[i], bt[i], at[i], wt[i], tat[i]);
    }

    printf("\nAverage waiting time = %.2f\n", (float)total_wt / n);
    printf("Average turn-around time = %.2f\n", (float)total_tat / n);
}

int main() {
    int processes[] = { 1, 2, 3, 4 };
    int n = sizeof(processes) / sizeof(processes[0]);
    int burst_time[] = { 10, 5, 8, 12 };
    int arrival_time[] = { 0, 1, 2, 3 };

    findavgTime(processes, n, burst_time, arrival_time);
    return 0;
}
