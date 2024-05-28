//
// Created by Anastassiya Zabudkina on 27.05.24.
//

#include <unistd.h>
#include <tclDecls.h>
#include "scheduler.h"
#include "scheduler_fcfs.h"
#include "doubly_linked_list.h"

/**
 * \brief Enqueues a process in READY state
 *
 * \param rq  The scheduler's run queue
 * \param pid The process to be enqueued
 */
void stud_FCFS_start(struct run_queue* rq, int pid) {
    struct task* new_task = (struct task*)malloc(sizeof(struct task));
    if (new_task == NULL) {
        // Handle memory allocation failure
        return;
    }

    // Initialize the new task
    new_task->pid = pid;
    new_task->state = READY;
    new_task->prev = NULL;
    new_task->next = NULL;

    // Insert the new task at the end of the run queue
    if (rq->head == NULL) {
        // If the run queue is empty, the new task becomes the head
        rq->head = new_task;
    } else {
        // Traverse to the end of the run queue
        struct task* current = rq->head;
        while (current->next != NULL) {
            current = current->next;
        }
        // Add the new task at the end of the queue
        current->next = new_task;
        new_task->prev = current;
    }

    // Increment the task count
    rq->n_tasks++;
}

/**
 * \brief Elects and starts a process from the run queue. The running process MUST be placed
 *        at the head of `rq` if it is not already there.
 *
 * \param rq  The scheduler's run queue
 */
void stud_FCFS_elect(struct run_queue* rq) {
    // Check if the run queue is empty
    if (rq->head == NULL) {
        return;
    }

    // Select the first task in the queue
    struct task* selected_task = rq->head;

    // Change the state of the selected task to RUNNING
    selected_task->state = RUNNING;

    // Ensure the selected task is at the head of the queue (this should already be the case in FCFS)
    rq->head = selected_task;
}

/**
 * \brief Terminates the current running process (i.e. rq->head) and places it at the BACK
 *        of the run_queue.
 *
 * \param rq  The scheduler's run queue
 */
void stud_FCFS_terminate(struct run_queue* rq) {
    // Check if the run queue is empty
    if (rq->head == NULL) {
        return;
    }

    // Identify the running task (which is at the head of the queue)
    struct task* running_task = rq->head;

    // Change the state of the running task to TERMINATED
    running_task->state = TERMINATED;

    // If the running task is the only task in the queue, no need to move it
    if (running_task->next == NULL) {
        return;
    }

    // Move the task from the head to the back of the run queue
    rq->head = running_task->next;
    rq->head->prev = NULL;

    // Find the last task in the queue
    struct task* current = rq->head;
    while (current->next != NULL) {
        current = current->next;
    }

    // Add the terminated task at the end of the queue
    current->next = running_task;
    running_task->prev = current;
    running_task->next = NULL;
}

/**
 * \brief Performs a clock tick as specified by FCFS.
 *
 * \param rq  The scheduler's run queue
 */
void stud_FCFS_clock_tick(struct run_queue* rq) {
    if (rq->head == NULL) {
        return;
    }

}

/**
 * \brief Sets the state of the running process to BLOCKED, moves it to the BACK of the
 *        run_queue, and elects and runs a new process.
 *
 * \param rq  The scheduler's run queue
 */
void stud_FCFS_wait(struct run_queue* rq) {
    // Check if the run queue is empty
    if (rq->head == NULL) {
        return;
    }

    // Identify the running task (which is at the head of the queue)
    struct task* running_task = rq->head;

    // Set the state of the running task to BLOCKED
    running_task->state = BLOCKED;

    // Move the blocked task to the back of the run queue
    if (running_task->next != NULL) {
        // Update the head to the next task
        rq->head = running_task->next;
        rq->head->prev = NULL;

        // Find the last task in the queue
        struct task* current = rq->head;
        while (current->next != NULL) {
            current = current->next;
        }

        // Add the blocked task at the end of the queue
        current->next = running_task;
        running_task->prev = current;
        running_task->next = NULL;
    }
    // If the running task is the only task in the queue, it remains the only task, but its state is now BLOCKED

    // Elect and run a new process (the new head of the queue)
    if (rq->head != NULL) {
        rq->head->state = RUNNING;
    }
}

/**
 * \brief Sets the state of `pid` to READY, if it exists, and moves it to the BACK
 *        of the run_queue
 *
 * \param rq  The scheduler's run queue
 * \param pid The process to be woken up
 */
void stud_FCFS_wake_up(struct run_queue* rq, int pid) {
    if (rq->head == NULL) {
        return;
    }

    // Find the task with the given pid
    struct task* current = rq->head;
    while (current != NULL) {
        if (current->pid == pid) {
            break;
        }
        current = current->next;
    }

    // If the task with the given pid is not found, return
    if (current == NULL) {
        return;
    }

    // Set the state of the found task to READY
    current->state = READY;

    // If the task is already at the back of the queue, no need to move it
    if (current->next == NULL) {
        return;
    }

    // Move the task to the back of the run queue
    // If the task is the head of the queue
    if (current == rq->head) {
        rq->head = current->next;
        rq->head->prev = NULL;
    } else {
        // If the task is in the middle of the queue
        if (current->prev != NULL) {
            current->prev->next = current->next;
        }
        if (current->next != NULL) {
            current->next->prev = current->prev;
        }
    }

    // Find the last task in the queue
    struct task* last = rq->head;
    while (last->next != NULL) {
        last = last->next;
    }

    // Add the task at the end of the queue
    last->next = current;
    current->prev = last;
    current->next = NULL;
}

/**
 * \brief Event handler for FCFS
 *
 * \param rq    The scheduler's run queue
 * \param event The event to be handled
 * \param pid   Depending on `event`, the `pid` of the target process.
 *              If the `event` doesn't need this, it is ignored.
 */
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
        case wait_event: {  // Corrected the event name to `wait`
            stud_FCFS_wait(rq);
            break;
        }
        case wake_up: {
            stud_FCFS_wake_up(rq, pid);
            break;
        }
        default: {
            // Handle unknown events or do nothing
            break;
        }
    }
}
