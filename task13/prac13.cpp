#include <iostream>
#include <string>
#include <vector>
#include <cctype>

// ==============================================================================
// ЗАВДАННЯ 1: Підрядок між першою ':' та наступною ','
// ==============================================================================

// Варіант 1: Повертає новий рядок
std::string task1_new(const std::string& str) {
    size_t colon_pos = str.find(':');
    if (colon_pos == std::string::npos) {
        return str; // Немає двокрапки - залишаємо без змін
    }
    
    size_t comma_pos = str.find(',', colon_pos + 1);
    if (comma_pos == std::string::npos) {
        // Немає коми після двокрапки - від двокрапки до кінця (без самої двокрапки)
        return str.substr(colon_pos + 1); 
    }
    
    // Є і двокрапка, і кома - повертаємо між ними
    return str.substr(colon_pos + 1, comma_pos - colon_pos - 1);
}

// Варіант 2: Замінює існуючий рядок (через посилання)
void task1_mod(std::string& str) {
    str = task1_new(str);
}


// ==============================================================================
// ЗАВДАННЯ 2: Видалення підрядка між першою та останньою крапкою
// ==============================================================================

// Варіант 1: Повертає новий рядок
std::string task2_new(const std::string& s) {
    std::string str = s;
    size_t first_dot = str.find('.');
    size_t last_dot = str.rfind('.');

    if (first_dot == std::string::npos) {
        // Крапок немає: видаляємо всі пробіли на початку тексту
        size_t first_not_space = str.find_first_not_of(" ");
        if (first_not_space != std::string::npos) {
            str.erase(0, first_not_space);
        } else {
            str.clear(); // Якщо рядок складається лише з пробілів
        }
    } else if (first_dot == last_dot) {
        // Лише одна крапка: видаляємо все ДО неї
        str.erase(0, first_dot); 
    } else {
        // Більше однієї крапки: видаляємо між першою та останньою (залишаючи самі крапки)
        str.erase(first_dot + 1, last_dot - first_dot - 1);
    }
    return str;
}

// Варіант 2: Замінює існуючий рядок
void task2_mod(std::string& str) {
    size_t first_dot = str.find('.');
    size_t last_dot = str.rfind('.');

    if (first_dot == std::string::npos) {
        size_t first_not_space = str.find_first_not_of(" ");
        if (first_not_space != std::string::npos) {
            str.erase(0, first_not_space);
        } else {
            str.clear();
        }
    } else if (first_dot == last_dot) {
        str.erase(0, first_dot);
    } else {
        str.erase(first_dot + 1, last_dot - first_dot - 1);
    }
}


// ==============================================================================
// ЗАВДАННЯ 3: Видалення останньої літери кожного слова
// ==============================================================================

// Варіант 1: Повертає новий рядок
std::string task3_new(const std::string& str) {
    std::string res;
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] != ' ') {
            // Перевіряємо, чи це остання літера слова
            if (i + 1 == str.length() || str[i+1] == ' ') {
                continue; // Пропускаємо додавання цієї літери
            }
        }
        res += str[i];
    }
    return res;
}

// Варіант 2: Замінює існуючий рядок (йдемо з кінця, щоб не збити індекси при видаленні)
void task3_mod(std::string& str) {
    if (str.empty()) return;
    for (int i = (int)str.length() - 1; i >= 0; --i) {
        if (str[i] != ' ') {
            if (i == (int)str.length() - 1 || str[i+1] == ' ') {
                str.erase(i, 1);
            }
        }
    }
}


// ==============================================================================
// ЗАВДАННЯ 6: Пошук найкоротшого слова
// ==============================================================================

void task6(const std::string& str) {
    std::vector<std::string> words;
    std::string current_word;
    
    // Парсимо речення на слова (тільки латинські літери)
    for (char c : str) {
        if (isalpha(c)) {
            current_word += c;
        } else {
            if (!current_word.empty()) {
                words.push_back(current_word);
                current_word.clear();
            }
        }
    }
    if (!current_word.empty()) words.push_back(current_word);

    if (words.empty()) {
        std::cout << "Не знайдено слів з латинських літер.\n";
        return;
    }

    // Знаходимо мінімальну довжину
    size_t min_len = words[0].length();
    for (const auto& w : words) {
        if (w.length() < min_len) min_len = w.length();
    }

    // Збираємо всі найкоротші слова
    std::vector<std::string> shortest;
    for (const auto& w : words) {
        if (w.length() == min_len) shortest.push_back(w);
    }

    std::cout << "а) Перше з них:   " << shortest.front() << "\n";
    std::cout << "б) Останнє з них: " << shortest.back() << "\n";
    std::cout << "в) Всі такі слова: ";
    for (const auto& w : shortest) {
        std::cout << w << " ";
    }
    std::cout << "\n";
}


// ==============================================================================
// ГОЛОВНА ФУНКЦІЯ (ДЕМОНСТРАЦІЯ РОБОТИ)
// ==============================================================================

int main() {
    std::cout << "--- ДЕМОНСТРАЦІЯ ЗАВДАННЯ 1 ---\n";
    std::string s1 = "Початок:середина,кінець";
    std::cout << "Оригінал: '" << s1 << "'\n";
    std::cout << "Варіант 1 (новий рядок): '" << task1_new(s1) << "'\n";
    task1_mod(s1);
    std::cout << "Варіант 2 (in-place):    '" << s1 << "'\n\n";

    std::cout << "--- ДЕМОНСТРАЦІЯ ЗАВДАННЯ 2 ---\n";
    std::string s2_no_dots = "    Без крапок";
    std::string s2_one_dot = "Текст до крапки.Текст після";
    std::string s2_many_dots = "Перша.Друга.Третя.Остання";
    
    std::cout << "Немає крапок:   '" << task2_new(s2_no_dots) << "'\n";
    std::cout << "Одна крапка:    '" << task2_new(s2_one_dot) << "'\n";
    std::cout << "Багато крапок:  '" << task2_new(s2_many_dots) << "'\n";
    
    task2_mod(s2_many_dots);
    std::cout << "In-place (багато крапок): '" << s2_many_dots << "'\n\n";

    std::cout << "--- ДЕМОНСТРАЦІЯ ЗАВДАННЯ 3 ---\n";
    std::string s3 = "hello  world from   Ukraine";
    std::cout << "Оригінал: '" << s3 << "'\n";
    std::cout << "Варіант 1 (новий рядок): '" << task3_new(s3) << "'\n";
    task3_mod(s3);
    std::cout << "Варіант 2 (in-place):    '" << s3 << "'\n\n";

    std::cout << "--- ДЕМОНСТРАЦІЯ ЗАВДАННЯ 6 ---\n";
    std::string s6 = "This is a simple test sentence with a short word at the end.";
    std::cout << "Речення: '" << s6 << "'\n";
    task6(s6);

    return 0;
}