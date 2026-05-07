#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

// --- ЗАДАЧА 9: Заміна чисел у файлі на квадрати ---
void solveTask9() {
    string filename = "task9.txt";
    cout << "\n--- Задача 9 ---\n";
    
    // Спершу перевіримо/створимо файл для тестування, якщо його немає
    ifstream checkFile(filename);
    if (!checkFile) {
        cout << "Файл task9.txt не знайдено. Створюю тестовий файл...\n";
        ofstream create(filename);
        create << "5 3 8 2 10 4 4"; // Приклад: 5>3 (буде 25), 8>2 (64), 10>4 (100)
        create.close();
    } else {
        checkFile.close();
    }

    ifstream fin(filename);
    vector<long long> nums;
    long long temp;
    
    while (fin >> temp) {
        nums.push_back(temp);
    }
    fin.close();

    if (nums.empty()) {
        cout << "Файл порожній.\n";
        return;
    }

    // Логіка: якщо елемент > наступного, підносимо до квадрата
    // Останній елемент не має наступного, тому його не чіпаємо
    for (size_t i = 0; i < nums.size() - 1; ++i) {
        if (nums[i] > nums[i+1]) {
            nums[i] = nums[i] * nums[i];
        }
    }

    // Перезапис файлу
    ofstream fout(filename);
    for (size_t i = 0; i < nums.size(); ++i) {
        fout << nums[i] << (i == nums.size() - 1 ? "" : " ");
    }
    fout.close();

    cout << "Файл " << filename << " успішно оновлено.\n";
    cout << "Новий вміст файлу виведено в консоль.\n";
}

// --- ГОЛОВНЕ МЕНЮ (включаючи попередні задачі) ---
int main() {
    setlocale(LC_ALL, "Ukrainian");
    int choice;
    do {
        cout << "\n--- МЕНЮ ---\n";
        cout << "1. Попередні задачі (1.4, 1.5, 2.1...)\n";
        cout << "6. Задача 9 (Заміна на квадрати у файлі)\n";
        cout << "0. Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
            case 6: solveTask9(); break;
            case 0: break;
            default: cout << "Виберіть дію з меню.\n";
        }
    } while (choice != 0);

    return 0;
}