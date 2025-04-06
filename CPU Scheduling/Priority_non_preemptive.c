#include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

void findWaitingTime(struct Process proc[], int n) {
    proc[0].waiting_time = 0;
    for (int i = 1; i < n; i++) {
        proc[i].waiting_time = proc[i - 1].waiting_time + proc[i - 1].burst_time;
    }
}

void findTurnAroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;
    }
}

void findAvgTime(struct Process proc[], int n) {
    findWaitingTime(proc, n);
    findTurnAroundTime(proc, n);

    float total_waiting_time = 0, total_turnaround_time = 0;

    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_waiting_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;

        printf("%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].id,
               proc[i].burst_time,
               proc[i].waiting_time,
               proc[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of processes must be greater than 0.\n");
        return 1;
    }

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Enter burst time for Process %d: ", proc[i].id);
        scanf("%d", &proc[i].burst_time);

        if (proc[i].burst_time < 0) {
            printf("Burst time must be non-negative.\n");
            return 1;
        }
    }

    findAvgTime(proc, n);
    return 0;
}