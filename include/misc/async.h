#ifndef _SL_ASYNC_H_
#define _SL_ASYNC_H_

/*
 *  THREAD: Utilities for thread manipulation.
 *  
 *  TODO:
 *  - Try finding better declarative statement
 * 
*/

#include "../base.h"
#include <errno.h>
#include <pthread.h>
#include <time.h>

/// @brief Sleep for nano seconds
/// @param nano_seconds Number of nanoseconds to sleep
/// @return Error code from `nanosleep` if failed
int SL_sleep_n(usize nano_seconds);
/// @brief Sleep for nano seconds
/// @param nano_seconds Number of microseconds to sleep
/// @return Error code from `nanosleep` if failed
int SL_sleep_u(usize micro_seconds);
/// @brief Sleep for nano seconds
/// @param nano_seconds Number of milliseconds to sleep
/// @return Error code from `nanosleep` if failed
int Sl_sleep_m(usize milli_seconds);

#define  __SL_ASYNC_VAR2_1_COM(xpd, var_type, var_name, ...) xpd(var_type, var_name) __VA_OPT__(, xpd(__VA_ARGS__))
#define  __SL_ASYNC_VAR2_2_COM(xpd, var_type, var_name, ...) xpd(var_type, var_name) __VA_OPT__(, __SL_ASYNC_VAR2_1_COM(xpd, __VA_ARGS__))
#define  __SL_ASYNC_VAR2_3_COM(xpd, var_type, var_name, ...) xpd(var_type, var_name) __VA_OPT__(, __SL_ASYNC_VAR2_2_COM(xpd, __VA_ARGS__))
#define  __SL_ASYNC_VAR2_4_COM(xpd, var_type, var_name, ...) xpd(var_type, var_name) __VA_OPT__(, __SL_ASYNC_VAR2_3_COM(xpd, __VA_ARGS__))
#define  __SL_ASYNC_VAR2_5_COM(xpd, var_type, var_name, ...) xpd(var_type, var_name) __VA_OPT__(, __SL_ASYNC_VAR2_4_COM(xpd, __VA_ARGS__))
#define  __SL_ASYNC_VAR2_6_COM(xpd, var_type, var_name, ...) xpd(var_type, var_name) __VA_OPT__(, __SL_ASYNC_VAR2_5_COM(xpd, __VA_ARGS__))
#define  __SL_ASYNC_VAR2_7_COM(xpd, var_type, var_name, ...) xpd(var_type, var_name) __VA_OPT__(, __SL_ASYNC_VAR2_6_COM(xpd, __VA_ARGS__))
#define  __SL_ASYNC_VAR2_8_COM(xpd, var_type, var_name, ...) xpd(var_type, var_name) __VA_OPT__(, __SL_ASYNC_VAR2_7_COM(xpd, __VA_ARGS__))
#define  __SL_ASYNC_VAR2_9_COM(xpd, var_type, var_name, ...) xpd(var_type, var_name) __VA_OPT__(, __SL_ASYNC_VAR2_8_COM(xpd, __VA_ARGS__))
#define __SL_ASYNC_VAR2_10_COM(xpd, var_type, var_name, ...) xpd(var_type, var_name) __VA_OPT__(, __SL_ASYNC_VAR2_9_COM(xpd, __VA_ARGS__))
#define __SL_ASYNC_VAR2_11_COM(xpd, var_type, var_name, ...) xpd(var_type, var_name) __VA_OPT__(, __SL_ASYNC_VAR2_10_COM(xpd, __VA_ARGS__))

#define  __SL_ASYNC_VAR2_1(xpd, sep, var_type, var_name, ...) xpd(var_type, var_name) __VA_OPT__(sep xpd(__VA_ARGS__))
#define  __SL_ASYNC_VAR2_2(xpd, sep, var_type, var_name, ...) xpd(var_type, var_name) __VA_OPT__(sep __SL_ASYNC_VAR2_1(xpd, sep, __VA_ARGS__))
#define  __SL_ASYNC_VAR2_3(xpd, sep, var_type, var_name, ...) xpd(var_type, var_name) __VA_OPT__(sep __SL_ASYNC_VAR2_2(xpd, sep, __VA_ARGS__))
#define  __SL_ASYNC_VAR2_4(xpd, sep, var_type, var_name, ...) xpd(var_type, var_name) __VA_OPT__(sep __SL_ASYNC_VAR2_3(xpd, sep, __VA_ARGS__))
#define  __SL_ASYNC_VAR2_5(xpd, sep, var_type, var_name, ...) xpd(var_type, var_name) __VA_OPT__(sep __SL_ASYNC_VAR2_4(xpd, sep, __VA_ARGS__))
#define  __SL_ASYNC_VAR2_6(xpd, sep, var_type, var_name, ...) xpd(var_type, var_name) __VA_OPT__(sep __SL_ASYNC_VAR2_5(xpd, sep, __VA_ARGS__))
#define  __SL_ASYNC_VAR2_7(xpd, sep, var_type, var_name, ...) xpd(var_type, var_name) __VA_OPT__(sep __SL_ASYNC_VAR2_6(xpd, sep, __VA_ARGS__))
#define  __SL_ASYNC_VAR2_8(xpd, sep, var_type, var_name, ...) xpd(var_type, var_name) __VA_OPT__(sep __SL_ASYNC_VAR2_7(xpd, sep, __VA_ARGS__))
#define  __SL_ASYNC_VAR2_9(xpd, sep, var_type, var_name, ...) xpd(var_type, var_name) __VA_OPT__(sep __SL_ASYNC_VAR2_8(xpd, sep, __VA_ARGS__))
#define __SL_ASYNC_VAR2_10(xpd, sep, var_type, var_name, ...) xpd(var_type, var_name) __VA_OPT__(sep __SL_ASYNC_VAR2_9(xpd, sep, __VA_ARGS__))
#define __SL_ASYNC_VAR2_11(xpd, sep, var_type, var_name, ...) xpd(var_type, var_name) __VA_OPT__(sep __SL_ASYNC_VAR2_10(xpd, sep, __VA_ARGS__))

#define __SL_ASYNC_VAR2_COM(xpd, ...) __VA_OPT__(__SL_ASYNC_VAR2_11_COM(xpd, __VA_ARGS__))
#define __SL_ASYNC_VAR2(xpd, sep, ...) __VA_OPT__(__SL_ASYNC_VAR2_11(xpd, sep, __VA_ARGS__))

#define __SL_ASYNC_ARG_TYPE(var_type, var_name) var_type
#define __SL_ASYNC_ARG_NAME(var_type, var_name) var_name
#define __SL_ASYNC_ARG_DECL(var_type, var_name) var_type var_name
#define __SL_ASYNC_ARG_NULL(var_type, var_name) *(var_type *)NULL
#define __SL_ASYNC_ARG_CALL(var_type, var_name) task->var_name
#define __SL_ASYNC_ARG_MOVE(var_type, var_name) task->var_name = var_name

/// @brief Define the necessary functions and structures to call tasks seamlessly
/// @param func The function to make asynchronous
/// @param arg[i]_t The functions's i-th argument's type
/// @param arg[i]_n The functions's i-th argument's name
/// @return Definition of task type `{func}_task`, creation of functions `{func}_task *{func}_async(args...)` and `{func}_task *{func}_async_full(args..., const pthread_attr_t *attr)`
/// @note To declare a function parameter, you must first put the type of the parameter, a comma, and then the name of the parameter :
/// ``` 
/// int foo(int x, char *y);
/// SL_DEF_ASYNC(foo, int, x, char *, y);
/// ```
/// @warning Due to the internals of how this works, you cannot declare a void return type for an async function. Just use int and ignore the return value instead
/// @note Macros are declared for up to 12 parameters
#define SL_DEF_ASYNC(func, ...)                                                                                                                                                                                                 \
    typedef struct func##_task { sl_task_status status; pthread_t thread; __SL_ASYNC_VAR2(__SL_ASYNC_ARG_DECL, ;, ##__VA_ARGS__); typeof(func(__SL_ASYNC_VAR2_COM(__SL_ASYNC_ARG_NULL, ##__VA_ARGS__))) ret_val; } func##_task; \
    void *__##func##_async_exec(func##_task *task) {                                                                                                                                                                            \
        task->status = SL_TASK_WORKING;                                                                                                                                                                                         \
        task->ret_val = func(__SL_ASYNC_VAR2_COM(__SL_ASYNC_ARG_CALL, ##__VA_ARGS__));                                                                                                                                          \
        task->status = SL_TASK_DONE;                                                                                                                                                                                            \
        pthread_exit(NULL);                                                                                                                                                                                                     \
    }                                                                                                                                                                                                                           \
    const func##_task *func##_async_full(__SL_ASYNC_VAR2_COM(__SL_ASYNC_ARG_DECL, ##__VA_ARGS__) __VA_OPT__(,) const pthread_attr_t *attr) {                                                                                    \
        func##_task *task = malloc(sizeof(func##_task));                                                                                                                                                                        \
        task->status = SL_TASK_WAIT;                                                                                                                                                                                            \
        __SL_ASYNC_VAR2(__SL_ASYNC_ARG_MOVE, ;, ##__VA_ARGS__);                                                                                                                                                                 \
        if (pthread_create(&task->thread, attr, (void *(*)(void *))__##func##_async_exec, task))                                                                                                                                \
            return free((void *)task), __SL_ERROR(SL_ERROR_THREAD_CREATE), NULL;                                                                                                                                                \
        return task;                                                                                                                                                                                                            \
    }                                                                                                                                                                                                                           \
    const func##_task *func##_async(__SL_ASYNC_VAR2_COM(__SL_ASYNC_ARG_DECL, ##__VA_ARGS__)) { return func##_async_full(__SL_ASYNC_VAR2_COM(__SL_ASYNC_ARG_NAME, ##__VA_ARGS__) __VA_OPT__(,) NULL); }

typedef enum sl_task_status
{
    SL_TASK_WAIT,
    SL_TASK_WORKING,
    SL_TASK_DONE
} sl_task_status;

bool __SL_await(const void *task, usize task_thread_offset, usize ret_size, usize task_ret_offset, void *usr_ret);
/// @brief Waits until the task is complete
/// @param task The task to complete
/// @param ... A pointer in which to store the return value of the task
/// @return Wether the task was successfuly completed
/// @note Error status is recorded in SL_ERROR
#define SL_await(task, ...) __SL_await((task), offsetof(typeof(*task), thread), sizeof((task)->ret_val), offsetof(typeof(*task), ret_val), (NULL, ##__VA_ARGS__))



#ifdef SL_STRIP_PREFIX
#   define  sleep_n             SL_sleep_n
#   define  sleep_u             SL_sleep_u
#   define  sleep_m             SL_sleep_m
    typedef sl_task_status      task_status;
#   define  await               SL_await
#   define  DEF_ASYNC           SL_DEF_ASYNC
#endif



#ifdef SL_IMPLEMENTATION
int sleep_n(usize nano_seconds)
{
    struct timespec time = { .tv_sec = nano_seconds / 1000*1000*1000, .tv_nsec = (nano_seconds  % 1000*1000*1000) };
    int err = 0;
    while (nanosleep(&time, &time) < 0 && (err = errno) == EINTR);
    return err;
}
int sleep_u(usize micro_seconds)
{
    struct timespec time = { .tv_sec = micro_seconds / 1000*1000,     .tv_nsec = (micro_seconds % 1000*1000)*1000 };
    int err = 0;
    while (nanosleep(&time, &time) < 0 && (err = errno) == EINTR);
    return err;
}
int sleep_m(usize milli_seconds)
{
    struct timespec time = { .tv_sec = milli_seconds / 1000,          .tv_nsec = (milli_seconds % 1000)*1000*1000 };
    int err = 0;
    while (nanosleep(&time, &time) < 0 && (err = errno) == EINTR);
    return err;
}

bool __SL_await(const void *task, usize task_thread_offset, usize ret_size, usize task_ret_offset, void *usr_ret)
{
    if (!task) __SL_ERROR(SL_ERROR_THREAD_CREATE), false;
    pthread_t thread = *(pthread_t *)(task + task_thread_offset);
    if (pthread_join(thread, NULL))  
        return pthread_cancel(thread), free((void *)task), __SL_ERROR(SL_ERROR_THREAD_JOIN), false;
    if (usr_ret && !memcpy(usr_ret, task + task_ret_offset, ret_size)) 
        return free((void *)task), __SL_ERROR(SL_ERROR_MEMORY), false;
    return free((void *)task), true;
}
#endif
#endif // _SL_ASYNC_H_