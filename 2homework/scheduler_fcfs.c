#include "scheduler.h"
#include "scheduler_fcfs.h"
#include "doubly_linked_list.h"

void stud_FCFS_start(struct run_queue* rq, int pid) {
    struct task* existing_task = stud_rq_find(rq, pid);
    if (existing_task != NULL) {
        return; // Task with the same PID already exists
    }

    struct task* new_task = stud_task_create(pid, READY);
    if (new_task == NULL) {
        return;
    }

    stud_rq_enqueue(rq, new_task);
}

void stud_FCFS_elect(struct run_queue* rq) {
    if (stud_rq_empty(rq)) {
        return;
    }

    struct task* current_task = rq->head;

    // Ensure the task is not blocked
    while (current_task != NULL && current_task->state == BLOCKED) {
        current_task = current_task->next;
    }

    if (current_task != NULL) {
        current_task->state = RUNNING;
        rq->head = current_task;
    }
}

void stud_FCFS_terminate(struct run_queue* rq) {
    if (stud_rq_empty(rq)) {
        return;
    }

    struct task* running_task = rq->head;

    if (running_task == NULL || running_task->state != RUNNING) {
        return;
    }

    running_task->state = TERMINATED;
    rq->head = running_task->next;

    if (rq->head != NULL) {
        rq->head->prev = NULL;
    }

    // Move the terminated task to the end of the queue
    running_task->next = NULL;
    struct task* tail = stud_rq_tail(rq);
    if (tail != NULL) {
        tail->next = running_task;
        running_task->prev = tail;
    } else {
        rq->head = running_task;
    }
}


void stud_FCFS_clock_tick(struct run_queue* rq) {
    // FCFS is non-preemptive, so typically no action is required on each clock tick.
}

void stud_FCFS_wait(struct run_queue* rq) {
    if (stud_rq_empty(rq)) {
        return;
    }

    struct task* running_task = rq->head;
    running_task->state = BLOCKED;
    rq->head = running_task->next;
    if (rq->head != NULL) {
        rq->head->prev = NULL;
    }

    stud_rq_enqueue(rq, running_task);

    struct task* current_task = rq->head;
    while (current_task != NULL && current_task->state == BLOCKED) {
        current_task = current_task->next;
    }

    if (current_task != NULL) {
        current_task->state = RUNNING;
        rq->head = current_task;
    }
}


void stud_FCFS_wake_up(struct run_queue* rq, int pid) {
    if (stud_rq_empty(rq)) {
        return;
    }

    struct task* current = stud_rq_find(rq, pid);
    if (current == NULL) {
        return;
    }

    current->state = READY;

    if (current->next == NULL) {
        return;
    }

    if (current == rq->head) {
        rq->head = current->next;
        rq->head->prev = NULL;
    } else {
        if (current->prev != NULL) {
            current->prev->next = current->next;
        }
        if (current->next != NULL) {
            current->next->prev = current->prev;
        }
    }

    struct task* last = stud_rq_tail(rq);
    last->next = current;
    current->prev = last;
    current->next = NULL;
}

void stud_FCFS(struct run_queue* rq, enum events event, int pid) {
    switch(event) {
        case start: {
            stud_FCFS_start(rq, pid);
            break;
        }
        case terminate: {
            stud_FCFS_terminate(rq);
            break;
        }
        case clock_tick: {
            stud_FCFS_clock_tick(rq);
            break;
        }
        case wait: {
            stud_FCFS_wait(rq);
            break;
        }
        case wake_up: {
            stud_FCFS_wake_up(rq, pid);
            break;
        }
    }
}
