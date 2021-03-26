//-----------------------------------------------------------------------------
/*
 * https://github.com/rxi/log.c
 * Copyright (c) 2020 rxi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * https://github.com/deadsy/picox
 * Modified by Jason T. Harris for RPi Pico. Copyright (c) 2021
 *
 */
//-----------------------------------------------------------------------------

#include <string.h>
#include "log.h"

//-----------------------------------------------------------------------------

// timestamp returns a string with seconds since boot (millisecond resolution).
static void timestamp(char *s, size_t n, int64_t us) {
	uint32_t ms = us / 1000;
	int secs = ms / 1000;
	int msecs = ms - (secs * 1000);
	snprintf(s, n, "%d.%03d", secs, msecs);
}

//-----------------------------------------------------------------------------

typedef struct {
	log_LogFn fn;
	void *udata;
	int level;
} Callback;

#define MAX_CALLBACKS 4

static struct {
	void *udata;
	log_LockFn lock;
	int level;
	bool color;
	Callback callbacks[MAX_CALLBACKS];
} L;

//-----------------------------------------------------------------------------

static const char *level_strings[] = {
	"TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL",
};

static const char *level_colors[] = {
	"\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m",
};

//-----------------------------------------------------------------------------

// file_callback logs to the stdout interface
static void stdout_callback(log_Event * ev) {
	char buf[16];
	timestamp(buf, sizeof(buf), ev->time);
	if (L.color) {
		fprintf(ev->udata, "%d: %s %s%s\x1b[0m \x1b[90m%s(%d)\x1b[0m ", ev->thread, buf, level_colors[ev->level], level_strings[ev->level], ev->file, ev->line);
	} else {
		fprintf(ev->udata, "%d: %s %s %s(%d) ", ev->thread, buf, level_strings[ev->level], ev->file, ev->line);
	}
	vfprintf(ev->udata, ev->fmt, ev->ap);
	fprintf(ev->udata, "\n");
	fflush(ev->udata);
}

//-----------------------------------------------------------------------------

// file_callback logs to a file interface
static void file_callback(log_Event * ev) {
	char buf[16];
	timestamp(buf, sizeof(buf), ev->time);
	fprintf(ev->udata, "%d: %s %s %s(%d) ", ev->thread, buf, level_strings[ev->level], ev->file, ev->line);
	vfprintf(ev->udata, ev->fmt, ev->ap);
	fprintf(ev->udata, "\n");
//      fflush(ev->udata);
}

// log_add_fp adds a file as logging output
int log_add_fp(FILE * fp, int level) {
	return log_add_callback(file_callback, fp, level);
}

//-----------------------------------------------------------------------------
// locking

static void lock(void) {
	if (L.lock) {
		L.lock(true, L.udata);
	}
}

static void unlock(void) {
	if (L.lock) {
		L.lock(false, L.udata);
	}
}

// log_set_lock sets a locking function for exclusive logging access
void log_set_lock(log_LockFn fn, void *udata) {
	L.lock = fn;
	L.udata = udata;
}

//-----------------------------------------------------------------------------

// log_set_color enables color coding for stdout log messages
void log_set_color(bool enable) {
	L.color = enable;
}

// log_set_level sets the logging level
void log_set_level(int level) {
	L.level = level;
}

// log_add_callback adds a callback to another logging output
int log_add_callback(log_LogFn fn, void *udata, int level) {
	for (int i = 0; i < MAX_CALLBACKS; i++) {
		if (!L.callbacks[i].fn) {
			L.callbacks[i] = (Callback) {
			fn, udata, level};
			return 0;
		}
	}
	return -1;
}

//-----------------------------------------------------------------------------

// log_log generates a log message
void log_log(int level, const char *file, int line, const char *fmt, ...) {
	log_Event ev = {
		.fmt = fmt,
		.file = file,
		.line = line,
		.level = level,
		.thread = os_get_thread_num(),
		.time = os_get_time_usec(),
	};

	lock();

	for (int i = 0; i < MAX_CALLBACKS && L.callbacks[i].fn; i++) {
		Callback *cb = &L.callbacks[i];
		if (level >= cb->level) {
			ev.udata = cb->udata;
			va_start(ev.ap, fmt);
			cb->fn(&ev);
			va_end(ev.ap);
		}
	}

	unlock();
}

//-----------------------------------------------------------------------------

// log_init initializes the logging
int log_init(int level, bool color) {
	memset(&L, 0, sizeof(L));
	log_set_level(level);
	log_set_color(color);
	return log_add_callback(stdout_callback, stdout, 0);
}

//-----------------------------------------------------------------------------
