#include <iostream>
#include <cmath>
#include <cassert>
#include <stdexcept>
#include <new>
#include <limits>
#include <vector>

using namespace std;

// ==============================================================================
// 1. Власний клас для комплексного типу
// ==============================================================================
class CustomComplex {
private:
    double re;
    double im;

public:
    // Конструктори
    CustomComplex(double r = 0.0, double i = 0.0) : re(r), im(i) {}

    // Геттери
    double real() const { return re; }
    double imag() const { return im; }

    // Метод обчислення модуля |z| = sqrt(re^2 + im^2)
    double abs() const {
        return std::sqrt(re * re + im * im);
    }

    // --- Арифметичні операції ---
    CustomComplex operator+(const CustomComplex& other) const {
        return CustomComplex(re + other.re, im + other.im);
    }

    CustomComplex operator-(const CustomComplex& other) const {
        return CustomComplex(re - other.re, im - other.im);
    }

    CustomComplex operator*(const CustomComplex& other) const {
        return CustomComplex(re * other.re - im * other.im, 
                             re * other.im + im * other.re);
    }

    CustomComplex operator/(const CustomComplex& other) const {
        double denominator = other.re * other.re + other.im * other.im;
        if (denominator == 0.0) {
            throw std::invalid_argument("Помилка: Ділення на нульове комплексне число!");
        }
        return CustomComplex((re * other.re + im * other.im) / denominator, 
                             (im * other.re - re * other.im) / denominator);
    }

    // Додатковий оператор ділення на дійсне число (для формули Тейлора)
    CustomComplex operator/(double val) const {
        if (val == 0.0) {
            throw std::invalid_argument("Помилка: Ділення на нуль!");
        }
        return CustomComplex(re / val, im / val);
    }
    
    // Множення на дійсне число (для зміни знаку)
    CustomComplex operator*(double val) const {
        return CustomComplex(re * val, im * val);
    }

    // --- Методи введення/виведення ---
    friend ostream& operator<<(ostream& os, const CustomComplex& c) {
        os << c.re << (c.im >= 0 ? "+" : "") << c.im << "i";
        return os;
    }

    friend istream& operator>>(istream& is, CustomComplex& c) {
        // Очікуємо введення двох дійсних чисел через пробіл (дійсна та уявна частини)
        if (!(is >> c.re >> c.im)) {
            // Якщо введено літери замість чисел, кидаємо виключення
            throw std::runtime_error("Некоректне введення комплексного числа! Очікувались дійсні числа.");
        }
        return is;
    }
};

// ==============================================================================
// 2. Функція обчислення arctg(z) через ряд Тейлора
// ==============================================================================
CustomComplex calculateArctan(CustomComplex z, double epsilon) {
    // 1. Твердження про стан програми (Assertion)
    // Працює в Debug-режимі. Якщо умова хибна, програма аварійно зупиниться для розробника.
    assert(z.abs() < 1.0 && "Порушення математичної умови: |z| має бути менше 1");

    // 2. Обробка виключення для користувача (щоб вивести змістовне повідомлення)
    if (z.abs() >= 1.0) {
        throw std::domain_error(
            "Модуль введеного комплексного числа дорівнює або більший за 1 (|z| >= 1). "
            "Ряд Тейлора для arctg(z) при таких значеннях розбігається і обчислення неможливе!"
        );
    }
    if (epsilon < 0) {
        throw std::invalid_argument("Точність epsilon має бути більшою або рівною 0.");
    }

    CustomComplex sum(0, 0);       // Сума ряду
    CustomComplex current_z = z;   // z^(2n+1)
    CustomComplex z_squared = z * z; // z^2 для переходу до наступного степеня
    
    int n = 0;
    double sign = 1.0; // (-1)^n

    while (true) {
        // Обчислюємо поточний доданок: (-1)^n * z^(2n+1) / (2n+1)
        CustomComplex term = (current_z / (2.0 * n + 1.0)) * sign;

        // Перевіряємо умову зупинки (|term| < epsilon)
        if (term.abs() < epsilon) {
            break;
        }

        sum = sum + term;

        // Підготовка до наступної ітерації
        current_z = current_z * z_squared; // z^1 -> z^3 -> z^5 ...
        sign = -sign;                      // 1 -> -1 -> 1 ...
        n++;
    }

    return sum;
}

// ==============================================================================
// Головна функція з обробкою ВСІХ можливих виключень
// ==============================================================================
int main() {
    setlocale(LC_ALL, "Ukrainian");
    cout << "--- Обчислення arctg(z) у комплексній точці ---\n\n";

    try {
        // 1. Демонстрація перехоплення некоректного введення
        CustomComplex z;
        cout << "Введіть комплексну точку z (дійсна та уявна частина через пробіл, напр. '0.5 0.3'): ";
        cin >> z;

        double epsilon;
        cout << "Введіть точність epsilon (напр. '0.0001'): ";
        if (!(cin >> epsilon)) {
            throw std::runtime_error("Некоректне введення epsilon! Очікувалось дійсне число.");
        }

        // 2. Демонстрація обчислення (може викинути domain_error, якщо |z| >= 1)
        CustomComplex result = calculateArctan(z, epsilon);
        cout << "\nРезультат: arctg(" << z << ") = " << result << "\n\n";

        // 3. Демонстрація перехоплення помилки виділення пам'яті (std::bad_alloc)
        cout << "--- Перевірка системи виділення пам'яті ---\n";
        long long arraySize;
        cout << "Скільки елементів масиву виділити для збереження історії обчислень? "
             << "(Введіть дуже велике число, напр. 10000000000000, щоб викликати помилку): ";
        if (!(cin >> arraySize)) {
            throw std::runtime_error("Некоректне введення розміру масиву.");
        }

        // Намагаємось виділити масив вказаного розміру
        cout << "Намагаюсь виділити пам'ять під масив...\n";
        int* historyArray = new int[arraySize]; 
        
        cout << "Пам'ять успішно виділено!\n";
        delete[] historyArray; // Звільняємо, якщо якимось чином вдалося

    } 
    // Перехоплення математичної помилки (некоректне z)
    catch (const std::domain_error& e) {
        cerr << "\n[МАТЕМАТИЧНА ПОМИЛКА]: " << e.what() << "\n";
        cerr << "Підказка: Спробуйте ввести числа, що ближче до нуля, наприклад '0.2 0.4'\n";
    } 
    // Перехоплення помилки виділення пам'яті
    catch (const std::bad_alloc& e) {
        cerr << "\n[ПОМИЛКА ПАМ'ЯТІ (bad_alloc)]: Неможливо виділити такий великий обсяг оперативної пам'яті!\n";
        cerr << "Системне повідомлення: " << e.what() << "\n";
    } 
    // Перехоплення невірного аргументу (наприклад, ділення на нуль або від'ємний epsilon)
    catch (const std::invalid_argument& e) {
        cerr << "\n[ПОМИЛКА АРГУМЕНТУ]: " << e.what() << "\n";
    } 
    // Перехоплення некоректного введення користувачем з клавіатури
    catch (const std::runtime_error& e) {
        cerr << "\n[ПОМИЛКА ВВЕДЕННЯ]: " << e.what() << "\n";
    } 
    // Глобальний обробник для будь-яких інших непередбачених помилок
    catch (const std::exception& e) {
        cerr << "\n[НЕВІДОМА ПОМИЛКА]: " << e.what() << "\n";
    }

    return 0;
}