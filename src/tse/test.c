//-----------------------------------------------------------------------------
/*

Functions to test the speed/accuracy of lookup table functions.

*/
//-----------------------------------------------------------------------------

#define TSE_LOG_ENABLE

#include "tse.h"

//-----------------------------------------------------------------------------
// Error Analysis
// Compare a "fast" function against the known-accurate "slow" function
// Log the error stats to see how good the fast function is.

void rms_error(const char *name, float x0, float x1, float dx, float (*f0)(float), float (*f1)(float)) {
	float x = x0;
	float max_err = FLT_MIN;
	float min_err = FLT_MAX;
	float sum_err2 = 0.f;
	int n = 0;
	while (x < x1) {
		float y0 = f0(x);
		float y1 = f1(x);
		float err = fabsf(y1 - y0);
		//log_debug("x %f y0 %f y1 %f err %f", x, y0, y1, err);
		sum_err2 += err * err;
		if (err < min_err) {
			min_err = err;
		}
		if (err > max_err) {
			max_err = err;
		}
		x += dx;
		n++;
	}
	float rms_err = sqrtf(sum_err2 / (float)n);
	log_info("%s: min %f max %f rms %f", name, min_err, max_err, rms_err);
}

//-----------------------------------------------------------------------------
// function benchmarks

// benchmark int16_t func(uint32_t x)
void benchmark_f0(const char *name, int16_t(*f0) (uint32_t), unsigned int n) {
	uint32_t x = 0;
	unsigned int i = 0;
	int64_t start = os_get_time_usec();
	while (i < n) {
		f0(x);
		x += 17;
		i++;
	}
	int64_t usecs = os_get_time_usec() - start;
	float usecs_per = (float)usecs / (float)n;
	log_info("%s: %d calls, %" PRId64 " usecs (%f usecs/call)", name, n, usecs, usecs_per);
}

// benchmark float func(float x)
void benchmark_f1(const char *name, float (*f1)(float), unsigned int n) {
	float x = 0.f;
	unsigned int i = 0;
	int64_t start = os_get_time_usec();
	while (i < n) {
		f1(x);
		x += 0.05f;
		i++;
	}
	int64_t usecs = os_get_time_usec() - start;
	float usecs_per = (float)usecs / (float)n;
	log_info("%s: %d calls, %" PRId64 " usecs (%f usecs/call)", name, n, usecs, usecs_per);
}

// benchmark uint32_t func(q24  x)
void benchmark_f2(const char *name, uint32_t(*f2) (q24), unsigned int n) {
	q24 x = 0;
	unsigned int i = 0;
	int64_t start = os_get_time_usec();
	while (i < n) {
		f2(x);
		x += (1U << 23);	// 0.5
		i++;
	}
	int64_t usecs = os_get_time_usec() - start;
	float usecs_per = (float)usecs / (float)n;
	log_info("%s: %d calls, %" PRId64 " usecs (%f usecs/call)", name, n, usecs, usecs_per);
}

//-----------------------------------------------------------------------------
