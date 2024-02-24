#include <stdio.h>

#define MAX_PROCESSES 10
#define TIME_QUANTUM 2

typedef struct {
    int process_id;
    int burst_time;
    int remaining_time;
} Process;

void round_robin(Process processes[], int n) {
    int total_time = 0;
    int completed = 0;
    int current_time = 0;
    int quantum = TIME_QUANTUM;

    printf("Round Robin Scheduling:\n");
    printf("Time\tProcess ID\n");

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time <= quantum) {
                    current_time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                } else {
                    current_time += quantum;
                    processes[i].remaining_time -= quantum;
                }

                printf("%d\t%d\n", current_time, processes[i].process_id);

                if (processes[i].remaining_time == 0) {
                    completed++;
                }
            }
        }
    }

    printf("\nAverage Turnaround Time: %.2f\n", (float)current_time / n);
}

int main() {
    int n;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].process_id = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }

    round_robin(processes, n);

    return 0;
}
