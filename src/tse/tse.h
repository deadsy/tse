//-----------------------------------------------------------------------------
/*

Tiny Synth Engine Includes

*/
//-----------------------------------------------------------------------------

#ifndef TSE_TSE_H
#define TSE_TSE_H

//-----------------------------------------------------------------------------

#include <inttypes.h>
#include <math.h>
#include <float.h>

#include "os.h"
#include "qfmt.h"
#include "const.h"

//-----------------------------------------------------------------------------

#define TSE_VERSION "0.1"

//-----------------------------------------------------------------------------
// math

// cosine
q15 cos_q15(uint32_t x);
float cosf_fast(float x);

// pow2
q30 pow2(q31 x);
float pow2_fast(float x);
float pow2_slow(float x);

// clamp values
static inline float clampf(float x, float lo, float hi) {
	if (x < lo) {
		return lo;
	}
	if (x > hi) {
		return hi;
	}
	return x;
}

static inline int clampi(int x, int lo, int hi) {
	if (x < lo) {
		return lo;
	}
	if (x > hi) {
		return hi;
	}
	return x;
}

//-----------------------------------------------------------------------------
// test functions

void rms_error(const char *name, float x0, float x1, float dx, float (*f0)(float), float (*f1)(float));
void benchmark_f0(const char *name, int16_t(*f0) (uint32_t), unsigned int n);
void benchmark_f1(const char *name, float (*f1)(float), unsigned int n);
void benchmark_f2(const char *name, uint32_t(*f2) (q24), unsigned int n);

//-----------------------------------------------------------------------------
// midi

// midi to frequency
uint32_t m2f(q24 note);
float m2f_slow(float note);
float m2f_fast(float note);

// midi to cv conversion
q24 m2cv(q24 note);

//-----------------------------------------------------------------------------

#endif				// TSE_TSE_H

//-----------------------------------------------------------------------------
