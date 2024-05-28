#include <stdbool.h>
#include <stdlib.h>
#include "scheduler.h"
#include "doubly_linked_list.h"

bool stud_rq_empty(struct run_queue const *rq) {
    return (rq->head == NULL);
}

struct task *stud_task_create(int pid, enum states state) {
    struct task* new_task = (struct task*)malloc(sizeof(struct task));
    if (new_task == NULL) {
        return NULL;
    }

    new_task->pid = pid;
    new_task->state = state;
    new_task->prev = NULL;
    new_task->next = NULL;
    return new_task;
}

void stud_task_free(struct task *task) {
    free(task);
}

void stud_rq_destroy(struct run_queue *rq) {
    if (stud_rq_empty(rq) || !rq) {
        return;
    }

    struct task *current = rq->head;
    while (current != NULL) {
        struct task *next = current->next;
        stud_task_free(current);
        current = next;
    }

    rq->head = NULL;
    rq->n_tasks = 0;
    rq->time_counter = 0;
}

struct task *stud_rq_find(struct run_queue *rq, int pid) {
    struct task* current = rq->head;
    while (current != NULL) {
        if (current->pid == pid) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

struct task *stud_rq_head(struct run_queue *rq) {
    return rq->head;
}

struct task *stud_rq_tail(struct run_queue *rq) {
    struct task* current = rq->head;
    if (current == NULL) {
        return NULL;
    }
    while (current->next != NULL) {
        current = current->next;
    }
    return current;
}

bool stud_rq_enqueue(struct run_queue *rq, struct task *task) {
    if (rq->head == NULL) {
        rq->head = task;
    } else {
        struct task* current = rq->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = task;
        task->prev = current;
    }
    rq->n_tasks++;
    return true;
}

bool stud_rq_prepend(struct run_queue *rq, struct task *task) {
    if (rq->head == NULL) {
        rq->head = task;
    } else {
        task->next = rq->head;
        rq->head->prev = task;
        rq->head = task;
    }
    rq->n_tasks++;
    return true;
}

size_t stud_rq_length(struct run_queue *rq) {
    size_t length = 0;
    struct task* current = rq->head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}
