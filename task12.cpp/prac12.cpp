#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

// --- Завдання 1.4: Робота з файлами та степенями ---
void solveTask1_4() {
    int n;
    cout << "\n--- Завдання 1.4 ---\nВведіть n: ";
    cin >> n;

    vector<int> m(n);
    cout << "Введіть " << n << " цілих чисел (масив m): ";
    for (int i = 0; i < n; i++) cin >> m[i];

    ifstream fin("input_14.txt");
    if (!fin) {
        cout << "Помилка: файл input_14.txt не знайдено!\n";
        return;
    }

    vector<double> x(n);
    for (int i = 0; i < n; i++) {
        if (!(fin >> x[i])) {
            cout << "Помилка: недостатньо даних або некоректні дані у файлі.\n";
            return;
        }
    }
    fin.close();

    ofstream fout("output_14.txt");
    fout << fixed << setprecision(4);
    for (int i = 0; i < n; i++) {
        fout << pow(x[i], m[i]) << (i == n - 1 ? "" : " ");
    }
    fout.close();
    cout << "Результати x_i^m_i збережено в output_14.txt\n";
}

// --- Завдання 1.5: Зворотній вивід коренів великих чисел ---
void solveTask1_5() {
    cout << "\n--- Завдання 1.5 ---\n";
    ifstream fin("input_15.txt");
    if (!fin) {
        cout << "Помилка: файл input_15.txt не знайдено!\n";
        return;
    }

    vector<unsigned long long> nums;
    unsigned long long val;
    while (fin >> val) {
        nums.push_back(val);
    }
    fin.close();

    cout << "Результати (корені у зворотному порядку):\n";
    cout << fixed << setprecision(3);
    for (auto it = nums.rbegin(); it != nums.rend(); ++it) {
        cout << sqrt((double)*it) << endl;
    }
}

// --- Завдання 2.1: Степінь x^y у різних форматах ---
void solveTask2_1() {
    double x, y;
    cout << "\n--- Завдання 2.1 ---\nВведіть x: ";
    cin >> x;
    cout << "Введіть y: ";
    cin >> y;

    double res = pow(x, y);
    cout << "Десяткове представлення: " << fixed << res << endl;
    cout << "Наукове представлення: " << scientific << res << endl;
    cout << defaultfloat; // Скидання формату
}

// --- Завдання 2.2: Сума 10-значних чисел ---
void solveTask2_2() {
    int n;
    cout << "\n--- Завдання 2.2 ---\nВведіть n (кількість чисел): ";
    cin >> n;

    vector<unsigned long long> arr(n);
    unsigned long long totalSum = 0;

    cout << "Введіть " << 10 * n << " цифр поспіль (або блоки по 10 цифр):\n";
    for (int i = 0; i < n; i++) {
        string s;
        // Зчитуємо рівно 10 символів
        for(int j = 0; j < 10; ++j) {
            char ch;
            cin >> ch;
            s += ch;
        }
        arr[i] = stoull(s);
        totalSum += arr[i];
    }

    cout << "Сума введених чисел: " << totalSum << endl;
}

// --- Завдання 2.3: Таблиця коренів ---
void solveTask2_3() {
    int n;
    cout << "\n--- Завдання 2.3 ---\nВведіть n: ";
    cin >> n;

    auto printLine = [n](int width) {
        for (int i = 0; i < n * width + 1; i++) cout << "+";
        cout << endl;
    };

    const int w = 8; // Ширина колонки
    printLine(w);

    // Рядок з числами
    cout << "|";
    for (int i = 1; i <= n; i++) cout << setw(w - 1) << i << "|";
    cout << endl;

    printLine(w);

    // Рядок з коренями
    cout << "|";
    for (int i = 1; i <= n; i++) {
        double r = sqrt(i);
        // Якщо корінь цілий — 0 знаків, інакше — 2
        if (r == floor(r)) 
            cout << setw(w - 1) << setprecision(0) << fixed << r << "|";
        else 
            cout << setw(w - 1) << setprecision(2) << fixed << r << "|";
    }
    cout << endl;

    printLine(w);
    cout << defaultfloat;
}

int main() {
    // Налаштування локалі для підтримки української мови в консолі
    setlocale(LC_ALL, "Ukrainian");

    int choice;
    do {
        cout << "\n================ Меню ================\n";
        cout << "1. Завдання 1.4 (x_i^m_i з файлу)\n";
        cout << "2. Завдання 1.5 (Корені 10^18 навпаки)\n";
        cout << "3. Завдання 2.1 (x^y у двох форматах)\n";
        cout << "4. Завдання 2.2 (Сума 10-значних чисел)\n";
        cout << "5. Завдання 2.3 (Таблиця коренів)\n";
        cout << "0. Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
            case 1: solveTask1_4(); break;
            case 2: solveTask1_5(); break;
            case 3: solveTask2_1(); break;
            case 4: solveTask2_2(); break;
            case 5: solveTask2_3(); break;
            case 0: cout << "Вихід...\n"; break;
            default: cout << "Невірний вибір!\n";
        }
    } while (choice != 0);

    return 0;
}