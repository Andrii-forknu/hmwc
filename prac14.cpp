#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <stdexcept>
#include <iomanip>
#include <fstream>

class Rational {
private:
    long long nominator;
    long long denominator;

    // Private method to find the Greatest Common Divisor (GCD)
    long long gcd(long long a, long long b) const {
        a = std::abs(a);
        b = std::abs(b);
        while (b != 0) {
            long long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    // Private method to reduce the fraction
    void reduce() {
        if (denominator < 0) { // The denominator must always be positive
            nominator = -nominator;
            denominator = -denominator;
        }
        long long common_divisor = gcd(nominator, denominator);
        if (common_divisor > 1) {
            nominator /= common_divisor;
            denominator /= common_divisor;
        }
    }

public:
    // Default constructor (initializes with ones)
    Rational() : nominator(1), denominator(1) {}

    // Constructor with two parameters

    Rational(long long n, long long d) {
       
        if (d == 0) {
            throw std::invalid_argument("Denominator cannot be zero!");
        }
        nominator = n;
        denominator = d;
        reduce();
    }

    // Methods to initialize the nominator and denominator separately
    void setNominator(long long n) {
        nominator = n;
        reduce();
    }

    void setDenominator(long long d) {
        if (d == 0) {
            throw std::invalid_argument("Denominator cannot be zero!");
        }
        denominator = d;
        reduce();
    }

    long long getNominator() const { return nominator; }
    long long getDenominator() const { return denominator; }

    // Input and output methods (alternative to overloaded operators)
    void read() {
        long long n, d;
        char slash;
        std::cin >> n >> slash >> d;
        if (d == 0) throw std::invalid_argument("Denominator cannot be zero!");
        nominator = n;
        denominator = d;
        reduce();
    }

    void print() const {
        std::cout << nominator << "/" << denominator;
    }

    // Addition method
    Rational add(const Rational& other) const {
        long long new_nom = nominator * other.denominator + other.nominator * denominator;
        long long new_den = denominator * other.denominator;
        return Rational(new_nom, new_den);
    }

    // Multiplication method
    Rational multiply(const Rational& other) const {
        return Rational(nominator * other.nominator, denominator * other.denominator);
    }

    // Overloading basic arithmetic operators
    Rational operator+(const Rational& other) const { return add(other); }
    Rational operator-(const Rational& other) const {
        long long new_nom = nominator * other.denominator - other.nominator * denominator;
        long long new_den = denominator * other.denominator;
        return Rational(new_nom, new_den);
    }
    Rational operator*(const Rational& other) const { return multiply(other); }
    Rational operator/(const Rational& other) const {
        if (other.nominator == 0) throw std::invalid_argument("Division by zero!");
        return Rational(nominator * other.denominator, denominator * other.nominator);
    }

    // Overloading comparison operators
    bool operator==(const Rational& other) const {
        return nominator == other.nominator && denominator == other.denominator;
    }
    bool operator<(const Rational& other) const {
        return nominator * other.denominator < other.nominator * denominator;
    }
    bool operator>(const Rational& other) const { return other < *this; }
    bool operator<=(const Rational& other) const { return !(*this > other); }
    bool operator>=(const Rational& other) const { return !(*this < other); }
    bool operator!=(const Rational& other) const { return !(*this == other); }

    // Overloading input/output streams
    friend std::ostream& operator<<(std::ostream& out, const Rational& r) {
        out << r.nominator << "/" << r.denominator;
        return out;
    }
    friend std::istream& operator>>(std::istream& in, Rational& r) {
        r.read();
        return in;
    }

    // Conversion to double for precision calculations
    double toDouble() const {
        return static_cast<double>(nominator) / denominator;
    }
};

int main() {
    // --- TASK 1: Find the smallest rational number in the array ---
    std::cout << "--- Task 1: Finding the minimum ---" << std::endl;
    Rational* arr;
    int k;
    std::cout << "Enter the number of rational numbers: ";
    std::cin >> k;
    arr = new Rational[k];
    for (int i = 0; i < k; ++i) {
        try{
            std::cout << "Enter rational number " << (i + 1) << " (format: a/b): ";
            std::cin >> arr[i];
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid input: " << e.what() << ". Please try again." << std::endl;
            --i; // Decrement i to retry the input for this index
        }
    }

    Rational min_val = arr[0];
    for (size_t i = 1; i < k; ++i) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    std::cout << "Array elements: ";
    for (int i = 0; i < k; ++i) {
        std::cout << arr[i] << "  ";
    }
    std::cout << "\nSmallest rational number: " << min_val << std::endl;
    delete[] arr;

    // --- TASK 2: Calculate the sum of the series ---
    std::cout << "\n--- Task 2: Sum of the series ---" << std::endl;
    Rational sum(0, 1); // Initial sum is 0/1
    double precision = 0.01;
    long long n = 1;
    
    while (true) {
        // Calculate the sign (-1)^(n+1)
        long long sign = (n % 2 == 1) ? 1 : -1;
        Rational term(sign, n * n);
        
        sum = sum + term;

        // Check the stopping condition: if the absolute value of the term is <= 0.01
        if (std::abs(term.toDouble()) <= precision) {
            break;
        }
        n++;
    }

    double calc_value = sum.toDouble();
    // Pi constant from the cmath library (M_PI)
    double pi_value = M_PI; 
    double exact_value = (pi_value * pi_value) / 12.0;

    std::cout << "Sum of the series as a fraction (at n = " << n << "): " << sum << std::endl;
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Sum of the series as a decimal:    " << calc_value << std::endl;
    std::cout << "Analytical value (pi^2 / 12):      " << exact_value << std::endl;
    std::cout << "Difference:                        " << std::abs(exact_value - calc_value) << std::endl;
    std::cout << "\nConclusion: The series indeed converges to pi^2/12. The values match within the given precision." << std::endl;

    return 0;
}