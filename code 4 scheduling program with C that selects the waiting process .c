#include <stdio.h>

#define MAX_PROCESSES 10

// Process structure
typedef struct {
    int pid; // Process ID
    int arrival_time; // Arrival time
    int burst_time; // Burst time
    int completion_time; // Completion time
    int turnaround_time; // Turnaround time
    int waiting_time; // Waiting time
    int executed; // Flag to mark if the process has been executed
} Process;

// Function prototypes
void sjf(Process processes[], int n);
void display_results(Process processes[], int n);

int main() {
    Process processes[MAX_PROCESSES];
    int n, i;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input the process details
    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].pid = i + 1;
        processes[i].executed = 0;
    }

    // Run the SJF scheduling algorithm
    sjf(processes, n);

    // Display the results
    display_results(processes, n);

    return 0;
}

// Shortest Job First (SJF) scheduling algorithm
void sjf(Process processes[], int n) {
    int current_time = 0;
    int remaining_processes = n;

    while (remaining_processes > 0) {
        int shortest_burst_index = -1;
        int shortest_burst = __INT_MAX__;

        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (!processes[i].executed && processes[i].arrival_time <= current_time && processes[i].burst_time < shortest_burst) {
                shortest_burst = processes[i].burst_time;
                shortest_burst_index = i;
            }
        }

        if (shortest_burst_index == -1) {
            current_time++; // No process to execute, move to the next time unit
        } else {
            // Execute the selected process
            current_time += processes[shortest_burst_index].burst_time;
            processes[shortest_burst_index].completion_time = current_time;
            processes[shortest_burst_index].turnaround_time = processes[shortest_burst_index].completion_time - processes[shortest_burst_index].arrival_time;
            processes[shortest_burst_index].waiting_time = processes[shortest_burst_index].turnaround_time - processes[shortest_burst_index].burst_time;
            processes[shortest_burst_index].executed = 1;
            remaining_processes--;
        }
    }
}

// Display results
void display_results(Process processes[], int n) {
    float avg_turnaround_time = 0, avg_waiting_time = 0;

    printf("\nProcess\t Arrival Time\t Burst Time\t Completion Time\t Turnaround Time\t Waiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t %d\t\t %d\t\t %d\t\t\t %d\t\t\t %d\n", processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time,
               processes[i].waiting_time);

        avg_turnaround_time += processes[i].turnaround_time;
        avg_waiting_time += processes[i].waiting_time;
    }

    avg_turnaround_time /= n;
    avg_waiting_time /= n;

    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
}
