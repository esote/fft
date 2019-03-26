#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L \
	|| !defined(__STDC__)
#error "fft relies on C99 complex.h, C99 is required"
#endif

#if defined(__STDC_NO_COMPLEX__)
#error "complex.h is not supported on your system"
#endif

#if !defined(FFT_NO_INCLUDES)
#include <complex.h>
#include <errno.h>
#include <math.h>
#endif

#if defined(FFT_PRIVATE)
#define FFT_API static
#else
#define FFT_API extern
#endif

#if !defined(M_PI)
#define M_PI	3.14159265358979323846
#endif

static void
_fft_internal(double complex *restrict const buf,
	double complex *restrict const out, size_t const n, size_t const step)
{
	double complex t;
	size_t i;

	if (step >= n) {
		return;
	}

	_fft_internal(out, buf, n, step * 2);
	_fft_internal(out + step, buf + step, n, step * 2);

	for (i = 0; i < n; i += 2 * step) {
		t = cexp(-I * M_PI * (double)i / (double)n) * out[i + step];
		buf[i / 2] = out[i] + t;
		buf[i + (n - i) / 2] = out[i] - t;
	}
}

FFT_API int
fft(double complex *const buf, size_t const n)
{
	size_t i;
	double complex out[n];

	if ((n & (n - 1)) != 0) {
		/* n must be a power of two, if not you can pad with zeroes */
		errno = EINVAL;
		return -1;
	}

	for (i = 0; i < n; ++i) {
		out[i] = buf[i];
	}

	_fft_internal(buf, out, n, 1);
	return 0;
}

