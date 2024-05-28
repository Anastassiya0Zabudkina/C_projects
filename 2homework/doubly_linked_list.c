//
// Created by Anastassiya Zabudkina on 27.05.24.
//

#include "doubly_linked_list.h"
#include <stdbool.h>
#include <MacTypes.h>
#include "scheduler.h"
#include "doubly_linked_list.h"

/**
 * \brief Checks whether a run_queue is empty
 *
 * \param rq Pointer to the run_queue
 *
 * \returns `true` iff the run_queue is empty
 */
bool stud_rq_empty(struct run_queue const *rq) {
    return false;
}

/**
 * \brief Creates a task
 *
 * \param pid   The pid of the new task
 * \param state Default state of the task
 *
 * \return A pointer to the new task, `NULL` if failed
 */

struct task *stud_task_create(int pid, enum states state) {
    return NULL;
}

/**
 * \brief Frees/destroys a task This function assumes the task has already been
 *        removed from any run queue. It does not handle linked list operations
 *        or modifications to the run queue.
 *
 * \param task Pointer to the task to-be-destroyed
 */
void stud_task_free(struct task *task) {
    return;
}

/**
 * \brief Frees all the elements of the `run_queue` and empties it.
 *        `rq` itself should NOT be freed. After calling this function,
 *        `rq` must simply be an empty `run_queue`.
 *
 * \param rq Pointer to the run_queue to-be-destroyed
 */
void stud_rq_destroy(struct run_queue *rq) {
    return;
}

/**
 * \brief Tries to find a task in a run_queue by its PID
 *
 * \param rq  Pointer to the run_queue
 * \param pid PID of the wanted task
 *
 * \returns Pointer to the task, `NULL` if failed
 */
struct task *stud_rq_find(struct run_queue *rq, int pid) {
    return NULL;
}
