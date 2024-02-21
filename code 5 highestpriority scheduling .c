#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESS 10

typedef struct {
    int id;
    int priority;
} Process;

typedef struct {
    Process heap[MAX_PROCESS];
    int size;
} PriorityQueue;

void swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

void initialize(PriorityQueue *pq) {
    pq->size = 0;
}

void enqueue(PriorityQueue *pq, int id, int priority) {
    if (pq->size == MAX_PROCESS) {
        printf("Queue is full\n");
        return;
    }

    Process newProcess = {id, priority};
    pq->heap[pq->size] = newProcess;
    int current = pq->size;

    while (current > 0 && pq->heap[current].priority > pq->heap[(current - 1) / 2].priority) {
        swap(&pq->heap[current], &pq->heap[(current - 1) / 2]);
        current = (current - 1) / 2;
    }

    pq->size++;
}

Process dequeue(PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("Queue is empty\n");
        exit(1);
    }

    Process root = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;

    int current = 0;
    while (1) {
        int left = 2 * current + 1;
        int right = 2 * current + 2;
        int largest = current;

        if (left < pq->size && pq->heap[left].priority > pq->heap[largest].priority) {
            largest = left;
        }

        if (right < pq->size && pq->heap[right].priority > pq->heap[largest].priority) {
            largest = right;
        }

        if (largest != current) {
            swap(&pq->heap[current], &pq->heap[largest]);
            current = largest;
        } else {
            break;
        }
    }

    return root;
}

int main() {
    PriorityQueue pq;
    initialize(&pq);

    // Enqueue some processes with their priorities
    enqueue(&pq, 1, 5);
    enqueue(&pq, 2, 2);
    enqueue(&pq, 3, 7);
    enqueue(&pq, 4, 1);
    enqueue(&pq, 5, 9);

    // Dequeue and print processes in order of priority
    printf("Processes in order of priority:\n");
    while (pq.size > 0) {
        Process p = dequeue(&pq);
        printf("Process ID: %d, Priority: %d\n", p.id, p.priority);
    }

    return 0;
}
