#include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};

void findAvgTime(struct Process proc[], int n, int time_quantum) {
    int time = 0;
    int completed = 0;

    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
    }

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0) {
                if (proc[i].remaining_time > time_quantum) {
                    time += time_quantum;
                    proc[i].remaining_time -= time_quantum;
                } else {
                    time += proc[i].remaining_time;
                    proc[i].waiting_time = time - proc[i].burst_time;
                    proc[i].turnaround_time = time;
                    proc[i].remaining_time = 0;
                    completed++;
                }
            }
        }
    }
}

int main() {
    int n, time_quantum;

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

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    if (time_quantum <= 0) {
        printf("Time quantum must be greater than 0.\n");
        return 1;
    }

    findAvgTime(proc, n, time_quantum);

    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].id,
               proc[i].burst_time,
               proc[i].waiting_time,
               proc[i].turnaround_time);
    }

    return 0;
}
