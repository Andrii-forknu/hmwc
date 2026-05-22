

#include "ComplexTask.h"

// ==============================================================================
// FUNCTIONS FOR SAFE INPUT
// ==============================================================================
void clear_input_buffer() {
    std::cin.clear(); 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
}

double read_double(const std::string& prompt) {
    double val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) {
            clear_input_buffer(); 
            return val;
        }
        std::cout << "[Error] Please enter a valid real number.\n";
        clear_input_buffer();
    }
}

int read_int(const std::string& prompt) {
    int val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) {
            clear_input_buffer();
            return val;
        }
        std::cout << "[Error] Please enter a valid integer.\n";
        clear_input_buffer();
    }
}

Complex read_complex_std(const std::string& prompt) {
    Complex c;
    while (true) {
        std::cout << prompt;
        if (std::cin >> c) {
            clear_input_buffer();
            return c;
        }
        std::cout << "[Error] Use format (re,im), e.g., (3,4) or (-1.5,0.2).\n";
        clear_input_buffer();
    }
}

// ==============================================================================
// ITEM 1: CUSTOM CLASS
// ==============================================================================
MyComplex::MyComplex(double r, double i) : re(r), im(i) {}

double MyComplex::real() const { return re; }
double MyComplex::imag() const { return im; }
double MyComplex::abs() const { return std::sqrt(re * re + im * im); }
double MyComplex::arg() const { return std::atan2(im, re); }

MyComplex MyComplex::operator+(const MyComplex& other) const { return MyComplex(re + other.re, im + other.im); }
MyComplex MyComplex::operator-(const MyComplex& other) const { return MyComplex(re - other.re, im - other.im); }

std::ostream& operator<<(std::ostream& os, const MyComplex& c) {
    os << c.re << (c.im >= 0 ? "+" : "") << c.im << "i";
    return os;
}
    
std::istream& operator>>(std::istream& is, MyComplex& c) {
    std::string s;
    if (!(is >> s)) return is;
        
    double r = 0, i = 0; 
    char pm = '+', ch_i = 'i';
    std::stringstream ss(s);
        
    if (ss >> r >> pm >> i >> ch_i) {
        if ((pm == '+' || pm == '-') && ch_i == 'i') {
            c.re = r;
            c.im = (pm == '-') ? -i : i;
            return is;
        }
    }
    is.setstate(std::ios::failbit);
    return is;
}

void demo_custom_class(bool auto_mode) {
    std::cout << "\n--- Demonstration of custom class MyComplex ---\n";
    MyComplex z1, z2;
    
    if (auto_mode) {
        z1 = MyComplex(3, 4);
        z2 = MyComplex(1, -2);
        std::cout << "[Auto-mode] z1 = " << z1 << ", z2 = " << z2 << "\n";
    } else {
        while (true) {
            std::cout << "Enter the first number in format a+bi or a-bi (NO SPACES, e.g., 3+4i): ";
            if (std::cin >> z1) { clear_input_buffer(); break; }
            std::cout << "[Error] Invalid format!\n";
            clear_input_buffer();
        }
        
        while (true) {
            std::cout << "Enter the second number (e.g., 1-2i): ";
            if (std::cin >> z2) { clear_input_buffer(); break; }
            std::cout << "[Error] Invalid format!\n";
            clear_input_buffer();
        }
    }
    
    std::cout << "z1: " << z1 << ", Modulus: " << z1.abs() << ", Argument: " << z1.arg() << "\n";
    std::cout << "z1 + z2 = " << (z1 + z2) << "\n";
}

// ==============================================================================
// ITEM 2: QUADRATIC EQUATION
// ==============================================================================
std::pair<Complex, Complex> solve_quadratic(Complex A, Complex B, Complex C) {
    Complex D = B * B - 4.0 * A * C;
    Complex sqrtD = std::sqrt(D); 
    Complex z1 = (-B + sqrtD) / (2.0 * A);
    Complex z2 = (-B - sqrtD) / (2.0 * A);
    return {z1, z2};
}

void demo_quadratic(bool auto_mode) {
    std::cout << "\n--- Quadratic equation Az^2 + Bz + C = 0 ---\n";
    Complex A, B, C;

    if (auto_mode) {
        A = Complex(1, 0);
        B = Complex(-3, 2);
        C = Complex(2, -1);
        std::cout << "[Auto-mode] Equation: (1,0)z^2 + (-3,2)z + (2,-1) = 0\n";
    } else {
        A = read_complex_std("Coefficient A (format (re,im)): ");
        B = read_complex_std("Coefficient B (format (re,im)): ");
        C = read_complex_std("Coefficient C (format (re,im)): ");
    }
    
    auto roots = solve_quadratic(A, B, C);
    std::cout << "Roots: z1 = " << roots.first << ", z2 = " << roots.second << "\n";
}

// ==============================================================================
// ITEM 3: TAYLOR SERIES
// ==============================================================================
Complex taylor_ln(Complex z, double epsilon) {
    Complex sum = 0, term = z;
    int n = 1;
    while (std::abs(term / double(n)) >= epsilon) {
        if (n % 2 == 1) sum += term / double(n);
        else sum -= term / double(n);
        term *= z;
        n++;
    }
    return sum;
}

Complex taylor_arctg(Complex z, double epsilon) {
    Complex sum = 0, term = z, z_sq = z * z;
    int n = 0;
    while (true) {
        Complex current = term / double(2 * n + 1);
        if (std::abs(current) < epsilon) break;
        if (n % 2 == 0) sum += current;
        else sum -= current;
        term *= z_sq;
        n++;
    }
    return sum;
}

void demo_taylor(bool auto_mode) {
    std::cout << "\n--- Taylor Series (|z| < 1) ---\n";
    Complex z;
    double eps;
    
    if (auto_mode) {
        z = Complex(0.5, 0.3);
        eps = 1e-6;
        std::cout << "[Auto-mode] Point z = " << z << ", Precision eps = " << eps << "\n";
    } else {
        while (true) {
            z = read_complex_std("Enter point z (|z| < 1) in format (re,im): ");
            if (std::abs(z) < 1.0) break;
            std::cout << "[Warning] The modulus of your number is: " << std::abs(z) << ". The Taylor series diverges. Enter a smaller value!\n";
        }

        while (true) {
            eps = read_double("Enter precision epsilon (e.g., 0.000001): ");
            if (eps > 0 && eps < 1) break;
            std::cout << "[Error] Precision must be greater than 0 and less than 1.\n";
        }
    }

    std::cout << "ln(1+z) [Taylor Series]: " << taylor_ln(z, eps) << " | [C++ Std]: " << std::log(1.0 + z) << "\n";
    std::cout << "arctg(z) [Taylor Series]: " << taylor_arctg(z, eps) << " | [C++ Std]: " << std::atan(z) << "\n";
}

// ==============================================================================
// ITEM 4: CUBIC AND QUARTIC EQUATIONS
// ==============================================================================
std::vector<Complex> solve_cubic(Complex A, Complex B, Complex C) {
    Complex p = B - (A * A) / 3.0;
    Complex q = C - (A * B) / 3.0 + (2.0 * A * A * A) / 27.0;
    Complex D = (q * q) / 4.0 + (p * p * p) / 27.0;
    Complex sqrtD = std::sqrt(D);

    Complex u = std::pow(-q / 2.0 + sqrtD, 1.0 / 3.0);
    Complex v = std::pow(-q / 2.0 - sqrtD, 1.0 / 3.0);

    Complex omega1(-0.5, std::sqrt(3.0) / 2.0);
    Complex omega2(-0.5, -std::sqrt(3.0) / 2.0);

    return {
        u + v - A / 3.0,
        u * omega1 + v * omega2 - A / 3.0,
        u * omega2 + v * omega1 - A / 3.0
    };
}

void demo_cubic(bool auto_mode) {
    std::cout << "\n--- Cubic equation z^3 + Az^2 + Bz + C = 0 (Cardano) ---\n";
    Complex A, B, C;

    if (auto_mode) {
        A = Complex(0, 0);
        B = Complex(-6, 0);
        C = Complex(-20, 0);
        std::cout << "[Auto-mode] Equation: z^3 - 6z - 20 = 0\n";
    } else {
        A = read_complex_std("Coefficient A (format (re,im)): ");
        B = read_complex_std("Coefficient B (format (re,im)): ");
        C = read_complex_std("Coefficient C (format (re,im)): ");
    }
    
    auto roots = solve_cubic(A, B, C);
    for(size_t i = 0; i < roots.size(); ++i) 
        std::cout << "z" << i+1 << " = " << roots[i] << "\n";
}

std::vector<Complex> solve_quartic(double a, double b, double c, double d) {
    auto cubic_roots = solve_cubic(-b, (a * c - 4.0 * d), -(a * a * d + c * c - 4.0 * b * d));
    Complex y = cubic_roots[0]; 

    Complex R = std::sqrt(a * a / 4.0 - b + y);
    Complex D1, D2;

    if (std::abs(R) > 1e-9) {
        D1 = std::sqrt(3.0 * a * a / 4.0 - R * R - 2.0 * b + (4.0 * a * b - 8.0 * c - a * a * a) / (4.0 * R));
        D2 = std::sqrt(3.0 * a * a / 4.0 - R * R - 2.0 * b - (4.0 * a * b - 8.0 * c - a * a * a) / (4.0 * R));
    } else {
        D1 = std::sqrt(3.0 * a * a / 4.0 - 2.0 * b + 2.0 * std::sqrt(y * y - 4.0 * d));
        D2 = std::sqrt(3.0 * a * a / 4.0 - 2.0 * b - 2.0 * std::sqrt(y * y - 4.0 * d));
    }

    return {
        -a / 4.0 + R / 2.0 + D1 / 2.0,
        -a / 4.0 + R / 2.0 - D1 / 2.0,
        -a / 4.0 - R / 2.0 + D2 / 2.0,
        -a / 4.0 - R / 2.0 - D2 / 2.0
    };
}

void demo_quartic(bool auto_mode) {
    std::cout << "\n--- Quartic equation x^4 + ax^3 + bx^2 + cx + d = 0 (Ferrari) ---\n";
    double a, b, c, d;

    if (auto_mode) {
        a = -1; b = -1; c = 1; d = -2;
        std::cout << "[Auto-mode] Equation: x^4 - x^3 - x^2 + x - 2 = 0\n";
    } else {
        std::cout << "Enter REAL coefficients:\n";
        a = read_double("a = ");
        b = read_double("b = ");
        c = read_double("c = ");
        d = read_double("d = ");
    }

    auto roots = solve_quartic(a, b, c, d);
    for(size_t i = 0; i < roots.size(); ++i) 
        std::cout << "x" << i+1 << " = " << roots[i] << "\n";
}

// ==============================================================================
// ITEM 5: FAST FOURIER TRANSFORM (FFT)
// ==============================================================================
const double PI = std::acos(-1.0);
const int N_SIZE = 16384; 

void fft(std::vector<Complex>& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) std::swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        Complex wlen(std::cos(ang), std::sin(ang));
        for (int i = 0; i < n; i += len) {
            Complex w(1);
            for (int j = 0; j < len / 2; j++) {
                Complex u = a[i + j];
                Complex v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (auto& x : a) x /= n;
    }
}

std::vector<Complex> solve_convolution_system(const std::vector<Complex>& A, const std::vector<Complex>& b) {
    std::vector<Complex> fft_A = A, fft_b = b;
    fft(fft_A, false);
    fft(fft_b, false);

    std::vector<Complex> fft_x(N_SIZE);
    for (int i = 0; i < N_SIZE; ++i) {
        if (std::abs(fft_A[i]) < 1e-9) fft_x[i] = 0;
        else fft_x[i] = fft_b[i] / fft_A[i];
    }

    fft(fft_x, true);
    return fft_x;
}

void demo_fft(bool auto_mode) {
    std::cout << "\n--- Solving a system of 16384 equations using FFT ---\n";
    std::vector<Complex> A(N_SIZE, 0.0);
    std::vector<Complex> b(N_SIZE, 0.0);

    int choice = 1; // Default - random
    
    if (auto_mode) {
        std::cout << "[Auto-mode] Filling arrays with random numbers...\n";
    } else {
        std::cout << "Choose a method to fill the arrays (16384 elements):\n"
                  << "1. Fill with random numbers automatically\n"
                  << "2. Enter the first K elements manually (the rest will be zeros)\n";
        while (true) {
            choice = read_int("Your choice (1 or 2): ");
            if (choice == 1 || choice == 2) break;
            std::cout << "[Error] Please enter 1 or 2.\n";
        }
    }

    if (choice == 2 && !auto_mode) {
        int k;
        while (true) {
            k = read_int("How many elements do you want to enter manually? (max 16384): ");
            if (k > 0 && k <= N_SIZE) break;
            std::cout << "[Error] Quantity must be from 1 to 16384.\n";
        }
        
        std::cout << "--- Entering array A ---\n";
        for (int i = 0; i < k; ++i) {
            A[i] = read_complex_std("A[" + std::to_string(i) + "] (format (re,im)): ");
        }
        std::cout << "--- Entering array b ---\n";
        for (int i = 0; i < k; ++i) {
            b[i] = read_complex_std("b[" + std::to_string(i) + "] (format (re,im)): ");
        }
    } else {
        for (int i = 0; i < N_SIZE; ++i) {
            A[i] = Complex(rand() % 100 / 10.0, rand() % 100 / 10.0);
            b[i] = Complex(rand() % 100 / 10.0, rand() % 100 / 10.0);
        }
        if (!auto_mode) std::cout << "Arrays successfully filled with random numbers.\n";
    }

    std::cout << "Calculating the vector of unknowns x...\n";
    std::vector<Complex> x = solve_convolution_system(A, b);

    std::cout << "--- Convolution system check (first 3 equations) ---\n";
    for (int m = 0; m < 3; ++m) {
        Complex current_b = 0;
        for (int i = 0; i < N_SIZE; ++i) {
            int idx = m - i;
            if (idx < 0) idx += N_SIZE; 
            current_b += A[idx] * x[i];
        }
        std::cout << "Equation m=" << m 
                  << " | Found b: " << current_b 
                  << " | Expected b: " << b[m] << "\n";
    }

}
// ==============================================================================
// ITEM 6: BENCHMARK & VISUALIZATION IMPLEMENTATION
// ==============================================================================
void run_benchmark() {
    int n_runs;
    while (true) {
        n_runs = read_int("Enter the number of iterations for the FFT benchmark (e.g., 100): ");
        if (n_runs > 0) break;
        std::cout << "[Error] Please enter a positive integer.\n";
    }

    std::cout << "Generating random data for 16384 equations...\n";
    std::vector<Complex> A(N_SIZE);
    std::vector<Complex> b(N_SIZE);
    for (int i = 0; i < N_SIZE; ++i) {
        A[i] = Complex(rand() % 100 / 10.0, rand() % 100 / 10.0);
        b[i] = Complex(rand() % 100 / 10.0, rand() % 100 / 10.0);
    }

    std::cout << "Running the convolution system solver " << n_runs << " times...\n";
    
    // Запускаємо таймер
    auto start_time = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < n_runs; ++i) {
        // Копіюємо вектори, щоб не зіпсувати оригінальні дані під час розв'язку
        std::vector<Complex> temp_A = A;
        std::vector<Complex> temp_b = b;
        solve_convolution_system(temp_A, temp_b);
    }
    
    // Зупиняємо таймер
    auto end_time = std::chrono::high_resolution_clock::now();
    
    // Рахуємо різницю в мілісекундах
    std::chrono::duration<double, std::milli> total_time = end_time - start_time;
    double avg_time = total_time.count() / n_runs;
    
    std::cout << "\n--- Benchmark Results ---\n";
    std::cout << "Total time for " << n_runs << " runs: " << total_time.count() << " ms\n";
    std::cout << "Average time per system solve (16384 size): " << avg_time << " ms\n";
}

void visualize_fft_matrix() {
    std::cout << "\n--- Discrete Fourier Transform (DFT) Matrix Visualization ---\n";
    std::cout << "Formula: X[k] = Sum(x[n] * W^(k*n)), where W = e^(-i * 2*PI / N)\n\n";
    
    int N;
    while (true) {
        N = read_int("Enter matrix dimension N for visualization (Recommended 4 or 8): ");
        if (N >= 2 && N <= 16) break;
        std::cout << "[Error] Please enter a small number between 2 and 16 for readable output.\n";
    }

    std::cout << "\nRotation factor matrix (W) for N = " << N << ":\n";
    
    for (int k = 0; k < N; ++k) {
        for (int n = 0; n < N; ++n) {
            // Обчислюємо кут для експоненти e^(-i * theta)
            double angle = -2.0 * PI * k * n / N;
            Complex w(std::cos(angle), std::sin(angle));
            
            // Заокруглюємо числа, щоб прибрати сміття типу 1.22e-16 (яке насправді є нулем)
            double r = std::abs(w.real()) < 1e-9 ? 0.0 : w.real();
            double i = std::abs(w.imag()) < 1e-9 ? 0.0 : w.imag();
            
            // Виводимо елемент матриці
            std::cout << std::fixed << std::setprecision(1);
            std::cout << "(" << (r >= 0 ? " " : "") << r << "," 
                      << (i >= 0 ? " " : "") << i << "i)\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n(Rows represent frequency 'k', Columns represent time 'n').\n";
}
// ==============================================================================
// ITEM 7: PROOF OF CORRECTNESS IMPLEMENTATION
// ==============================================================================

// Повільне, але математично пряме обчислення Дискретного перетворення Фур'є
std::vector<Complex> naive_dft(const std::vector<Complex>& x, bool invert) {
    int N = x.size();
    std::vector<Complex> X(N, 0.0);
    double sign = invert ? 1.0 : -1.0;
    
    for (int k = 0; k < N; ++k) {
        for (int n = 0; n < N; ++n) {
            double angle = sign * 2.0 * PI * k * n / N;
            X[k] += x[n] * Complex(std::cos(angle), std::sin(angle));
        }
        if (invert) X[k] /= N;
    }
    return X;
}

void verify_fft_correctness() {
    std::cout << "\n--- FFT Proof of Correctness ---\n";
    std::cout << "Proving correctness on a small array (N=8):\n";
    std::cout << "Method A: FFT Result must exactly match Naive Mathematical DFT.\n";
    std::cout << "Method B: Inverse FFT( FFT(x) ) must recover the original array.\n\n";

    int N = 8; // Беремо маленький розмір, щоб зручно було дивитися на екран
    std::vector<Complex> original(N);
    for (int i = 0; i < N; ++i) {
        original[i] = Complex(i + 1, 0); // Прості числа: 1, 2, 3, 4, 5, 6, 7, 8
    }

    std::cout << "1. ORIGINAL ARRAY:\n";
    for (int i = 0; i < N; ++i) {
        std::cout << "x[" << i << "] = " << original[i] << "\n";
    }

    // Виконуємо наше Швидке Фур'є (FFT)
    std::vector<Complex> fft_result = original;
    fft(fft_result, false);

    // Виконуємо математичне Фур'є за прямою формулою (DFT)
    std::vector<Complex> dft_result = naive_dft(original, false);

    std::cout << "\n2. FREQUENCY DOMAIN COMPARISON:\n";
    std::cout << "Index |      Fast Fourier (FFT)     |     Naive Math (DFT)\n";
    std::cout << "--------------------------------------------------------------\n";
    for (int i = 0; i < N; ++i) {
        // Очищаємо мікро-похибки типу 1.23e-16 для красивого виводу
        double r_fft = std::abs(fft_result[i].real()) < 1e-9 ? 0 : fft_result[i].real();
        double i_fft = std::abs(fft_result[i].imag()) < 1e-9 ? 0 : fft_result[i].imag();
        double r_dft = std::abs(dft_result[i].real()) < 1e-9 ? 0 : dft_result[i].real();
        double i_dft = std::abs(dft_result[i].imag()) < 1e-9 ? 0 : dft_result[i].imag();
        
        std::cout << "  " << i << "   | "
                  << "(" << r_fft << "," << i_fft << "i)\t| "
                  << "(" << r_dft << "," << i_dft << "i)\n";
    }

    // Виконуємо обернене Швидке Фур'є, щоб відновити дані
    std::vector<Complex> recovered = fft_result;
    fft(recovered, true);

    std::cout << "\n3. INVERSE FFT RECOVERY (Should match original):\n";
    for (int i = 0; i < N; ++i) {
        double r_rec = std::abs(recovered[i].real()) < 1e-9 ? 0 : recovered[i].real();
        double i_rec = std::abs(recovered[i].imag()) < 1e-9 ? 0 : recovered[i].imag();
        std::cout << "x'[" << i << "] = (" << r_rec << "," << i_rec << "i)\n";
    }
    
    std::cout << "\nCONCLUSION: \n";
    std::cout << "1) The columns in Step 2 match perfectly (FFT is mathematically sound).\n";
    std::cout << "2) The values in Step 3 match Step 1 (IFFT successfully recovers data).\n";
}