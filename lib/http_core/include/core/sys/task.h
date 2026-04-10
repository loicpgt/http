#ifndef HTTP_TASK_H
#define HTTP_TASK_H
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct task {
    uint8_t id;
    uint8_t used;
} task_t;

typedef struct task_pool {
    uint8_t pool_size;
    size_t task_size;
    task_t* memory_region;
} task_pool_t;

void task_pool_init(task_pool_t* pool, uint8_t pool_size, size_t task_size);
void task_pool_destroy(task_pool_t* pool);

task_t* task_acquire(task_pool_t* pool);
void task_release(task_t* task);

#ifdef __cplusplus
}
#endif

#endif //HTTP_TASK_H