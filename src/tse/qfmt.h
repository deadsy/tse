//-----------------------------------------------------------------------------
/*

Fixed Point Q-Format Code

*/
//-----------------------------------------------------------------------------

#ifndef TSE_QFMT_H
#define TSE_QFMT_H

#ifndef TSE_TSE_H
#warning "please include this file using tse.h"
#endif

//-----------------------------------------------------------------------------

typedef int32_t q31;		// Q1.31
typedef int32_t q30;		// Q2.30
typedef int32_t q24;		// Q8.24
typedef int32_t q17;		// Q15.17
typedef int16_t q15;		// Q1.15

//-----------------------------------------------------------------------------
// Q1.31: -1 .. 0.999

static inline float q31_to_float(q31 x) {
	return (float)x *(1.f / (float)(1UL << 31));
}

static inline q31 float_to_q31(float x) {
	return (q24) (x * (float)(1UL << 31));
}

static inline q15 q31_to_q15(q31 x) {
	return (int16_t) (x >> 16);
}

//-----------------------------------------------------------------------------
// Q2.30: -2 .. 1.999

static inline float q30_to_float(q30 x) {
	return (float)x *(1.f / (float)(1UL << 30));
}

//-----------------------------------------------------------------------------
// Q8.24: -128 .. 127.999

static inline float q24_to_float(q24 x) {
	return (float)x *(1.f / (float)(1UL << 24));
}

static inline q24 float_to_q24(float x) {
	return (q24) (x * (float)(1UL << 24));
}

static inline q24 int_to_q24(int x) {
	return (q24) (x << 24);
}

static inline q24 q24_frac(q24 x) {
	return (q24) (x & ((1U << 24) - 1));
}

static inline int q24_int(q24 x) {
	return (int)(x >> 24);
}

static inline q24 mul_q24(q24 a, q24 b) {
	int64_t x = (int64_t) a * (int64_t) b;
	return (q24) (x >> 24);
}

//-----------------------------------------------------------------------------
// Q15.17: -16384 .. 16383.999

static inline float q17_to_float(q17 x) {
	return (float)x *(1.f / (float)(1UL << 17));
}

//-----------------------------------------------------------------------------
// Q1.15: -1 .. 0.999

static inline float q15_to_float(q15 x) {
	return (float)x *(1.f / (float)(1UL << 15));
}

static inline q15 float_to_q15(float x) {
	return (q15) (x * (float)(1UL << 15));
}

static inline q15 mul_q15(q15 a, q15 b) {
	int32_t x = (int32_t) a * (int32_t) b;
	return (q15) (x >> 15);
}

//-----------------------------------------------------------------------------

#endif				// TSE_QFMT_H

//-----------------------------------------------------------------------------
