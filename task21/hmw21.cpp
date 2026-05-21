#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Структура для зберігання даних про людину
struct Person {
    string surname;
    int age;
};

// Допоміжна функція для зручного виводу списку
void printPeople(const vector<Person>& people, const string& title) {
    cout << "=== " << title << " ===" << endl;
    for (const auto& p : people) {
        cout << setw(15) << left << p.surname << " | Вік: " << p.age << endl;
    }
    cout << endl;
}

int main() {
    // Налаштування кодування для коректного відображення кирилиці в консолі Windows
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    // Згенеруємо довільну кількість людей з різним віком та прізвищами
    vector<Person> recruits = {
        {"Коваленко", 40},
        {"Шевченко", 22},
        {"Бойко", 34},
        {"Ткаченко", 19},
        {"Кравченко", 35},
        {"Олійник", 28},
        {"Мельник", 45},
        {"Волошин", 25},
        {"Лисенко", 38},
        {"Григоренко", 18}
    };

    printPeople(recruits, "Початковий (несортований) список");

    // 1. Розділяємо вектор: ті, кому менше 35, йдуть на початок.
    // std::partition повертає ітератор на перший елемент другої групи (тих, кому 35 і більше)
    auto bound = partition(recruits.begin(), recruits.end(), [](const Person& p) {
        return p.age < 35;
    });

    // 2. Сортуємо першу частину (< 35 років) від наймолодшого до найстаршого (за зростанням віку)
    sort(recruits.begin(), bound, [](const Person& a, const Person& b) {
        return a.age < b.age;
    });

    // 3. Сортуємо другу частину (>= 35 років) за прізвищем за алфавітом
    sort(bound, recruits.end(), [](const Person& a, const Person& b) {
        return a.surname < b.surname;
    });

    // Виводимо фінальний результат
    printPeople(recruits, "Відсортований список для армії");

    return 0;
}