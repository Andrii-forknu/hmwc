

#include "ComplexTask.h"
#include <tgmath.h>
#include <stdlib.h>
#include <string.h>

PairComplex solve_quadratic(double complex A, double complex B, double complex C) {
    double complex D = B * B - 4.0 * A * C;
    double complex sqrtD = csqrt(D); 
    PairComplex roots;
    roots.z1 = (-B + sqrtD) / (2.0 * A);
    roots.z2 = (-B - sqrtD) / (2.0 * A);
    return roots;
}

double complex taylor_ln(double complex z, double epsilon) {
    double complex sum = 0, term = z;
    int n = 1;
    while (cabs(term / (double)n) >= epsilon) {
        if (n % 2 == 1) sum += term / (double)n;
        else sum -= term / (double)n;
        term *= z;
        n++;
    }
    return sum;
}

double complex taylor_arctg(double complex z, double epsilon) {
    double complex sum = 0, term = z, z_sq = z * z;
    int n = 0;
    while (true) {
        double complex current = term / (double)(2 * n + 1);
        if (cabs(current) < epsilon) break;
        if (n % 2 == 0) sum += current;
        else sum -= current;
        term *= z_sq;
        n++;
    }
    return sum;
}

TripletComplex solve_cubic(double complex A, double complex B, double complex C) {
    double complex p = B - (A * A) / 3.0;
    double complex q = C - (A * B) / 3.0 + (2.0 * A * A * A) / 27.0;
    double complex D = (q * q) / 4.0 + (p * p * p) / 27.0;
    double complex sqrtD = csqrt(D);

    double complex u = cpow(-q / 2.0 + sqrtD, 1.0 / 3.0);
    double complex v = cpow(-q / 2.0 - sqrtD, 1.0 / 3.0);

    double complex omega1 = -0.5 + (sqrt(3.0) / 2.0) * I;
    double complex omega2 = -0.5 - (sqrt(3.0) / 2.0) * I;

    TripletComplex roots;
    roots.z1 = u + v - A / 3.0;
    roots.z2 = u * omega1 + v * omega2 - A / 3.0;
    roots.z3 = u * omega2 + v * omega1 - A / 3.0;
    return roots;
}

QuartetComplex solve_quartic(double a, double b, double c, double d) {
    TripletComplex cubic_roots = solve_cubic(-b, (a * c - 4.0 * d), -(a * a * d + c * c - 4.0 * b * d));
    double complex y = cubic_roots.z1; 

    double complex R = csqrt(a * a / 4.0 - b + y);
    double complex D1, D2;

    if (cabs(R) > 1e-9) {
        D1 = csqrt(3.0 * a * a / 4.0 - R * R - 2.0 * b + (4.0 * a * b - 8.0 * c - a * a * a) / (4.0 * R));
        D2 = csqrt(3.0 * a * a / 4.0 - R * R - 2.0 * b - (4.0 * a * b - 8.0 * c - a * a * a) / (4.0 * R));
    } else {
        D1 = csqrt(3.0 * a * a / 4.0 - 2.0 * b + 2.0 * csqrt(y * y - 4.0 * d));
        D2 = csqrt(3.0 * a * a / 4.0 - 2.0 * b - 2.0 * csqrt(y * y - 4.0 * d));
    }

    QuartetComplex roots;
    roots.z1 = -a / 4.0 + R / 2.0 + D1 / 2.0;
    roots.z2 = -a / 4.0 + R / 2.0 - D1 / 2.0;
    roots.z3 = -a / 4.0 - R / 2.0 + D2 / 2.0;
    roots.z4 = -a / 4.0 - R / 2.0 - D2 / 2.0;
    return roots;
}

/* swap_complex (Internal function) */
void swap_complex(double complex* a, double complex* b) {
    double complex temp = *a;
    *a = *b;
    *b = temp;
}

/* fft (Internal function) */
void fft(double complex* a, int n, bool invert) {
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap_complex(&a[i], &a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        double complex wlen = cos(ang) + sin(ang) * I;
        for (int i = 0; i < n; i += len) {
            double complex w = 1;
            for (int j = 0; j < len / 2; j++) {
                double complex u = a[i + j];
                double complex v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (int i = 0; i < n; i++) a[i] /= n;
    }
}

double complex* solve_convolution_system(const double complex* A_in, const double complex* b_in) {
    double complex* fft_A = (double complex*)malloc(N_SIZE * sizeof(double complex));
    double complex* fft_b = (double complex*)malloc(N_SIZE * sizeof(double complex));
    double complex* fft_x = (double complex*)malloc(N_SIZE * sizeof(double complex));

    memcpy(fft_A, A_in, N_SIZE * sizeof(double complex));
    memcpy(fft_b, b_in, N_SIZE * sizeof(double complex));

    fft(fft_A, N_SIZE, false);
    fft(fft_b, N_SIZE, false);

    for (int i = 0; i < N_SIZE; ++i) {
        if (cabs(fft_A[i]) < 1e-9) fft_x[i] = 0;
        else fft_x[i] = fft_b[i] / fft_A[i];
    }

    fft(fft_x, N_SIZE, true);
    
    free(fft_A);
    free(fft_b);
    return fft_x;
}