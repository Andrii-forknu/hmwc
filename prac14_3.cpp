#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Polynomial {
private:
    double* coefficients;
    int size; // Number of elements (N)

public:
    // 1. Constructor with size N (initializes with zeros)
    Polynomial(int n) : size(n) {
        coefficients = new double[size]();
    }

    // 2. Constructor with size N and initial values
    Polynomial(int n, const double* initialValues) : size(n) {
        coefficients = new double[size];
        for (int i = 0; i < size; ++i) {
            coefficients[i] = initialValues[i];
        }
    }

    // 3. Copy Constructor (Deep Copy)
    Polynomial(const Polynomial& other) : size(other.size) {
        coefficients = new double[size];
        for (int i = 0; i < size; ++i) {
            coefficients[i] = other.coefficients[i];
        }
    }

    // 4. Destructor
    ~Polynomial() {
        delete[] coefficients;
    }

    // 5. Assignment Operator (Essential to overload!)
    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            delete[] coefficients;
            size = other.size;
            coefficients = new double[size];
            for (int i = 0; i < size; ++i) {
                coefficients[i] = other.coefficients[i];
            }
        }
        return *this;
    }

    // Method to set a specific coefficient by index
    void setCoefficient(int index, double value) {
        if (index >= 0 && index < size) {
            coefficients[index] = value;
        } else {
            std::cerr << "Index out of bounds!" << std::endl;
        }
    }

    // Method to output the polynomial to console
    void print() const {
        for (int i = size - 1; i >= 0; --i) {
            std::cout << coefficients[i] << (i > 0 ? "x^" : "") << (i > 0 ? std::to_string(i) : "") << (i > 0 ? " + " : "");
        }
        std::cout << std::endl;
    }

    // Friendly functions for Binary File I/O
    friend void saveToBinary(const std::string& filename, const Polynomial& poly);
    friend void loadFromBinary(const std::string& filename, Polynomial& poly);
};

// --- Binary File Functions ---

void saveToBinary(const std::string& filename, const Polynomial& poly) {
    std::ofstream outFile(filename, std::ios::binary);
    if (outFile.is_open()) {
        // Write size first
        outFile.write(reinterpret_cast<const char*>(&poly.size), sizeof(int));
        // Write array data
        outFile.write(reinterpret_cast<const char*>(poly.coefficients), sizeof(double) * poly.size);
        outFile.close();
        std::cout << "Polynomial saved to " << filename << std::endl;
    }
}

void loadFromBinary(const std::string& filename, Polynomial& poly) {
    std::ifstream inFile(filename, std::ios::binary);
    if (inFile.is_open()) {
        int newSize;
        inFile.read(reinterpret_cast<char*>(&newSize), sizeof(int));

        // Reallocate memory if sizes differ
        if (newSize != poly.size) {
            delete[] poly.coefficients;
            poly.size = newSize;
            poly.coefficients = new double[poly.size];
        }

        inFile.read(reinterpret_cast<char*>(poly.coefficients), sizeof(double) * poly.size);
        inFile.close();
        std::cout << "Polynomial loaded from " << filename << std::endl;
    }
}

int main() {
    // Example usage
    double initial[] = {1.5, 2.0, 3.5}; // 1.5 + 2x + 3.5x^2
    Polynomial p1(3, initial);
    
    std::cout << "Original P1: ";
    p1.print();

    // Test Copy Constructor
    Polynomial p2 = p1;
    p2.setCoefficient(0, 9.9);
    
    std::cout << "Modified P2 (Copy): ";
    p2.print();

    // Binary File operations
    saveToBinary("poly.dat", p1);
    
    Polynomial p3(1); // Small poly
    loadFromBinary("poly.dat", p3);
    std::cout << "Loaded P3: ";
    p3.print();

    return 0;
}