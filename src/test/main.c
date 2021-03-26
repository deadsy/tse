//-----------------------------------------------------------------------------
/*

Tiny Synth Engine Test Code

*/
//-----------------------------------------------------------------------------

#define TSE_LOG_ENABLE

#include "log.h"
#include "tse.h"

//-----------------------------------------------------------------------------

int main(int argc, char **argv) {

	log_init(TSE_LOG_TRACE, true);

	log_info("tiny synth engine version %s", TSE_VERSION);

	log_info("%d samples/sec", AudioSampleFrequency);
	log_info("%d bytes/buffer", AudioBufferSize);
	log_info("%.2f ms/buffer", SecsPerAudioBuffer * 1000.f);

	rms_error("cosf/cosf_fast", 0.f, 4.f * Tau, 0.01f, cosf, cosf_fast);
	benchmark_f0("cos_q15", cos_q15, 2048);
	benchmark_f1("cosf_fast", cosf_fast, 2048);
	benchmark_f1("cosf", cosf, 2048);

	rms_error("pow2_slow/pow2_fast", 0.f, 1.f, 0.01f, pow2_slow, pow2_fast);
	benchmark_f1("pow2_slow", pow2_slow, 2048);
	benchmark_f1("pow2_fast", pow2_fast, 2048);

	rms_error("m2f_slow/m2f_fast", 0.f, 127.f, 0.3f, m2f_slow, m2f_fast);
	benchmark_f1("m2f_slow", m2f_slow, 2048);
	benchmark_f1("m2f_fast", m2f_fast, 2048);
	benchmark_f2("m2f", m2f, 2048);

	return 0;
}

//-----------------------------------------------------------------------------
