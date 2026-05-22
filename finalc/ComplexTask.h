

#ifndef COMPLEX_TASK_H
#define COMPLEX_TASK_H

#include <complex.h>
#include <stdbool.h>

#define PI 3.14159265358979323846
#define N_SIZE 16384

/* Base structure for pair of complex roots */
typedef struct {
    double complex z1, z2;
} PairComplex;

/* Base structure for three complex roots */
typedef struct {
    double complex z1, z2, z3;
} TripletComplex;

/* Base structure for four complex roots */
typedef struct {
    double complex z1, z2, z3, z4;
} QuartetComplex;

/* Solve quadratic equation
   Calculates the roots of Az^2 + Bz + C = 0
   @param - IN - A (Coefficient A)
   @param - IN - B (Coefficient B)
   @param - IN - C (Coefficient C)
   @result - PairComplex: structure containing two roots
*/
PairComplex solve_quadratic(double complex A, double complex B, double complex C);

/* Taylor series for ln(1+z)
   Calculates the natural logarithm using Taylor series expansion
   @param - IN - z (Complex point, |z| < 1)
   @param - IN - epsilon (Accuracy)
   @result - double complex: calculated value
*/
double complex taylor_ln(double complex z, double epsilon);

/* Taylor series for arctg(z)
   Calculates the arctangent using Taylor series expansion
   @param - IN - z (Complex point, |z| < 1)
   @param - IN - epsilon (Accuracy)
   @result - double complex: calculated value
*/
double complex taylor_arctg(double complex z, double epsilon);

/* Solve cubic equation
   Calculates the roots using Cardano's formula
   @param - IN - A (Coefficient A)
   @param - IN - B (Coefficient B)
   @param - IN - C (Coefficient C)
   @result - TripletComplex: structure containing three roots
*/
TripletComplex solve_cubic(double complex A, double complex B, double complex C);

/* Solve quartic equation
   Calculates the roots using Ferrari's formula
   @param - IN - a, b, c, d (Real coefficients)
   @result - QuartetComplex: structure containing four roots
*/
QuartetComplex solve_quartic(double a, double b, double c, double d);

/* Solve convolution system using FFT
   Solves a system of linear equations using Fast Fourier Transform
   @param - IN - A_in (Array of coefficients)
   @param - IN - b_in (Array of constant terms)
   @result - double complex*: Pointer to dynamically allocated array of unknowns
*/
double complex* solve_convolution_system(const double complex* A_in, const double complex* b_in);

/* Perform in-place FFT on a complex array
   @param - INOUT - a (array of complex values)
   @param - IN - n (size, must be a power of two)
   @param - IN - invert (false for forward FFT, true for inverse FFT)
*/
void fft(double complex* a, int n, bool invert);

#endif // COMPLEX_TASK_H