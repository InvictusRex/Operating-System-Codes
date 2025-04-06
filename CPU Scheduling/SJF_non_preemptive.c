#include <stdio.h>
#include <stdbool.h>

void findWaitingTime(int processes[], int n, int bt[], int at[], int wt[]) {
    int service_time[n];
    service_time[0] = 0;
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        service_time[i] = service_time[i - 1] + bt[i - 1];
        wt[i] = service_time[i] - at[i];
        if (wt[i] < 0) {
            wt[i] = 0;
        }
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

void sortProcesses(int processes[], int n, int bt[], int at[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                int temp_bt = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp_bt;

                int temp_at = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp_at;

                int temp_pid = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp_pid;
            }
        }
    }
}

int main() {
    int processes[] = { 1, 2, 3, 4 };
    int n = sizeof(processes) / sizeof(processes[0]);
    int burst_time[] = { 10, 5, 8, 12 };
    int arrival_time[] = { 0, 1, 2, 3 };
    sortProcesses(processes, n, burst_time, arrival_time);
    findavgTime(processes, n, burst_time, arrival_time);
    return 0;
}
