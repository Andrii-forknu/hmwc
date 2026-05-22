
#include "ComplexTask.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

// ==============================================================================
// I/O UTILITIES FOR CONSOLE AND FILE SUPPORT
// ==============================================================================

/* Print to both console and output file */
void print_out(FILE* fout, const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    if (fout) {
        va_start(args, format);
        vfprintf(fout, format, args);
        va_end(args);
    }
}

void print_complex(FILE* fout, double complex c) {
    double re = creal(c);
    double im = cimag(c);
    print_out(fout, "%g%s%gi", re, (im >= 0 ? "+" : ""), im);
}

void clear_input_buffer(FILE* fin) {
    if (fin != stdin) return;
    int c;
    while ((c = fgetc(fin)) != '\n' && c != EOF) {}
}

double read_double(FILE* fin, FILE* fout, const char* prompt) {
    double val;
    while (true) {
        if (fin == stdin) print_out(fout, "%s", prompt);
        if (fscanf(fin, "%lf", &val) == 1) {
            clear_input_buffer(fin);
            if (fin != stdin) print_out(fout, "%s%g\n", prompt, val);
            return val;
        }
        if (fin == stdin) {
            print_out(fout, "[Error] Please enter a valid real number.\n");
            clear_input_buffer(fin);
        } else {
            print_out(fout, "[Error] File format error reading double.\n");
            exit(1);
        }
    }
}

int read_int(FILE* fin, FILE* fout, const char* prompt) {
    int val;
    while (true) {
        if (fin == stdin) print_out(fout, "%s", prompt);
        if (fscanf(fin, "%d", &val) == 1) {
            clear_input_buffer(fin);
            if (fin != stdin) print_out(fout, "%s%d\n", prompt, val);
            return val;
        }
        if (fin == stdin) {
            print_out(fout, "[Error] Please enter a valid integer.\n");
            clear_input_buffer(fin);
        } else {
            print_out(fout, "[Error] File format error reading int.\n");
            exit(1);
        }
    }
}

double complex read_complex_std(FILE* fin, FILE* fout, const char* prompt) {
    double re, im;
    while (true) {
        if (fin == stdin) print_out(fout, "%s", prompt);
        if (fscanf(fin, " (%lf,%lf)", &re, &im) == 2) {
            clear_input_buffer(fin);
            if (fin != stdin) print_out(fout, "%s(%g,%g)\n", prompt, re, im);
            return re + im * I;
        }
        if (fin == stdin) {
            print_out(fout, "[Error] Use format (re,im), e.g., (3,4).\n");
            clear_input_buffer(fin);
        } else {
            print_out(fout, "[Error] File format error reading complex.\n");
            exit(1);
        }
    }
}

// ==============================================================================
// DEMONSTRATION FUNCTIONS
// ==============================================================================

void demo_complex_std(FILE* fin, FILE* fout) {
    print_out(fout, "\n--- Demonstration of Standard complex.h ---\n");
    double complex z1 = read_complex_std(fin, fout, "Enter the first number (format (re,im)): ");
    double complex z2 = read_complex_std(fin, fout, "Enter the second number (format (re,im)): ");
    
    print_out(fout, "z1: "); print_complex(fout, z1);
    print_out(fout, ", Modulus: %g, Argument: %g\n", cabs(z1), carg(z1));
    print_out(fout, "z1 + z2 = "); print_complex(fout, z1 + z2); print_out(fout, "\n");
}

void demo_quadratic(FILE* fin, FILE* fout) {
    print_out(fout, "\n--- Quadratic equation Az^2 + Bz + C = 0 ---\n");
    double complex A = read_complex_std(fin, fout, "Coefficient A (format (re,im)): ");
    double complex B = read_complex_std(fin, fout, "Coefficient B (format (re,im)): ");
    double complex C = read_complex_std(fin, fout, "Coefficient C (format (re,im)): ");
    
    PairComplex roots = solve_quadratic(A, B, C);
    print_out(fout, "Roots: z1 = "); print_complex(fout, roots.z1);
    print_out(fout, ", z2 = "); print_complex(fout, roots.z2); print_out(fout, "\n");
}

void demo_taylor(FILE* fin, FILE* fout) {
    print_out(fout, "\n--- Taylor Series (|z| < 1) ---\n");
    double complex z;
    while (true) {
        z = read_complex_std(fin, fout, "Enter point z (|z| < 1) in format (re,im): ");
        if (cabs(z) < 1.0) break;
        if (fin == stdin) print_out(fout, "[Warning] Modulus >= 1. Diverges. Try again!\n");
        else { print_out(fout, "File provided invalid z.\n"); exit(1); }
    }

    double eps = read_double(fin, fout, "Enter accuracy epsilon (e.g. 0.000001): ");

    print_out(fout, "ln(1+z) [Taylor]: "); print_complex(fout, taylor_ln(z, eps));
    print_out(fout, " | [Std C]: "); print_complex(fout, clog(1.0 + z)); print_out(fout, "\n");
    
    print_out(fout, "arctg(z) [Taylor]: "); print_complex(fout, taylor_arctg(z, eps));
    print_out(fout, " | [Std C]: "); print_complex(fout, catan(z)); print_out(fout, "\n");
}

void demo_cubic(FILE* fin, FILE* fout) {
    print_out(fout, "\n--- Cubic equation z^3 + Az^2 + Bz + C = 0 (Cardano) ---\n");
    double complex A = read_complex_std(fin, fout, "Coefficient A (format (re,im)): ");
    double complex B = read_complex_std(fin, fout, "Coefficient B (format (re,im)): ");
    double complex C = read_complex_std(fin, fout, "Coefficient C (format (re,im)): ");
    
    TripletComplex roots = solve_cubic(A, B, C);
    print_out(fout, "z1 = "); print_complex(fout, roots.z1); print_out(fout, "\n");
    print_out(fout, "z2 = "); print_complex(fout, roots.z2); print_out(fout, "\n");
    print_out(fout, "z3 = "); print_complex(fout, roots.z3); print_out(fout, "\n");
}

void demo_quartic(FILE* fin, FILE* fout) {
    print_out(fout, "\n--- 4th degree equation x^4 + ax^3 + bx^2 + cx + d = 0 (Ferrari) ---\n");
    print_out(fout, "Enter REAL coefficients:\n");
    double a = read_double(fin, fout, "a = ");
    double b = read_double(fin, fout, "b = ");
    double c = read_double(fin, fout, "c = ");
    double d = read_double(fin, fout, "d = ");

    QuartetComplex roots = solve_quartic(a, b, c, d);
    print_out(fout, "x1 = "); print_complex(fout, roots.z1); print_out(fout, "\n");
    print_out(fout, "x2 = "); print_complex(fout, roots.z2); print_out(fout, "\n");
    print_out(fout, "x3 = "); print_complex(fout, roots.z3); print_out(fout, "\n");
    print_out(fout, "x4 = "); print_complex(fout, roots.z4); print_out(fout, "\n");
}

void demo_fft(FILE* fin, FILE* fout) {
    print_out(fout, "\n--- Solving a system of 16384 equations using FFT ---\n");
    double complex* A = (double complex*)calloc(N_SIZE, sizeof(double complex));
    double complex* b = (double complex*)calloc(N_SIZE, sizeof(double complex));

    int k = read_int(fin, fout, "How many elements do you want to enter manually? (max 16384): ");
    
    print_out(fout, "--- Entering array A ---\n");
    for (int i = 0; i < k; ++i) {
        char prompt[64];
        sprintf(prompt, "A[%d] (format (re,im)): ", i);
        A[i] = read_complex_std(fin, fout, prompt);
    }
    print_out(fout, "--- Entering array b ---\n");
    for (int i = 0; i < k; ++i) {
        char prompt[64];
        sprintf(prompt, "b[%d] (format (re,im)): ", i);
        b[i] = read_complex_std(fin, fout, prompt);
    }

    print_out(fout, "Calculating the vector of unknowns x...\n");
    double complex* x = solve_convolution_system(A, b);

    print_out(fout, "--- Checking the convolution system (first 3 equations) ---\n");
    for (int m = 0; m < 3; ++m) {
        double complex current_b = 0;
        for (int i = 0; i < N_SIZE; ++i) {
            int idx = m - i;
            if (idx < 0) idx += N_SIZE; 
            current_b += A[idx] * x[i];
        }
        print_out(fout, "Equation m=%d | Found b: ", m); print_complex(fout, current_b);
        print_out(fout, " | Expected b: "); print_complex(fout, b[m]); print_out(fout, "\n");
    }
    
    free(A);
    free(b);
    free(x);
}

void demo_fft_benchmark(FILE* fout) {
    print_out(fout, "\n--- Benchmark: FFT-based solver over 100 runs ---\n");
    double complex* A = (double complex*)calloc(N_SIZE, sizeof(double complex));
    double complex* b = (double complex*)calloc(N_SIZE, sizeof(double complex));

    if (!A || !b) {
        print_out(fout, "[Error] Memory allocation failed for benchmark data.\n");
        free(A);
        free(b);
        return;
    }

    for (int i = 0; i < N_SIZE; ++i) {
        A[i] = (i % 2 == 0 ? 1.0 : 2.0) + (i % 3 == 0 ? 1.0 : -1.0) * I;
        b[i] = (i % 5 == 0 ? 2.0 : -1.0) + (i % 7 == 0 ? 0.5 : -0.5) * I;
    }

    clock_t start = clock();
    for (int run = 0; run < 100; ++run) {
        double complex* x = solve_convolution_system(A, b);
        if (x) free(x);
    }
    clock_t end = clock();
    double totalSeconds = (double)(end - start) / CLOCKS_PER_SEC;
    double averageMs = totalSeconds * 1000.0 / 100.0;

    print_out(fout, "Average execution time for 100 FFT runs: %.3f ms\n", averageMs);

    free(A);
    free(b);
}

void print_complex_array(FILE* fout, const double complex* array, int n, const char* label) {
    print_out(fout, "%s\n", label);
    for (int i = 0; i < n; ++i) {
        print_out(fout, "[%2d] ", i);
        print_complex(fout, array[i]);
        print_out(fout, "\n");
    }
}

void demo_fft_visualization(FILE* fout) {
    const int smallN = 8;
    print_out(fout, "\n--- FFT Visualization on a small array (size %d) ---\n", smallN);

    double complex data[smallN];
    for (int i = 0; i < smallN; ++i) {
        data[i] = i + 1 + I * (smallN - i);
    }

    double complex working[smallN];
    for (int i = 0; i < smallN; ++i) working[i] = data[i];

    print_complex_array(fout, data, smallN, "Input array:");
    fft(working, smallN, false);
    print_complex_array(fout, working, smallN, "FFT result:");
    fft(working, smallN, true);
    print_complex_array(fout, working, smallN, "Inverse FFT (reconstructed input):");
}

// ==============================================================================
// MAIN MENU
// ==============================================================================

int main() {
    FILE* fin = stdin;
    FILE* fout = fopen("ComplexTask_result.txt", "w");
    
    if (!fout) {
        printf("Failed to open output file.\n");
        return 1;
    }

    print_out(fout, "========================================================\n");
    print_out(fout, " WELCOME TO THE COMPLEX NUMBERS CALCULATION PROGRAM! \n");
    print_out(fout, "========================================================\n");
    print_out(fout, "Select program mode:\n");
    print_out(fout, "1 - Console Input (Manual)\n");
    print_out(fout, "2 - File Input (reads from ComplexTask_test.txt)\n");
    print_out(fout, "3 - Benchmark FFT over 100 runs and print average time\n");
    print_out(fout, "4 - Visualize FFT on a small matrix and print full results\n");
    print_out(fout, "0 - Exit\n");
    
    int mode_choice = read_int(stdin, fout, "Your choice (0-4): ");
    
    switch (mode_choice) {
        case 1:
            print_out(fout, "\n*** CONSOLE INPUT MODE STARTED ***\n");
            demo_complex_std(stdin, fout);
            demo_quadratic(stdin, fout);
            demo_taylor(stdin, fout);
            demo_cubic(stdin, fout);
            demo_quartic(stdin, fout);
            demo_fft(stdin, fout);
            break;
        case 2:
            fin = fopen("ComplexTask_test.txt", "r");
            if (!fin) {
                print_out(fout, "[Error] Could not open ComplexTask_test.txt! Falling back to console.\n");
                fin = stdin;
            } else {
                print_out(fout, "\n*** FILE INPUT MODE STARTED ***\n");
            }
            demo_complex_std(fin, fout);
            demo_quadratic(fin, fout);
            demo_taylor(fin, fout);
            demo_cubic(fin, fout);
            demo_quartic(fin, fout);
            demo_fft(fin, fout);
            break;
        case 3:
            demo_fft_benchmark(fout);
            break;
        case 4:
            demo_fft_visualization(fout);
            break;
        default:
            print_out(fout, "Exiting program.\n");
            break;
    }

    print_out(fout, "\nProgram finished.\n");
    
    if (fin != stdin) fclose(fin);
    if (fout) fclose(fout);
    
    return 0;
}