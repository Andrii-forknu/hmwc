#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>

using namespace std;

// ==============================================================================
// 1. Базовий клас Person
// ==============================================================================
class Person {
protected: // Змінено з private на protected, щоб похідні класи мали доступ
    string name; // прізвище
    unsigned byear; // рік народження

public:
    // Конструктор за замовчуванням
    Person(string n = "Unknown", unsigned y = 0) : name(n), byear(y) {}

    // Віртуальний деструктор (важливо для поліморфізму)
    virtual ~Person() {}

    // Геттер для прізвища (потрібен для пошуку)
    string getName() const { return name; }

    // Метод вводу
    virtual int input() {
        cout << "Введіть прізвище: ";
        cin >> name;
        cout << "Введіть рік народження: ";
        while (!(cin >> byear)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка. Введіть число: ";
        }
        return 1;
    }

    // Метод виводу
    virtual void show() const {
        cout << "Прізвище: " << name << ", Рік народження: " << byear;
    }

    // Перевантаження операторів вводу-виводу
    friend istream& operator>>(istream& is, Person& p) {
        is >> p.name >> p.byear;
        return is;
    }

    friend ostream& operator<<(ostream& os, const Person& p) {
        os << p.name << " " << p.byear;
        return os;
    }
};

// ==============================================================================
// 2. Клас Знайомий (Acquaintance) - похідний від Person
// ==============================================================================
class Acquaintance : public Person {
private:
    string phone_number; // Додаткове поле: номер телефону

public:
    // Конструктор
    Acquaintance(string n = "Unknown", unsigned y = 0, string phone = "") 
        : Person(n, y), phone_number(phone) {}

    // Геттер і сеттер для телефону
    string getPhone() const { return phone_number; }
    void setPhone(const string& new_phone) { phone_number = new_phone; }

    // Перевизначення методу вводу
    int input() override {
        Person::input(); // Виклик базового методу
        cout << "Введіть номер телефону: ";
        cin >> phone_number;
        return 1;
    }

    // Перевизначення методу виводу
    void show() const override {
        Person::show(); // Виклик базового методу
        cout << ", Телефон: " << phone_number << endl;
    }

    // Перевантаження операторів для зручної роботи з файлами
    friend istream& operator>>(istream& is, Acquaintance& a) {
        is >> a.name >> a.byear >> a.phone_number;
        return is;
    }

    friend ostream& operator<<(ostream& os, const Acquaintance& a) {
        os << a.name << " " << a.byear << " " << a.phone_number;
        return os;
    }
};

// ==============================================================================
// 3. Клас Телефонний довідник (PhoneBook)
// ==============================================================================
class PhoneBook {
private:
    vector<Acquaintance> contacts;
    string filename;
    const size_t MAX_CONTACTS = 100; // Обмеження за умовою

public:
    // Конструктор: завантажує дані з файлу при створенні
    PhoneBook(const string& file) : filename(file) {
        loadFromFile();
    }

    // Деструктор: зберігає дані у файл перед знищенням об'єкта
    ~PhoneBook() {
        saveToFile();
    }

    // Додавання запису
    void addContact() {
        if (contacts.size() >= MAX_CONTACTS) {
            cout << "Довідник переповнений! Максимум " << MAX_CONTACTS << " записів.\n";
            return;
        }
        Acquaintance new_contact;
        cout << "\n--- Додавання нового знайомого ---\n";
        new_contact.input();
        contacts.push_back(new_contact);
        cout << "Запис успішно додано.\n";
    }

    // Виведення всіх записів
    void showAll() const {
        if (contacts.empty()) {
            cout << "Довідник порожній.\n";
            return;
        }
        cout << "\n--- Телефонний довідник (" << contacts.size() << "/" << MAX_CONTACTS << ") ---\n";
        for (const auto& contact : contacts) {
            contact.show();
        }
    }

    // Пошук номера телефону за прізвищем
    void searchByName() const {
        string target_name;
        cout << "\nВведіть прізвище для пошуку: ";
        cin >> target_name;

        bool found = false;
        for (const auto& contact : contacts) {
            if (contact.getName() == target_name) {
                cout << "Знайдено: ";
                contact.show();
                found = true;
            }
        }
        if (!found) {
            cout << "Абонента з прізвищем '" << target_name << "' не знайдено.\n";
        }
    }

    // Заміна номера телефону за прізвищем
    void updatePhone() {
        string target_name;
        cout << "\nВведіть прізвище абонента, якому треба змінити номер: ";
        cin >> target_name;

        bool found = false;
        for (auto& contact : contacts) {
            if (contact.getName() == target_name) {
                cout << "Поточний запис: ";
                contact.show();
                string new_phone;
                cout << "Введіть новий номер телефону: ";
                cin >> new_phone;
                contact.setPhone(new_phone);
                cout << "Номер успішно оновлено.\n";
                found = true;
                break; // Припускаємо, що змінюємо перший знайдений збіг
            }
        }
        if (!found) {
            cout << "Абонента з прізвищем '" << target_name << "' не знайдено.\n";
        }
    }

private:
    // Читання з файлу
    void loadFromFile() {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Файл '" << filename << "' не знайдено. Буде створено новий.\n";
            return;
        }
        
        Acquaintance temp;
        while (file >> temp) {
            if (contacts.size() < MAX_CONTACTS) {
                contacts.push_back(temp);
            } else {
                cout << "Увага: у файлі більше 100 записів. Завантажено лише перші 100.\n";
                break;
            }
        }
        file.close();
        cout << "Довідник завантажено з файлу. Кількість записів: " << contacts.size() << "\n";
    }

    // Запис у файл
    void saveToFile() const {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Помилка при збереженні файлу!\n";
            return;
        }
        for (const auto& contact : contacts) {
            file << contact << "\n";
        }
        file.close();
    }
};

// ==============================================================================
// ГОЛОВНА ФУНКЦІЯ (Меню)
// ==============================================================================
void displayMenu() {
    cout << "\n===============================\n";
    cout << "      ТЕЛЕФОННИЙ ДОВІДНИК\n";
    cout << "===============================\n";
    cout << "1. Вивести всі записи\n";
    cout << "2. Додати знайомого\n";
    cout << "3. Знайти номер за прізвищем\n";
    cout << "4. Змінити номер телефону\n";
    cout << "0. Вийти (збереження автоматичне)\n";
    cout << "Ваш вибір: ";
}

int main() {
    // Встановлення української локалі
    setlocale(LC_ALL, "Ukrainian");

    string db_filename = "contacts.txt";
    PhoneBook book(db_filename);

    int choice;
    do {
        displayMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = -1;
        }

        switch (choice) {
            case 1: book.showAll(); break;
            case 2: book.addContact(); break;
            case 3: book.searchByName(); break;
            case 4: book.updatePhone(); break;
            case 0: cout << "Збереження даних... Вихід з програми.\n"; break;
            default: cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    } while (choice != 0);

    return 0;
}