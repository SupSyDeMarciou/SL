#ifndef _SL_LOG_H_
#define _SL_LOG_H_

#include <stdio.h>

#define SL_DEF_LOGGER(name, title_, lvl) \
    struct __LOGGER_##name##_t__ { const char *title; FILE *stream; int level; } __LOGGER_##name##__ = { .level = lvl, .title = title_, .stream = NULL }; \
    static struct __LOGGER_##name##_t__  *__LOGGER__ = &__LOGGER_##name##__

typedef enum SL_log_lvl {
    SL_LOG_LVL_OFF     = -100,
    SL_LOG_LVL_INFO    =  0,
    SL_LOG_LVL_WARNING =  1,
    SL_LOG_LVL_ERROR   =  2,
    SL_LOG_LVL_ALL     =  100,
} SL_log_lvl;

#ifndef SL_LOG_LVL_GLOBAL
#   define SL_LOG_LVL_GLOBAL SL_LOG_LVL_ALL
#endif

#define SL_logger_log(logger, log_level, color, title_, msg, ...) (logger->level >= (log_level) && logger->level >= SL_LOG_LVL_GLOBAL ? fprintf(logger->stream ? logger->stream : stderr, "\033["#color"m%s:%u@%s - [%s "title_"] "msg"\033[0m\n", __FILE__, __LINE__, __FUNCTION__, logger->title, ##__VA_ARGS__) : (0))
#define SL_logger_lvl(name, log_level)     (__LOGGER_##name##__.level = (log_level))
#define SL_logger_out(name, output_stream) (__LOGGER_##name##__.stream = (output_stream))

#define SL_todo(msg, ...) (SL_logger_log(__LOGGER__, SL_LOG_LVL_ALL,     32, "TODO",    msg, ##__VA_ARGS__), exit(1))
#define SL_logI(msg, ...)  SL_logger_log(__LOGGER__, SL_LOG_LVL_INFO,    37, "INFO",    msg, ##__VA_ARGS__)
#define SL_logW(msg, ...)  SL_logger_log(__LOGGER__, SL_LOG_LVL_WARNING, 33, "WARNING", msg, ##__VA_ARGS__)
#define SL_logE(msg, ...)  SL_logger_log(__LOGGER__, SL_LOG_LVL_ERROR,   31, "ERROR",   msg, ##__VA_ARGS__)



#ifdef SL_STRIP_PREFIX
#   define DEF_LOGGER     SL_DEF_LOGGER
    typedef SL_log_lvl    log_lvl;
#   define LOG_LVL_GLOBAL SL_LOG_LVL_GLOBAL
#   define logger_log     SL_logger_log
#   define logger_lvl     SL_logger_lvl
#   define logger_out     SL_logger_out
#   define todo           SL_todo
#   define logI           SL_logI
#   define logW           SL_logW
#   define logE           SL_logE
#endif

#endif // _SL_LOG_H_