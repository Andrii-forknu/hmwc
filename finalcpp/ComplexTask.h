

#ifndef COMPLEX_TASK_H
#define COMPLEX_TASK_H

#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <utility>
#include <cstdlib>
#include <string>
#include <sstream>
#include <limits>
#include <chrono>
#include <iomanip> // Для красивого форматування матриці
using Complex = std::complex<double>;

// ==============================================================================
// FUNCTIONS FOR SAFE INPUT
// ==============================================================================
void clear_input_buffer();
double read_double(const std::string& prompt);
int read_int(const std::string& prompt);
Complex read_complex_std(const std::string& prompt);

// ==============================================================================
// ITEM 1: CUSTOM CLASS
// ==============================================================================
class MyComplex {
private:
    double re, im;
public:
    MyComplex(double r = 0.0, double i = 0.0);

    double real() const;
    double imag() const;
    double abs() const;
    double arg() const;

    MyComplex operator+(const MyComplex& other) const;
    MyComplex operator-(const MyComplex& other) const;

    friend std::ostream& operator<<(std::ostream& os, const MyComplex& c);
    friend std::istream& operator>>(std::istream& is, MyComplex& c);
};

void demo_custom_class(bool auto_mode);

// ==============================================================================
// ITEMS 2, 3, 4, 5: MATHEMATICAL CALCULATIONS AND DEMO FUNCTIONS
// ==============================================================================
std::pair<Complex, Complex> solve_quadratic(Complex A, Complex B, Complex C);
void demo_quadratic(bool auto_mode);

Complex taylor_ln(Complex z, double epsilon);
Complex taylor_arctg(Complex z, double epsilon);
void demo_taylor(bool auto_mode);

std::vector<Complex> solve_cubic(Complex A, Complex B, Complex C);
void demo_cubic(bool auto_mode);

std::vector<Complex> solve_quartic(double a, double b, double c, double d);
void demo_quartic(bool auto_mode);

void fft(std::vector<Complex>& a, bool invert);
std::vector<Complex> solve_convolution_system(const std::vector<Complex>& A, const std::vector<Complex>& b);
void demo_fft(bool auto_mode);
// ==============================================================================
// ITEM 6: BENCHMARK & VISUALIZATION
// ==============================================================================
void run_benchmark();
void visualize_fft_matrix();
// ==============================================================================
// ITEM 7: PROOF OF CORRECTNESS
// ==============================================================================
std::vector<Complex> naive_dft(const std::vector<Complex>& x, bool invert);
void verify_fft_correctness();
#endif // COMPLEX_TASK_H