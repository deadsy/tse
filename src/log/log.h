//-----------------------------------------------------------------------------
/*
 * https://github.com/rxi/log.c
 * Copyright (c) 2020 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `log.c` for details.
 *
 */
//-----------------------------------------------------------------------------

#ifndef LOG_H
#define LOG_H

//-----------------------------------------------------------------------------

#include <inttypes.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

//-----------------------------------------------------------------------------

typedef struct {
	va_list ap;
	const char *fmt;
	const char *file;
	int64_t time;		// usecs
	void *udata;
	unsigned int thread;
	int line;
	int level;
} log_Event;

typedef void (*log_LogFn)(log_Event * ev);
typedef void (*log_LockFn)(bool lock, void *udata);

int log_init(int level, bool color);
void log_set_lock(log_LockFn fn, void *udata);
void log_set_level(int level);
void log_set_color(bool enable);
int log_add_callback(log_LogFn fn, void *udata, int level);
int log_add_fp(FILE * fp, int level);

void log_log(int level, const char *file, int line, const char *fmt, ...);

//-----------------------------------------------------------------------------
// os functions

int64_t os_get_time_usec(void);
unsigned int os_get_thread_num(void);

//-----------------------------------------------------------------------------

#endif				// LOG_H

//-----------------------------------------------------------------------------
