#ifndef _SL_LOG_H_
#define _SL_LOG_H_

#include <stdio.h>

typedef struct sl_logger
{
    const char *title;
    FILE *output; 
    int level;
} sl_logger;

#define SL_DEF_LOGGER(logger, title_, ...) \
    sl_logger logger = { .level = SL_LOG_LVL_GLOBAL, .output = NULL, ##__VA_ARGS__, .title = title_ }; \
    static sl_logger  *__SL_LOCAL_LOGGER__ = &logger

#define SL_loggerUse(logger) (__SL_LOCAL_LOGGER__ = &logger)

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

#define SL_loggerLog(logger, log_level, color, title_, msg, ...) ((logger)->level >= (log_level) && (logger)->level >= SL_LOG_LVL_GLOBAL ? fprintf((logger)->output ? (logger)->output : stderr, "\033["#color"m%s:%u@%s - [%s "title_"] "msg"\033[0m\n", __FILE__, __LINE__, __func__, (logger)->title, ##__VA_ARGS__) : (0))
#define SL_loggerLvl(name, log_level)     ((logger)->level  = (log_level))
#define SL_loggerOut(name, output_stream) ((logger)->stream = (output_stream))

#define SL_todo(msg, ...) (SL_loggerLog(__SL_LOCAL_LOGGER__, SL_LOG_LVL_ALL,     32, "TODO",    msg, ##__VA_ARGS__), exit(1))
#define SL_logI(msg, ...)  SL_loggerLog(__SL_LOCAL_LOGGER__, SL_LOG_LVL_INFO,    37, "INFO",    msg, ##__VA_ARGS__)
#define SL_logW(msg, ...)  SL_loggerLog(__SL_LOCAL_LOGGER__, SL_LOG_LVL_WARNING, 33, "WARNING", msg, ##__VA_ARGS__)
#define SL_logE(msg, ...)  SL_loggerLog(__SL_LOCAL_LOGGER__, SL_LOG_LVL_ERROR,   31, "ERROR",   msg, ##__VA_ARGS__)



#ifdef SL_STRIP_PREFIX
#   define  DEF_LOGGER      SL_DEF_LOGGER
#   define  loggerUse       SL_loggerUse
    typedef SL_log_lvl      log_lvl;
#   define  LOG_LVL_GLOBAL  SL_LOG_LVL_GLOBAL
#   define  loggerLog       SL_loggerLog
#   define  loggerLvl       SL_loggerLvl
#   define  loggerOut       SL_loggerOut
#   define  todo            SL_todo
#   define  logI            SL_logI
#   define  logW            SL_logW
#   define  logE            SL_logE
#endif

#endif // _SL_LOG_H_