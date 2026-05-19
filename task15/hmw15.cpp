#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>

// Визначаємо константу PI для переведення радіанів у градуси і навпаки
const double PI = std::acos(-1.0);

class Triangle {
private:
    double sideA;       // Ліва бічна сторона
    double sideB;       // Права бічна сторона
    double topAngleRad; // Верхній кут у радіанах

public:
    // Конструктор класу (кут передається у градусах для зручності)
    Triangle(double a, double b, double angleDeg) {
        if (a <= 0 || b <= 0) {
            throw std::invalid_argument("Довжини сторін повинні бути більшими за нуль.");
        }
        if (angleDeg <= 0 || angleDeg >= 180) {
            throw std::invalid_argument("Кут повинен бути в межах від 0 до 180 градусів.");
        }
        
        sideA = a;
        sideB = b;
        // Переводимо градуси в радіани для математичних функцій C++
        topAngleRad = angleDeg * PI / 180.0; 
    }

    // --- Методи для отримання сторін ---

    double getSideA() const { return sideA; }
    
    double getSideB() const { return sideB; }
    
    // Знаходимо основу за теоремою косинусів: c^2 = a^2 + b^2 - 2ab * cos(gamma)
    double getBase() const {
        return std::sqrt(sideA * sideA + sideB * sideB - 2 * sideA * sideB * std::cos(topAngleRad));
    }

    // --- Методи для отримання кутів (у градусах) ---

    double getTopAngle() const {
        return topAngleRad * 180.0 / PI;
    }

    // Знаходимо кут при основі (навпроти сторони A) за теоремою косинусів
    double getBaseAngle1() const {
        double base = getBase();
        double cosVal = (sideB * sideB + base * base - sideA * sideA) / (2 * sideB * base);
        // Захист від похибок обчислення з плаваючою комою (щоб значення не вийшло за [-1, 1])
        cosVal = std::max(-1.0, std::min(1.0, cosVal)); 
        return std::acos(cosVal) * 180.0 / PI;
    }

    // Знаходимо кут при основі (навпроти сторони B) за теоремою косинусів
    double getBaseAngle2() const {
        double base = getBase();
        double cosVal = (sideA * sideA + base * base - sideB * sideB) / (2 * sideA * base);
        cosVal = std::max(-1.0, std::min(1.0, cosVal));
        return std::acos(cosVal) * 180.0 / PI;
    }

    // --- Периметр та Площа ---

    double getPerimeter() const {
        return sideA + sideB + getBase();
    }

    // Площа за формулою S = 0.5 * a * b * sin(gamma)
    double getArea() const {
        return 0.5 * sideA * sideB * std::sin(topAngleRad);
    }
};

// Демонстрація роботи класу
int main() {
    // Для коректного відображення української мови у консолі
    setlocale(LC_ALL, "uk_UA.UTF-8");

    try {
        // Створюємо трикутник: бічні сторони 5 і 7, верхній кут 60 градусів
        Triangle myTriangle(5.0, 7.0, 60.0);

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "--- Параметри трикутника ---\n";
        
        std::cout << "\n1. Сторони:\n";
        std::cout << "- Бічна сторона 1: " << myTriangle.getSideA() << "\n";
        std::cout << "- Бічна сторона 2: " << myTriangle.getSideB() << "\n";
        std::cout << "- Основа: " << myTriangle.getBase() << "\n";

        std::cout << "\n2. Кути:\n";
        std::cout << "- Верхній кут: " << myTriangle.getTopAngle() << "°\n";
        std::cout << "- Кут при основі 1: " << myTriangle.getBaseAngle1() << "°\n";
        std::cout << "- Кут при основі 2: " << myTriangle.getBaseAngle2() << "°\n";
        
        // Перевірка (сума кутів має бути 180)
        double sumAngles = myTriangle.getTopAngle() + myTriangle.getBaseAngle1() + myTriangle.getBaseAngle2();
        std::cout << "  (Сума кутів: " << sumAngles << "°)\n";

        std::cout << "\n3. Властивості:\n";
        std::cout << "- Периметр: " << myTriangle.getPerimeter() << "\n";
        std::cout << "- Площа: " << myTriangle.getArea() << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Помилка: " << e.what() << "\n";
    }

    return 0;
}