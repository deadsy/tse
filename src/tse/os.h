//-----------------------------------------------------------------------------
/*

API to OS Provided Functions

*/
//-----------------------------------------------------------------------------

#ifndef TSE_OS_H
#define TSE_OS_H

#ifndef TSE_TSE_H
#warning "please include this file using tse.h"
#endif

//-----------------------------------------------------------------------------
// logging

#ifdef TSE_LOG_ENABLE

enum {
	TSE_LOG_TRACE,
	TSE_LOG_DEBUG,
	TSE_LOG_INFO,
	TSE_LOG_WARN,
	TSE_LOG_ERROR,
	TSE_LOG_FATAL,
};

#define log_trace(...) log_log(TSE_LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...) log_log(TSE_LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...)  log_log(TSE_LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...)  log_log(TSE_LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...) log_log(TSE_LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal(...) log_log(TSE_LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

void log_log(int level, const char *file, int line, const char *fmt, ...);

#else				// disable logging

#define log_trace(...) do{}while(0)
#define log_debug(...) do{}while(0)
#define log_info(...)  do{}while(0)
#define log_warn(...)  do{}while(0)
#define log_error(...) do{}while(0)
#define log_fatal(...) do{}while(0)

#endif

//-----------------------------------------------------------------------------
// time

// return the absolute time in microseconds
int64_t os_get_time_usec(void);

//-----------------------------------------------------------------------------

#endif				// TSE_LOG_H

//-----------------------------------------------------------------------------
