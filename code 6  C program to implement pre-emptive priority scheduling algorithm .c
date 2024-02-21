#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
} Process;

typedef struct {
    Process* array[MAX_PROCESSES];
    int size;
} PriorityQueue;

void initializePriorityQueue(PriorityQueue* pq) {
    pq->size = 0;
}

void enqueue(PriorityQueue* pq, Process* process) {
    int i = pq->size;
    while (i > 0 && pq->array[(i - 1) / 2]->priority > process->priority) {
        pq->array[i] = pq->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    pq->array[i] = process;
    pq->size++;
}

Process* dequeue(PriorityQueue* pq) {
    if (pq->size == 0)
        return NULL;

    Process* min_process = pq->array[0];
    pq->size--;
    Process* last_process = pq->array[pq->size];
    int i = 0;
    int child = 1;

    while (child < pq->size) {
        if (child + 1 < pq->size && pq->array[child + 1]->priority < pq->array[child]->priority)
            child++;
        if (last_process->priority <= pq->array[child]->priority)
            break;
        pq->array[i] = pq->array[child];
        i = child;
        child = 2 * i + 1;
    }
    pq->array[i] = last_process;
    return min_process;
}

void preemptivePriorityScheduling(Process* processes[], int num_processes) {
    PriorityQueue ready_queue;
    initializePriorityQueue(&ready_queue);

    int current_time = 0;
    int completed_processes = 0;
    int i = 0;

    while (completed_processes < num_processes) {
        while (i < num_processes && processes[i]->arrival_time <= current_time) {
            enqueue(&ready_queue, processes[i]);
            i++;
        }

        if (ready_queue.size == 0) {
            printf("Idle at time %d\n", current_time);
            current_time++;
            continue;
        }

        Process* current_process = dequeue(&ready_queue);
        printf("Executing process %d at time %d\n", current_process->process_id, current_time);

        current_process->remaining_time--;

        if (current_process->remaining_time == 0) {
            completed_processes++;
            printf("Process %d completed at time %d\n", current_process->process_id, current_time);
        } else {
            enqueue(&ready_queue, current_process);
        }

        current_time++;
    }
}

int main() {
    Process* processes[MAX_PROCESSES];
    int num_processes;

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    for (int i = 0; i < num_processes; i++) {
        processes[i] = (Process*)malloc(sizeof(Process));
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i]->arrival_time, &processes[i]->burst_time, &processes[i]->priority);
        processes[i]->process_id = i + 1;
        processes[i]->remaining_time = processes[i]->burst_time;
    }

    preemptivePriorityScheduling(processes, num_processes);

    for (int i = 0; i < num_processes; i++)
        free(processes[i]);

    return 0;
}
