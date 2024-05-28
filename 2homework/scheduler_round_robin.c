//
// Created by Anastassiya Zabudkina on 27.05.24.
//

#include "scheduler.h"
#include "scheduler_round_robin.h"
#include "doubly_linked_list.h"

void stud_RR_start(struct run_queue* rq, int pid) {
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

void stud_RR_elect(struct run_queue* rq) {
    if (stud_rq_empty(rq)) {
        return;
    }

    struct task* selected_task = rq->head;
    selected_task->state = RUNNING;
    rq->head = selected_task;
    rq->time_counter = QUANTUM;
}



void stud_RR_terminate(struct run_queue* rq) {
    if (rq == NULL || rq->head == NULL) {
        return;
    }

    struct task *active = rq->head;
    if (active->state != RUNNING) {
        return;
    }

    active->state = TERMINATED;
    rq->head = active->next;
    if (rq->head != NULL) {
        rq->head->prev = NULL;
    }
    stud_rq_enqueue(rq, active);

    if (rq->head != NULL) {
        rq->head->state = RUNNING;
        rq->time_counter = QUANTUM;
    }
}

void stud_RR_clock_tick(struct run_queue* rq) {
    if (stud_rq_empty(rq)) {
        return;
    }

    if (rq->head != NULL && rq->time_counter > 0) {
        rq->time_counter--;
        if (rq->time_counter == 0) {
            struct task* running_task = rq->head;
            running_task->state = READY;
            rq->head = running_task->next;
            if (rq->head != NULL) {
                rq->head->prev = NULL;
            }
            stud_rq_enqueue(rq, running_task);

            struct task* next_task = rq->head;
            while (next_task != NULL && next_task->state != READY) {
                next_task = next_task->next;
            }

            if (next_task != NULL) {
                next_task->state = RUNNING;
                rq->time_counter = QUANTUM;
            }
        }
    }
}


void stud_RR_wait(struct run_queue* rq) {
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
    if (rq->head != NULL) {
        rq->head->state = RUNNING;
        rq->time_counter = QUANTUM;
    }
}

void stud_RR_wake_up(struct run_queue* rq, int pid) {
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

void stud_RR(struct run_queue* rq, enum events event, int pid) {
    switch(event) {
        case start: {
            stud_RR_start(rq, pid);
            break;
        }
        case terminate: {
            stud_RR_terminate(rq);
            break;
        }
        case clock_tick: {
            stud_RR_clock_tick(rq);
            break;
        }
        case wait: {
            stud_RR_wait(rq);
            break;
        }
        case wake_up: {
            stud_RR_wake_up(rq, pid);
            break;
        }
    }
}