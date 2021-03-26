//-----------------------------------------------------------------------------
/*

OS Functions

*/
//-----------------------------------------------------------------------------

#include <time.h>

#include "log.h"
#include "tse.h"

//-----------------------------------------------------------------------------

int64_t os_get_time_usec(void) {
	struct timespec tp;
	int rc = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp);
	if (rc != 0) {
		return 0;
	}
	return (1000000LL * (int64_t) tp.tv_sec) + ((int64_t) tp.tv_nsec / 1000LL);
}

unsigned int os_get_thread_num(void) {
	return 0;
}

//-----------------------------------------------------------------------------
