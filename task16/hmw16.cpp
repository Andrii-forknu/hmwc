#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <memory>
#include <limits>
#include <string>

using namespace std;

// Структура для зберігання результатів розв'язку
struct SolutionSet {
    bool isInfinite = false;
    vector<double> roots;
};

// =========================================================
// 1. Базовий клас: Лінійне рівняння (bx + c = 0)
// =========================================================
class LinearEquation {
protected:
    double b, c; // Використовуємо b та c для узгодженості з квадратним рівнянням

public:
    LinearEquation(double b = 0, double c = 0) : b(b), c(c) {}
    virtual ~LinearEquation() {}

    virtual void setCoeffs(double b, double c) {
        this->b = b;
        this->c = c;
    }

    virtual void read(istream& is) {
        is >> b >> c;
    }

    virtual void print(ostream& os) const {
        os << b << "x + " << c << " = 0";
    }

    virtual SolutionSet solve() const {
        SolutionSet res;
        if (b == 0) {
            if (c == 0) res.isInfinite = true; // 0 = 0
            // Якщо c != 0, розв'язків немає (0 = c)
        } else {
            res.roots.push_back(-c / b);
        }
        return res;
    }
};

// =========================================================
// 2. Похідний клас 1: Квадратне рівняння (ax^2 + bx + c = 0)
// =========================================================
class QuadraticEquation : public LinearEquation {
protected:
    double a;

public:
    QuadraticEquation(double a = 0, double b = 0, double c = 0) : LinearEquation(b, c), a(a) {}

    virtual void setCoeffs(double a, double b, double c) {
        this->a = a;
        LinearEquation::setCoeffs(b, c);
    }

    virtual void read(istream& is) override {
        is >> a;
        LinearEquation::read(is);
    }

    virtual void print(ostream& os) const override {
        os << a << "x^2 + " << b << "x + " << c << " = 0";
    }

    virtual SolutionSet solve() const override {
        // Якщо a == 0, рівняння вироджується в лінійне
        if (a == 0) return LinearEquation::solve(); 

        SolutionSet res;
        double D = b * b - 4 * a * c;

        if (D > 0) {
            res.roots.push_back((-b + sqrt(D)) / (2 * a));
            res.roots.push_back((-b - sqrt(D)) / (2 * a));
        } else if (D == 0) {
            res.roots.push_back(-b / (2 * a));
        }
        return res;
    }
};

// =========================================================
// 3. Похідний клас 2: Біквадратне рівняння (ax^4 + bx^2 + c = 0)
// =========================================================
class BiquadraticEquation : public QuadraticEquation {
public:
    BiquadraticEquation(double a = 0, double b = 0, double c = 0) : QuadraticEquation(a, b, c) {}

    virtual void print(ostream& os) const override {
        os << a << "x^4 + " << b << "x^2 + " << c << " = 0";
    }

    virtual SolutionSet solve() const override {
        if (a == 0) {
            // Вироджується в bx^2 + c = 0
            SolutionSet res;
            if (b == 0) {
                if (c == 0) res.isInfinite = true;
            } else {
                double t = -c / b;
                if (t > 0) {
                    res.roots.push_back(sqrt(t));
                    res.roots.push_back(-sqrt(t));
                } else if (t == 0) {
                    res.roots.push_back(0);
                }
            }
            return res;
        }

        // Розв'язуємо як квадратне відносно t = x^2
        SolutionSet t_res = QuadraticEquation::solve();
        SolutionSet final_res;

        if (t_res.isInfinite) {
            final_res.isInfinite = true;
            return final_res;
        }

        for (double t : t_res.roots) {
            if (t > 0) {
                final_res.roots.push_back(sqrt(t));
                final_res.roots.push_back(-sqrt(t));
            } else if (t == 0) {
                final_res.roots.push_back(0);
            }
        }
        return final_res;
    }
};

// =========================================================
// Головна функція
// =========================================================
int main() {
    setlocale(LC_ALL, "Ukrainian");

    // Вектор для зберігання поліморфних вказівників на рівняння
    vector<unique_ptr<LinearEquation>> equations;

    ifstream file("equations.txt");
    if (!file.is_open()) {
        cerr << "Помилка відкриття файлу equations.txt!" << endl;
        cerr << "Створіть файл equations.txt з форматом (L b c), (Q a b c) або (B a b c)." << endl;
        return 1;
    }

    char type;
    while (file >> type) {
        if (type == 'L') {
            auto eq = make_unique<LinearEquation>();
            eq->read(file);
            equations.push_back(move(eq));
        } else if (type == 'Q') {
            auto eq = make_unique<QuadraticEquation>();
            eq->read(file);
            equations.push_back(move(eq));
        } else if (type == 'B') {
            auto eq = make_unique<BiquadraticEquation>();
            eq->read(file);
            equations.push_back(move(eq));
        }
    }
    file.close();

    cout << "Зчитано рівнянь: " << equations.size() << "\n\n";

    // Змінні для статистики
    int noSolutionCount = 0;
    double minModulus = numeric_limits<double>::max();
    double sumOfSquares = 0.0;
    bool hasAnyRoots = false;

    // Аналіз масиву рівнянь
    for (size_t i = 0; i < equations.size(); ++i) {
        cout << "[" << i + 1 << "] Рівняння: ";
        equations[i]->print(cout);
        
        SolutionSet res = equations[i]->solve();

        if (res.isInfinite) {
            cout << " => Має нескінченну кількість розв'язків.\n";
            // Якщо коренів нескінченність, ми не враховуємо їх у суму квадратів чи мін. модуль
        } else if (res.roots.empty()) {
            cout << " => Немає дійсних розв'язків.\n";
            noSolutionCount++;
        } else {
            cout << " => Корені: ";
            for (double root : res.roots) {
                cout << root << " ";
                
                // Рахуємо суму квадратів
                sumOfSquares += (root * root);
                
                // Шукаємо найменший за модулем розв'язок
                if (abs(root) < minModulus) {
                    minModulus = abs(root);
                }
                hasAnyRoots = true;
            }
            cout << "\n";
        }
    }

    // Виведення результатів
    cout << "\n--- РЕЗУЛЬТАТИ АНАЛІЗУ ---\n";
    cout << "Кількість рівнянь, що не мають дійсних розв'язків: " << noSolutionCount << "\n";
    
    if (hasAnyRoots) {
        cout << "Найменший за модулем розв'язок: " << minModulus << "\n";
        cout << "Сума квадратів усіх дійсних розв'язків: " << sumOfSquares << "\n";
    } else {
        cout << "Найменший за модулем розв'язок: Не знайдено (немає скінченних коренів)\n";
        cout << "Сума квадратів усіх дійсних розв'язків: 0\n";
    }

    return 0;
}