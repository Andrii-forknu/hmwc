#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <cctype>
#include <sstream>
#include <iterator>

using namespace std;

// =====================================================================
// ЗАВДАННЯ 1: Клас BoolVector
// =====================================================================
class BoolVector {
private:
    vector<bool> vec;
public:
    BoolVector(size_t size, bool default_val = false) : vec(size, default_val) {}
    BoolVector(initializer_list<bool> init) : vec(init) {}

    // Порозрядна кон'юнкція (AND)
    BoolVector operator&(const BoolVector& other) const {
        size_t min_size = min(vec.size(), other.vec.size());
        BoolVector result(min_size);
        for (size_t i = 0; i < min_size; ++i) result.vec[i] = vec[i] & other.vec[i];
        return result;
    }

    // Порозрядна диз'юнкція (OR)
    BoolVector operator|(const BoolVector& other) const {
        size_t min_size = min(vec.size(), other.vec.size());
        BoolVector result(min_size);
        for (size_t i = 0; i < min_size; ++i) result.vec[i] = vec[i] | other.vec[i];
        return result;
    }

    // Заперечення (NOT)
    BoolVector operator~() const {
        BoolVector result(vec.size());
        for (size_t i = 0; i < vec.size(); ++i) result.vec[i] = !vec[i];
        return result;
    }

    size_t countOnes() const { return count(vec.begin(), vec.end(), true); }
    size_t countZeros() const { return count(vec.begin(), vec.end(), false); }

    void print() const {
        for (bool b : vec) cout << b;
        cout << endl;
    }
};

void task1() {
    cout << "--- ЗАВДАННЯ 1 ---" << endl;
    BoolVector v1 = {true, false, true, false};
    BoolVector v2 = {true, true, false, false};
    
    cout << "v1: "; v1.print();
    cout << "v2: "; v2.print();
    
    cout << "v1 & v2: "; (v1 & v2).print();
    cout << "v1 | v2: "; (v1 | v2).print();
    cout << "~v1: "; (~v1).print();
    
    cout << "Одиниць у v1: " << v1.countOnes() << ", Нулів: " << v1.countZeros() << "\n\n";
}

// =====================================================================
// ЗАВДАННЯ 2: Перестановка елементів списку відносно X
// =====================================================================
void task2() {
    cout << "--- ЗАВДАННЯ 2 ---" << endl;
    list<int> List = {5, 12, 3, 8, 1, 15, 7, 2};
    int X = 6;
    
    cout << "Початковий список: ";
    for (int n : List) cout << n << " ";
    cout << "\nX = " << X << endl;

    // std::partition переставляє елементи так, що ті, які задовольняють умову, йдуть першими
    partition(List.begin(), List.end(), [X](int a) { return a <= X; });

    cout << "Відсортований список: ";
    for (int n : List) cout << n << " ";
    cout << "\n\n";
}

// =====================================================================
// ЗАВДАННЯ 3: k найбільших та найменших чисел
// =====================================================================
pair<int, vector<int>> processVector(const vector<int>& vec, int k) {
    if (k > vec.size() || k <= 0) {
        return {0, {}}; // Якщо k перевищує розмір або некоректне
    }

    // Сума k найбільших
    vector<int> desc = vec;
    sort(desc.rbegin(), desc.rend());
    int sumMax = accumulate(desc.begin(), desc.begin() + k, 0);

    // Масив з k найменших
    vector<int> asc = vec;
    sort(asc.begin(), asc.end());
    vector<int> minK(asc.begin(), asc.begin() + k);

    return {sumMax, minK};
}

void task3() {
    cout << "--- ЗАВДАННЯ 3 ---" << endl;
    vector<int> vec = {10, 2, 8, 4, 6, 1, 9, 3};
    int k = 3;
    
    auto result = processVector(vec, k);
    cout << "Сума " << k << " найбільших: " << result.first << endl;
    cout << "Масив з " << k << " найменших: ";
    for (int n : result.second) cout << n << " ";
    cout << "\n\n";
}

// =====================================================================
// ЗАВДАННЯ 4: Генератор clock_t та список
// =====================================================================
void task4() {
    cout << "--- ЗАВДАННЯ 4 ---" << endl;
    list<clock_t> times;
    
    // В умові вказано create_n(), але стандартною функцією є generate_n()
    generate_n(back_inserter(times), 10, []() { return clock(); });
    
    times.sort(); // Обов'язково для коректної роботи unique()
    times.unique(); // Видалення дублікатів
    
    cout << "Значення clock(): ";
    copy(times.begin(), times.end(), ostream_iterator<clock_t>(cout, " "));
    cout << "\n\n";
}

// =====================================================================
// ЗАВДАННЯ 5: transform() та toupper()
// =====================================================================
void task5() {
    cout << "--- ЗАВДАННЯ 5 ---" << endl;
    string str = "hello c++ standard library";
    cout << "До: " << str << endl;
    
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return toupper(c); });
    
    cout << "Після: " << str << "\n\n";
}

// =====================================================================
// ЗАВДАННЯ 6: Шаблон функціонального об'єкта Sum
// =====================================================================
template <typename T>
struct Sum {
    T total{}; // Ініціалізація нулем
    void operator()(const T& value) {
        total += value;
    }
};

void task6() {
    cout << "--- ЗАВДАННЯ 6 ---" << endl;
    vector<double> v = {1.5, 2.5, 3.0, 4.0};
    
    Sum<double> result = for_each(v.begin(), v.end(), Sum<double>());
    cout << "Сума елементів вектора: " << result.total << "\n\n";
}

// =====================================================================
// ЗАВДАННЯ 7: Генератор анаграм слова
// =====================================================================
void task7() {
    cout << "--- ЗАВДАННЯ 7 ---" << endl;
    string word = "abc"; // Жорстко задано для прикладу, можна замінити на cin >> word
    cout << "Анаграми для слова '" << word << "':\n";
    
    sort(word.begin(), word.end()); // Необхідно для next_permutation
    do {
        cout << word << " ";
    } while (next_permutation(word.begin(), word.end()));
    cout << "\n\n";
}

// =====================================================================
// ЗАВДАННЯ 8: Генератор анаграм речення
// =====================================================================
void task8() {
    cout << "--- ЗАВДАННЯ 8 ---" << endl;
    string sentence = "C++ is great"; 
    cout << "Анаграми речення '" << sentence << "':\n";
    
    stringstream ss(sentence);
    string word;
    vector<string> words;
    
    while (ss >> word) {
        words.push_back(word);
    }
    
    sort(words.begin(), words.end()); // Необхідно для next_permutation
    
    int count = 0;
    do {
        for (const string& w : words) cout << w << " ";
        cout << endl;
        count++;
    } while (next_permutation(words.begin(), words.end()));
    
    cout << "Всього комбінацій: " << count << "\n\n";
}

// =====================================================================
// ГОЛОВНА ФУНКЦІЯ
// =====================================================================
int main() {
    // Встановлення кодування для Windows (щоб українська мова виводилась коректно)
    #if defined(_WIN32) || defined(_WIN64)
    system("chcp 65001 > nul");
    #endif

    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    task7();
    task8();

    return 0;
}