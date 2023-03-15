#include <math.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#if 0
extern char * _argv_0;
#define MATH do { if (getenv("LIBM_DEBUG")) { fprintf(stderr, "%s called math function %s\n", _argv_0, __func__); } } while (0)
#else
#define MATH (void)0
#endif

double exp(double x) {
	return __builtin_powi(2.71828182846, x);
}

double sqrt(double x)
{
	return __builtin_sqrt(x);
}

int abs(int j) {
	return (j < 0 ? -j : j);
}

double fabs(double x) {
	MATH;
	return __builtin_fabs(x);
}

float fabsf(float x) {
	return fabs(x);
}

float sqrtf(float x) {
	return sqrt(x);
}

static double bad_sine_table[] = {
	0,
		0.01745240644,
		0.03489949671,
		0.05233595625,
		0.06975647375,
		0.08715574276,
		0.1045284633,
		0.1218693434,
		0.139173101,
		0.1564344651,
		0.1736481777,
		0.1908089954,
		0.2079116908,
		0.2249510544,
		0.2419218956,
		0.2588190451,
		0.2756373559,
		0.2923717048,
		0.3090169944,
		0.3255681545,
		0.3420201434,
		0.3583679496,
		0.3746065935,
		0.3907311285,
		0.4067366431,
		0.4226182618,
		0.4383711468,
		0.4539904998,
		0.4694715628,
		0.4848096203,
		0.5000000001,
		0.515038075,
		0.5299192643,
		0.5446390351,
		0.5591929035,
		0.5735764364,
		0.5877852524,
		0.6018150232,
		0.6156614754,
		0.6293203911,
		0.6427876098,
		0.6560590291,
		0.6691306064,
		0.6819983601,
		0.6946583705,
		0.7071067813,
		0.7193398004,
		0.7313537017,
		0.7431448256,
		0.7547095803,
		0.7660444432,
		0.7771459615,
		0.7880107537,
		0.7986355101,
		0.8090169944,
		0.8191520444,
		0.8290375726,
		0.838670568,
		0.8480480962,
		0.8571673008,
		0.8660254039,
		0.8746197072,
		0.8829475929,
		0.8910065243,
		0.8987940464,
		0.9063077871,
		0.9135454577,
		0.9205048535,
		0.9271838546,
		0.9335804266,
		0.9396926208,
		0.9455185757,
		0.9510565163,
		0.956304756,
		0.961261696,
		0.9659258263,
		0.9702957263,
		0.9743700648,
		0.9781476008,
		0.9816271835,
		0.984807753,
		0.9876883406,
		0.9902680688,
		0.9925461517,
		0.9945218954,
		0.9961946981,
		0.9975640503,
		0.9986295348,
		0.999390827,
		0.9998476952,
		1,
		0.9998476952,
		0.999390827,
		0.9986295347,
		0.9975640502,
		0.9961946981,
		0.9945218953,
		0.9925461516,
		0.9902680687,
		0.9876883406,
		0.984807753,
		0.9816271834,
		0.9781476007,
		0.9743700647,
		0.9702957262,
		0.9659258262,
		0.9612616959,
		0.9563047559,
		0.9510565162,
		0.9455185755,
		0.9396926207,
		0.9335804264,
		0.9271838545,
		0.9205048534,
		0.9135454575,
		0.9063077869,
		0.8987940462,
		0.8910065241,
		0.8829475927,
		0.874619707,
		0.8660254036,
		0.8571673006,
		0.848048096,
		0.8386705678,
		0.8290375724,
		0.8191520441,
		0.8090169942,
		0.7986355099,
		0.7880107534,
		0.7771459613,
		0.7660444429,
		0.75470958,
		0.7431448253,
		0.7313537014,
		0.7193398001,
		0.707106781,
		0.6946583702,
		0.6819983598,
		0.6691306061,
		0.6560590288,
		0.6427876094,
		0.6293203908,
		0.6156614751,
		0.6018150229,
		0.587785252,
		0.5735764361,
		0.5591929032,
		0.5446390347,
		0.5299192639,
		0.5150380746,
		0.4999999997,
		0.4848096199,
		0.4694715625,
		0.4539904994,
		0.4383711465,
		0.4226182614,
		0.4067366428,
		0.3907311282,
		0.3746065931,
		0.3583679492,
		0.342020143,
		0.3255681541,
		0.309016994,
		0.2923717044,
		0.2756373555,
		0.2588190447,
		0.2419218952,
		0.224951054,
		0.2079116904,
		0.190808995,
		0.1736481773,
		0.1564344647,
		0.1391731006,
		0.121869343,
		0.1045284629,
		0.08715574235,
		0.06975647334,
		0.05233595584,
		0.0348994963,
		0.01745240603,
		-0.000000000410206857,
		-0.01745240685,
		-0.03489949712,
		-0.05233595666,
		-0.06975647416,
		-0.08715574317,
		-0.1045284637,
		-0.1218693438,
		-0.1391731014,
		-0.1564344655,
		-0.1736481781,
		-0.1908089958,
		-0.2079116912,
		-0.2249510548,
		-0.241921896,
		-0.2588190455,
		-0.2756373562,
		-0.2923717052,
		-0.3090169948,
		-0.3255681549,
		-0.3420201438,
		-0.35836795,
		-0.3746065938,
		-0.3907311289,
		-0.4067366435,
		-0.4226182622,
		-0.4383711472,
		-0.4539905002,
		-0.4694715632,
		-0.4848096207,
		-0.5000000004,
		-0.5150380753,
		-0.5299192646,
		-0.5446390354,
		-0.5591929039,
		-0.5735764368,
		-0.5877852527,
		-0.6018150235,
		-0.6156614757,
		-0.6293203914,
		-0.6427876101,
		-0.6560590294,
		-0.6691306067,
		-0.6819983604,
		-0.6946583708,
		-0.7071067815,
		-0.7193398007,
		-0.731353702,
		-0.7431448258,
		-0.7547095806,
		-0.7660444435,
		-0.7771459618,
		-0.7880107539,
		-0.7986355104,
		-0.8090169947,
		-0.8191520446,
		-0.8290375729,
		-0.8386705682,
		-0.8480480964,
		-0.857167301,
		-0.8660254041,
		-0.8746197074,
		-0.8829475931,
		-0.8910065244,
		-0.8987940465,
		-0.9063077873,
		-0.9135454579,
		-0.9205048537,
		-0.9271838548,
		-0.9335804267,
		-0.939692621,
		-0.9455185758,
		-0.9510565165,
		-0.9563047561,
		-0.9612616961,
		-0.9659258264,
		-0.9702957264,
		-0.9743700649,
		-0.9781476009,
		-0.9816271836,
		-0.9848077531,
		-0.9876883407,
		-0.9902680688,
		-0.9925461517,
		-0.9945218954,
		-0.9961946981,
		-0.9975640503,
		-0.9986295348,
		-0.999390827,
		-0.9998476952,
		-1,
		-0.9998476951,
		-0.999390827,
		-0.9986295347,
		-0.9975640502,
		-0.996194698,
		-0.9945218953,
		-0.9925461516,
		-0.9902680687,
		-0.9876883405,
		-0.9848077529,
		-0.9816271833,
		-0.9781476006,
		-0.9743700646,
		-0.9702957261,
		-0.9659258261,
		-0.9612616958,
		-0.9563047558,
		-0.9510565161,
		-0.9455185754,
		-0.9396926206,
		-0.9335804263,
		-0.9271838543,
		-0.9205048532,
		-0.9135454574,
		-0.9063077868,
		-0.898794046,
		-0.8910065239,
		-0.8829475925,
		-0.8746197068,
		-0.8660254034,
		-0.8571673003,
		-0.8480480958,
		-0.8386705676,
		-0.8290375722,
		-0.8191520439,
		-0.809016994,
		-0.7986355096,
		-0.7880107532,
		-0.777145961,
		-0.7660444427,
		-0.7547095798,
		-0.743144825,
		-0.7313537011,
		-0.7193397998,
		-0.7071067807,
		-0.6946583699,
		-0.6819983595,
		-0.6691306058,
		-0.6560590284,
		-0.6427876091,
		-0.6293203905,
		-0.6156614747,
		-0.6018150226,
		-0.5877852517,
		-0.5735764357,
		-0.5591929029,
		-0.5446390344,
		-0.5299192636,
		-0.5150380743,
		-0.4999999993,
		-0.4848096196,
		-0.4694715621,
		-0.4539904991,
		-0.4383711461,
		-0.422618261,
		-0.4067366424,
		-0.3907311278,
		-0.3746065927,
		-0.3583679488,
		-0.3420201426,
		-0.3255681537,
		-0.3090169936,
		-0.292371704,
		-0.2756373551,
		-0.2588190443,
		-0.2419218948,
		-0.2249510536,
		-0.20791169,
		-0.1908089946,
		-0.1736481769,
		-0.1564344643,
		-0.1391731002,
		-0.1218693426,
		-0.1045284625,
		-0.08715574194,
		-0.06975647293,
		-0.05233595543,
		-0.03489949589,
		-0.01745240562,
		0.0
};

double sin(double x) {
	MATH;
	if (x < 0.0) {
		x += 3.141592654 * 2.0 * 100.0;
	}
	int i = x * 360.0 / (3.141592654 * 2.0);
	double z = x * 360.0 / (3.141592654 * 2.0);
	z -= i;

	i = i % 360;

	//fprintf(stderr, "z = %f\n", z);

	double a = bad_sine_table[i];
	double b = bad_sine_table[(i+1)%360];

	return a * (1.0-z) + b * (z);
}

double cos(double x) {
	return sin(x + 3.141592654 / 2.0);
}

double atan(double x) {
	return atan2(x,1.0);
}

double hypot(double x, double y) {
	return sqrt(x * x + y * y);
}

double modf(double x, double *iptr) {
	MATH;
	int i = (int)x;
	*iptr = (double)i;
	return x - i;
}

double frexp(double x, int *exp) {
	MATH;
	struct {
		uint32_t lsw;
		uint32_t msw;
	} extract;

	memcpy(&extract, &x, sizeof(double));

	*exp = ((extract.msw & 0x7ff00000) >> 20) - 0x3FE;

	struct {
		uint32_t lsw;
		uint32_t msw;
	} out_double;

	out_double.msw = (extract.msw & 0x800fffff) | 0x3FE00000;
	out_double.lsw = extract.lsw;

	double out;
	memcpy(&out, &out_double, sizeof(double));
	return out;
}

double cosh(double x) {
	return (exp(x) + exp(-x)) / 2.0;
}

double sinh(double x) {
	return (exp(x) - exp(-x)) / 2.0;
}

double tanh(double x) {
	return (exp(2.0*x) - 1.0) / (exp(2.0*x) + 1.0);
}

int fpclassify(double x) {
	union {
		double asFloat;
		uint64_t asInt;
	} bits = {x};
	uint64_t exponent = (bits.asInt >> 52) & 0x7FF;
	uint64_t mantissa = (bits.asInt & 0xFffffFFFFffffULL);

	if (exponent == 0x7FF) {
		return mantissa ? FP_NAN : FP_INFINITE;
	} else if (exponent == 0) {
		return mantissa ? FP_SUBNORMAL : FP_ZERO;
	}
	return FP_NORMAL;
}
