#include <stdlib.h>
#include <stdint.h>

#include "kernel.h"
#include "task.h"

void task_pool_init(task_pool_t* pool, uint8_t pool_size, size_t task_size) {
    pool->pool_size = pool_size;
    pool->task_size = task_size;
    pool->memory_region = calloc(pool_size, task_size);

    if (pool->memory_region == nullptr) {
        PANIC("Failed to initialize a task_pool.\n\nTask size: %zu bytes\n", task_size);
    }

    uint8_t cursor = 0;
    while (cursor < pool_size) {
        task_t* task = &pool->memory_region[
            cursor == 0 ? 0 :
            cursor * task_size + 1];

        task->id = cursor;
        task->used = 0;

        cursor++;
    }
}

void task_pool_destroy(task_pool_t* pool) {
    free(pool->memory_region);
}

task_t* task_acquire(task_pool_t* pool) {
    uint8_t cursor = 0;

    while (cursor < pool->pool_size) {
        task_t* task = &pool->memory_region[cursor];
        if (!task->used) {
            task->used = 1;
            return task;
        }

        cursor++;
    }

    return nullptr;
}

void task_release(task_t* task) {
    task->used = 0;
}

