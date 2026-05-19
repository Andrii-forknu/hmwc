#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <numeric>
#include <memory>

using namespace std;

// ==============================================================================
// ЗАВДАННЯ 1: Клас Раціональний дріб (Rational) з виключеннями
// ==============================================================================
class Rational {
private:
    int nominator;
    int denominator;

    void reduce() {
        if (denominator == 0) return;
        int gcd_val = std::gcd(abs(nominator), abs(denominator));
        nominator /= gcd_val;
        denominator /= gcd_val;
        if (denominator < 0) { // Завжди тримаємо знак у чисельнику
            nominator = -nominator;
            denominator = -denominator;
        }
    }

public:
    // Конструктор з генерацією виключення
    Rational(int n = 0, int d = 1) {
        if (d == 0) {
            throw invalid_argument("Помилка ініціалізації: Знаменник не може дорівнювати нулю!");
        }
        nominator = n;
        denominator = d;
        reduce();
    }

    // Сеттери з генерацією виключення
    void setNominator(int n) { 
        nominator = n; 
        reduce(); 
    }
    
    void setDenominator(int d) {
        if (d == 0) {
            throw invalid_argument("Помилка сеттера: Знаменник не може дорівнювати нулю!");
        }
        denominator = d;
        reduce();
    }

    // 1. Бінарний оператор віднімання (a - b)
    Rational operator-(const Rational& other) const {
        return Rational(nominator * other.denominator - other.nominator * denominator, 
                        denominator * other.denominator);
    }

    // 2. Унарний оператор віднімання (-a)
    Rational operator-() const {
        return Rational(-nominator, denominator);
    }

    // Оператор ділення (a / b)
    Rational operator/(const Rational& other) const {
        if (other.nominator == 0) {
            throw invalid_argument("Помилка ділення: Ділення на нуль (чисельник дільника = 0)!");
        }
        return Rational(nominator * other.denominator, denominator * other.nominator);
    }

    // Перевантаження введення з обробкою нуля
    friend istream& operator>>(istream& is, Rational& r) {
        int n, d;
        char slash;
        if (is >> n >> slash >> d && slash == '/') {
            if (d == 0) {
                throw invalid_argument("Помилка вводу: Знаменник не може дорівнювати нулю!");
            }
            r.nominator = n;
            r.denominator = d;
            r.reduce();
        } else {
            is.setstate(ios::failbit);
        }
        return is;
    }

    // Перевантаження виведення
    friend ostream& operator<<(ostream& os, const Rational& r) {
        os << r.nominator;
        if (r.denominator != 1 && r.nominator != 0) {
            os << "/" << r.denominator;
        }
        return os;
    }

    // Дружня функція запису у файл із генерацією виключення
    friend void writeToFile(const Rational& r, const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Помилка файлу: Неможливо відкрити файл '" + filename + "' для запису!");
        }
        file << r << endl;
        file.close();
    }
};

void runTask1() {
    cout << "--- ЗАВДАННЯ 1: Раціональний дріб та виключення ---\n";
    try {
        cout << "Створення дробу r1(3, 4)..." << endl;
        Rational r1(3, 4);
        cout << "r1 = " << r1 << endl;

        cout << "Перевірка унарного віднімання: -r1 = " << -r1 << endl;

        Rational r2;
        cout << "Введіть дріб r2 у форматі a/b: ";
        cin >> r2;
        cout << "r2 = " << r2 << endl;

        cout << "r1 - r2 = " << r1 - r2 << endl;
        cout << "r1 / r2 = " << r1 / r2 << endl;

        cout << "Спроба запису r1 у файл (test_frac.txt)..." << endl;
        writeToFile(r1, "test_frac.txt");
        cout << "Запис успішний!" << endl;

        // Штучно викликаємо виключення: заборонений шлях
        // writeToFile(r1, "X:/invalid_path/test.txt");

        cout << "Спроба змінити знаменник r1 на 0..." << endl;
        r1.setDenominator(0); // Це викине виняток

    } catch (const invalid_argument& e) {
        cerr << "\n[ПЕРЕХОПЛЕНО invalid_argument]: " << e.what() << endl;
    } catch (const runtime_error& e) {
        cerr << "\n[ПЕРЕХОПЛЕНО runtime_error]: " << e.what() << endl;
    }
    
    // Очищуємо потік після можливої помилки вводу
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Завершення Завдання 1.\n\n";
}

// ==============================================================================
// ЗАВДАННЯ 2: Ієрархія класів Людина, Студент, Викладач, Аспірант
// ==============================================================================

// Базовий клас (Віртуальне наслідування вирішить "Проблему ромба")
class Person {
protected:
    string pib;
    string gender;
    int age;

public:
    Person(string p = "", string g = "", int a = 0) : pib(p), gender(g), age(a) {}
    virtual ~Person() {}

    virtual void input() {
        cout << "Введіть ПІБ: ";
        getline(cin, pib);
        cout << "Введіть стать: ";
        getline(cin, gender);
        cout << "Введіть вік: ";
        while (!(cin >> age) || age < 0) {
            cout << "Помилка! Введіть коректний вік: ";
            cin.clear(); cin.ignore(10000, '\n');
        }
        cin.ignore(10000, '\n');
    }

    virtual void print() const {
        cout << "ПІБ: " << pib << " | Стать: " << gender << " | Вік: " << age;
    }

    // Віртуальний метод для безпечного отримання ВУЗу без створення нових членів
    virtual string getVUZ() const {
        return "Не застосовується (не прив'язаний до ВУЗу)";
    }
};

// Клас Студент (віртуальне наслідування від Person)
class Student : virtual public Person {
protected:
    int course;
    string group;
    string vuz; // ВУЗ студента

public:
    Student() {}
    
    void input() override {
        Person::input();
        cout << "Введіть курс: ";
        while (!(cin >> course) || course < 1) {
            cout << "Помилка! Введіть коректний курс: ";
            cin.clear(); cin.ignore(10000, '\n');
        }
        cin.ignore();
        cout << "Введіть групу: "; getline(cin, group);
        cout << "Введіть ВУЗ: "; getline(cin, vuz);
    }

    void print() const override {
        Person::print();
        cout << " | Статус: Студент | Курс: " << course << " | Група: " << group << " | ВУЗ: " << vuz;
    }

    string getVUZ() const override { return vuz; }
};

// Клас Викладач (віртуальне наслідування від Person)
class Teacher : virtual public Person {
protected:
    string vuz; // ВУЗ викладача
    string position;
    double salary;

public:
    Teacher() {}

    void input() override {
        Person::input();
        cout << "Введіть ВУЗ: "; getline(cin, vuz);
        cout << "Введіть посаду: "; getline(cin, position);
        cout << "Введіть зарплату: ";
        while (!(cin >> salary) || salary < 0) {
            cout << "Помилка! Введіть коректну зарплату: ";
            cin.clear(); cin.ignore(10000, '\n');
        }
        cin.ignore();
    }

    void print() const override {
        Person::print();
        cout << " | Статус: Викладач | Посада: " << position << " | З/П: " << salary << " | ВУЗ: " << vuz;
    }

    string getVUZ() const override { return vuz; }
};

// Клас Аспірант (множинне наслідування)
class Postgraduate : public Student, public Teacher {
public:
    Postgraduate() {}

    void input() override {
        // Запитуємо спільні дані
        Person::input();
        
        // Специфічні дані студента
        cout << "Введіть курс аспірантури: ";
        cin >> course; cin.ignore();
        cout << "Введіть групу (спеціальність): "; getline(cin, group);
        
        // Специфічні дані викладача
        cout << "Введіть посаду: "; getline(cin, position);
        cout << "Введіть зарплату: "; cin >> salary; cin.ignore();

        // Аспірант вчиться і викладає в одному ВУЗі, запитуємо один раз
        cout << "Введіть ВУЗ: "; 
        string current_vuz;
        getline(cin, current_vuz);
        
        // Синхронізуємо ВУЗ для обох батьківських гілок
        Student::vuz = current_vuz;
        Teacher::vuz = current_vuz;
    }

    void print() const override {
        Person::print();
        cout << " | Статус: Аспірант | Курс: " << course << " | Група: " << group 
             << " | Посада: " << position << " | ВУЗ: " << Student::vuz;
    }

    // Вирішення проблеми неоднозначності (Diamond Problem) щодо того, чий ВУЗ повертати
    string getVUZ() const override { 
        return Student::vuz; // Можна було б Teacher::vuz, вони ідентичні
    }
};

void runTask2() {
    cout << "--- ЗАВДАННЯ 2: Множинне наслідування (Людина -> Студент/Викладач -> Аспірант) ---\n";
    
    vector<shared_ptr<Person>> people;
    int n;
    
    cout << "Скільки людей ви хочете додати в базу? ";
    while (!(cin >> n) || n <= 0) {
        cout << "Помилка! Введіть додатнє число: ";
        cin.clear(); cin.ignore(10000, '\n');
    }
    cin.ignore();

    for (int i = 0; i < n; ++i) {
        cout << "\nКого додаємо? (1 - Людина, 2 - Студент, 3 - Викладач, 4 - Аспірант): ";
        int choice;
        cin >> choice; cin.ignore();

        shared_ptr<Person> p;
        try {
            switch (choice) {
                case 1: p = make_shared<Person>(); break;
                case 2: p = make_shared<Student>(); break;
                case 3: p = make_shared<Teacher>(); break;
                case 4: p = make_shared<Postgraduate>(); break;
                default: 
                    cout << "Некоректний вибір. Спробуйте ще раз.\n";
                    i--; continue;
            }
            p->input();
            people.push_back(p);
        } catch (...) {
            cout << "Виникла помилка під час вводу даних. Спробуйте знову.\n";
            i--;
        }
    }

    cout << "\n--- РЕЄСТР ВУЗІВ ДЛЯ ВСІХ ОГЛЯНУТИХ ОСІБ ---\n";
    for (size_t i = 0; i < people.size(); ++i) {
        cout << i + 1 << ". ";
        people[i]->print();
        cout << "\n   -> Здобутий ВУЗ через поліморфізм (без нових змінних): " << people[i]->getVUZ() << "\n\n";
    }
}

// ==============================================================================
// ГОЛОВНА ФУНКЦІЯ
// ==============================================================================
int main() {
    setlocale(LC_ALL, "Ukrainian");

    runTask1();
    runTask2();

    return 0;
}