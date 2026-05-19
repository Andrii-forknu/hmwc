#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

// ==============================================================================
// ЗАВДАННЯ 1: Клас Раціональне число (Rational)
// ==============================================================================
class Rational {
private:
    long long nominator;
    long long denominator; // Використовуємо long long для уникнення переповнення при сумуванні ряду

    // Приватний метод для скорочення дробу
    void reduce() {
        if (denominator == 0) return; // Захист
        long long gcd_val = std::gcd(abs(nominator), denominator);
        nominator /= gcd_val;
        denominator /= gcd_val;
    }

public:
    // Конструктор за замовчуванням (одиницями)
    Rational() : nominator(1), denominator(1) {}

    // Конструктор з двома параметрами
    Rational(long long n, long long d) {
        init(n, d);
    }

    // Методи ініціалізації окремо чисельника та знаменника
    void setNominator(long long n) {
        nominator = n;
        reduce();
    }

    void setDenominator(long long d) {
        if (d == 0) {
            throw invalid_argument("Знаменник не може дорівнювати нулю!");
        }
        // Забезпечуємо, щоб знаменник завжди був натуральним числом (>0)
        if (d < 0) {
            nominator = -nominator;
            denominator = -d;
        } else {
            denominator = d;
        }
        reduce();
    }

    // Загальний метод ініціалізації
    void init(long long n, long long d) {
        nominator = n;
        setDenominator(d); // тут є перевірка на нуль і скорочення
    }

    // Методи додавання та множення
    Rational add(const Rational& other) const {
        return Rational(nominator * other.denominator + other.nominator * denominator, 
                        denominator * other.denominator);
    }

    Rational multiply(const Rational& other) const {
        return Rational(nominator * other.nominator, denominator * other.denominator);
    }

    // Перевантаження арифметичних операторів
    Rational operator+(const Rational& other) const { return add(other); }
    Rational operator-(const Rational& other) const {
        return Rational(nominator * other.denominator - other.nominator * denominator, denominator * other.denominator);
    }
    Rational operator*(const Rational& other) const { return multiply(other); }
    Rational operator/(const Rational& other) const {
        return Rational(nominator * other.denominator, denominator * other.nominator);
    }

    // Перевантаження операторів порівняння
    bool operator<(const Rational& other) const {
        return nominator * other.denominator < other.nominator * denominator;
    }
    bool operator>(const Rational& other) const { return other < *this; }
    bool operator==(const Rational& other) const {
        return nominator == other.nominator && denominator == other.denominator;
    }

    // Переведення в дійсне число для перевірки збіжності
    double toDouble() const {
        return static_cast<double>(nominator) / denominator;
    }

    // Введення та виведення
    friend istream& operator>>(istream& is, Rational& r) {
        long long n, d;
        char slash;
        if (is >> n >> slash >> d && slash == '/') {
            r.init(n, d);
        } else {
            is.setstate(ios::failbit);
        }
        return is;
    }

    friend ostream& operator<<(ostream& os, const Rational& r) {
        os << r.nominator;
        if (r.denominator != 1 && r.nominator != 0) {
            os << "/" << r.denominator;
        }
        return os;
    }
};

void runTask1() {
    cout << "--- ЗАВДАННЯ 1: Раціональні числа ---\n";
    
    // 1. Пошук найменшого числа в масиві
    vector<Rational> arr = {Rational(3, 4), Rational(1, 3), Rational(-5, 2), Rational(7, 8)};
    Rational min_val = arr[0];
    for (const auto& r : arr) {
        if (r < min_val) min_val = r;
    }
    cout << "Найменше число в масиві: " << min_val << endl;

    // 2. Сума ряду: 1 - 1/2^2 + 1/3^2 - 1/4^2 + ... з точністю 0.01
    Rational sum(0, 1);
    long long n = 1;
    double precision = 0.01;
    double current_term_val;

    do {
        long long denom = n * n;
        Rational term(1, denom);
        if (n % 2 == 0) {
            term.setNominator(-1); // Парні члени від'ємні
        }
        
        sum = sum + term;
        current_term_val = abs(term.toDouble());
        n++;
    } while (current_term_val >= precision);

    double pi_squared_over_12 = (M_PI * M_PI) / 12.0;
    
    cout << "Сума ряду (раціональним дробом): " << sum << endl;
    cout << "Сума ряду (дійсним числом): " << sum.toDouble() << endl;
    cout << "Справжнє значення pi^2 / 12: " << pi_squared_over_12 << endl;
    cout << "Різниця: " << abs(sum.toDouble() - pi_squared_over_12) << "\n\n";
}


// ==============================================================================
// ЗАВДАННЯ 2: Клас Точка (Point)
// ==============================================================================
class Point {
private:
    double x, y;
    static int instances_count; // Статичний лічильник

public:
    Point(double x = 0, double y = 0) : x(x), y(y) {
        instances_count++;
    }
    
    Point(const Point& other) : x(other.x), y(other.y) {
        instances_count++;
    }

    ~Point() {
        instances_count--;
    }

    static int counter() {
        return instances_count;
    }

    double distanceTo(const Point& other) const {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }

    friend istream& operator>>(istream& is, Point& p) {
        is >> p.x >> p.y;
        return is;
    }
};

// Ініціалізація статичного члена
int Point::instances_count = 0;

void runTask2() {
    cout << "--- ЗАВДАННЯ 2: Багатокутник (Точки) ---\n";
    vector<Point> polygon;
    string answer;

    while (true) {
        cout << "Ввести вершину? (Так/Ні): ";
        cin >> answer;
        
        // Переводимо у нижній регістр для зручності перевірки
        if (answer == "Ні" || answer == "ні" || answer == "No" || answer == "no") {
            break;
        }

        cout << "Введіть координати X та Y через пробіл: ";
        Point p;
        cin >> p;
        polygon.push_back(p);
    }

    cout << "\nКількість існуючих екземплярів точок у пам'яті (counter): " << Point::counter() << endl;
    
    if (polygon.size() < 3) {
        cout << "Недостатньо вершин для багатокутника (мінімум 3)!\n\n";
        return;
    }

    // Обчислення периметра
    double perimeter = 0;
    for (size_t i = 0; i < polygon.size(); ++i) {
        size_t next_i = (i + 1) % polygon.size(); // Замикаємо багатокутник
        perimeter += polygon[i].distanceTo(polygon[next_i]);
    }

    cout << "Периметр багатокутника: " << perimeter << "\n\n";
}


// ==============================================================================
// ЗАВДАННЯ 3: Клас Поліном (Polynomial)
// ==============================================================================
class Polynomial {
private:
    int N;
    double* coeffs;

public:
    // Конструктор
    Polynomial(int size) : N(size) {
        coeffs = new double[N]{0}; // Виділення пам'яті та ініціалізація нулями
    }

    // Конструктор копіювання
    Polynomial(const Polynomial& other) : N(other.N) {
        coeffs = new double[N];
        for (int i = 0; i < N; ++i) {
            coeffs[i] = other.coeffs[i];
        }
    }

    // Деструктор
    ~Polynomial() {
        delete[] coeffs;
    }

    // ПЕРЕВАНТАЖЕННЯ ОПЕРАТОРА ПРИСВОЮВАННЯ (Відповідь на запитання з умови)
    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) { // Захист від самоприсвоювання
            delete[] coeffs;
            N = other.N;
            coeffs = new double[N];
            for (int i = 0; i < N; ++i) {
                coeffs[i] = other.coeffs[i];
            }
        }
        return *this;
    }

    // Метод заповнення масиву
    void fill(const double* arr, int size) {
        int limit = min(N, size);
        for (int i = 0; i < limit; ++i) {
            coeffs[i] = arr[i];
        }
    }

    // Задання конкретного коефіцієнта
    void setCoeff(int index, double value) {
        if (index >= 0 && index < N) {
            coeffs[index] = value;
        }
    }

    // Виведення поліному
    void print() const {
        for (int i = N - 1; i >= 0; --i) {
            cout << coeffs[i];
            if (i > 0) cout << "x^" << i << " + ";
        }
        cout << endl;
    }

    // Дружні функції для бінарного файлу
    friend void writeToBinaryFile(const Polynomial& p, const string& filename);
    friend Polynomial readFromBinaryFile(const string& filename);
};

// Реалізація дружніх функцій
void writeToBinaryFile(const Polynomial& p, const string& filename) {
    ofstream ofs(filename, ios::binary);
    if (ofs) {
        ofs.write(reinterpret_cast<const char*>(&p.N), sizeof(int)); // Записуємо розмір
        ofs.write(reinterpret_cast<const char*>(p.coeffs), p.N * sizeof(double)); // Записуємо масив
        ofs.close();
        cout << "Поліном записано у файл: " << filename << endl;
    } else {
        cerr << "Помилка відкриття файлу для запису!" << endl;
    }
}

Polynomial readFromBinaryFile(const string& filename) {
    ifstream ifs(filename, ios::binary);
    if (ifs) {
        int size = 0;
        ifs.read(reinterpret_cast<char*>(&size), sizeof(int)); // Читаємо розмір
        
        Polynomial p(size);
        ifs.read(reinterpret_cast<char*>(p.coeffs), size * sizeof(double)); // Читаємо масив
        ifs.close();
        return p;
    } else {
        cerr << "Помилка відкриття файлу для читання!" << endl;
        return Polynomial(0);
    }
}

void runTask3() {
    cout << "--- ЗАВДАННЯ 3: Поліном ---\n";
    Polynomial p1(3); // Поліном 2-го степеня (3 коефіцієнти: x^0, x^1, x^2)
    p1.setCoeff(0, 5.5);
    p1.setCoeff(1, -2.0);
    p1.setCoeff(2, 4.1);

    cout << "Створено поліном p1: ";
    p1.print();

    string filename = "polynomial.bin";
    
    // Запис у бінарний файл
    writeToBinaryFile(p1, filename);

    // Читання з бінарного файлу у новий об'єкт
    Polynomial p2 = readFromBinaryFile(filename);
    cout << "Зчитано поліном p2 з файлу: ";
    p2.print();
}

// ==============================================================================
// ГОЛОВНА ФУНКЦІЯ
// ==============================================================================
int main() {
    // Встановлення української локалі для правильного відображення в консолі (Windows)
    setlocale(LC_ALL, "Ukrainian");

    runTask1();
    runTask2();
    runTask3();

    return 0;
}