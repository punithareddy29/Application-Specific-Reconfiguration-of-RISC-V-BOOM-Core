#include "hpm.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef SIZE
#define SIZE 32
#endif

typedef struct {
    double real;
    double imag;
} Complex;

void fft(Complex *X, int N) {
    if (N <= 1) return;

    Complex *even = (Complex *)malloc(sizeof(Complex) * (N / 2));
    Complex *odd = (Complex *)malloc(sizeof(Complex) * (N / 2));

    for (int i = 0; i < N / 2; i++) {
        even[i] = X[i * 2];
        odd[i] = X[i * 2 + 1];
    }

    fft(even, N / 2);
    fft(odd, N / 2);

    double angle = -2 * M_PI / N;
    for (int k = 0; k < N / 2; k++) {
        double cos_val = cos(k * angle);
        double sin_val = sin(k * angle);

        Complex t;
        t.real = cos_val * odd[k].real - sin_val * odd[k].imag;
        t.imag = sin_val * odd[k].real + cos_val * odd[k].imag;

        X[k].real = even[k].real + t.real;
        X[k].imag = even[k].imag + t.imag;

        X[k + N / 2].real = even[k].real - t.real;
        X[k + N / 2].imag = even[k].imag - t.imag;
    }

    free(even);
    free(odd);
}

int main(void) {
    printf("Generating FFT input of size %d\n", SIZE);

    Complex *X = (Complex *)malloc(sizeof(Complex) * SIZE);
    for (int i = 0; i < SIZE; i++) {
        X[i].real = i;
        X[i].imag = 0;
    }

    printf("Computing the FFT...\n");

    /* Enable performance counters */
    hpm_init();

    fft(X, SIZE);

    /* Print performance counter data */
    hpm_print();

    free(X);

    return 0;
}
