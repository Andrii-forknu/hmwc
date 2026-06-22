#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>

// ==============================================================================
// 5) ШАБЛОННИЙ КЛАС МАСИВ ТА ЙОГО МЕТОДИ СОРТУВАННЯ (З ПОПЕРЕДНЬОГО ЗАВДАННЯ)
// ==============================================================================
template <typename T>
class Array {
private:
    T* data;
    size_t size;

public:
    Array(const std::vector<T>& init_data) {
        size = init_data.size();
        data = new T[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = init_data[i];
        }
    }

    ~Array() {
        delete[] data;
    }

    size_t getSize() const { return size; }
    T* getData() { return data; }

    void print() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    void bubbleSort() {
        bubbleSortStatic(this->data, this->size);
    }

    void shakerSort() {
        shakerSortStatic(this->data, this->size);
    }

    static void bubbleSortStatic(T* arr, size_t n) {
        if (n == 0) return;
        for (size_t i = 0; i < n - 1; ++i) {
            bool swapped = false;
            for (size_t j = 0; j < n - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
    }

    static void shakerSortStatic(T* arr, size_t n) {
        if (n == 0) return;
        int left = 0;
        int right = n - 1;
        bool swapped = true;

        while (left < right && swapped) {
            swapped = false;
            for (int i = left; i < right; ++i) {
                if (arr[i] > arr[i + 1]) {
                    std::swap(arr[i], arr[i + 1]);
                    swapped = true;
                }
            }
            right--;

            for (int i = right; i > left; --i) {
                if (arr[i - 1] > arr[i]) {
                    std::swap(arr[i - 1], arr[i]);
                    swapped = true;
                }
            }
            left++;
        }
    }
};

// ==============================================================================
// 7) ШАБЛОННИЙ КЛАС СУПЕР-РЯДОК (CustomString)
// ==============================================================================
template <typename T>
class CustomString {
private:
    std::vector<T> symbols; // Внутрішній масив символів довільного типу
    T delimiter;            // Роздільник того самого типу

public:
    // Конструктор
    CustomString(T delim = T()) : delimiter(delim) {}

    CustomString(const std::vector<T>& syms, T delim) : symbols(syms), delimiter(delim) {}

    // Введення та заміна роздільника
    void setDelimiter(const T& delim) {
        delimiter = delim;
    }

    T getDelimiter() const {
        return delimiter;
    }

    // Довжина рядка (кількість символів)
    size_t length() const {
        return symbols.size();
    }

    // Доступ до даного символу за квадратними дужками
    T& operator[](size_t index) {
        if (index >= symbols.size()) {
            throw std::out_of_range("Помилка: Індекс виходить за межі рядка!");
        }
        return symbols[index];
    }

    const T& operator[](size_t index) const {
        if (index >= symbols.size()) {
            throw std::out_of_range("Помилка: Індекс виходить за межі рядка!");
        }
        return symbols[index];
    }

    // Додавання символу в кінець рядка
    void append(const T& sym) {
        symbols.push_back(sym);
    }

    // Видалення даного символу за індексом
    void removeAt(size_t index) {
        if (index >= symbols.size()) {
            throw std::out_of_range("Помилка: Неможливо видалити символ, індекс поза межами!");
        }
        symbols.erase(symbols.begin() + index);
    }

    // Метод конкатенації (з додаванням між рядками роздільника)
    CustomString operator+(const CustomString& other) const {
        std::vector<T> new_symbols = this->symbols;
        
        // Якщо обидва рядки не порожні, додаємо поточний роздільник між ними
        if (!this->symbols.empty() && !other.symbols.empty()) {
            new_symbols.push_back(this->delimiter);
        }
        
        // Додаємо символи іншого рядка
        for (const auto& sym : other.symbols) {
            new_symbols.push_back(sym);
        }
        
        return CustomString(new_symbols, this->delimiter);
    }

    // Злиття символів – перетворення внутрішнього масиву елементів T на єдиний std::string
    std::string mergeToString() const {
        std::stringstream ss;
        for (size_t i = 0; i < symbols.size(); ++i) {
            ss << symbols[i];
            if (i + 1 < symbols.size()) {
                ss << delimiter;
            }
        }
        return ss.str();
    }

    // Дружні оператори для консольного вводу/виводу
    friend std::ostream& operator<<(std::ostream& os, const CustomString<T>& cs) {
        for (size_t i = 0; i < cs.symbols.size(); ++i) {
            os << cs.symbols[i];
            if (i + 1 < cs.symbols.size()) {
                os << cs.delimiter;
            }
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, CustomString<T>& cs) {
        size_t count;
        std::cout << "Введіть кількість елементів для заповнення рядка: ";
        if (!(is >> count)) {
            throw std::runtime_error("Помилка введення кількості елементів!");
        }
        
        std::cout << "Введіть значення роздільника: ";
        is >> cs.delimiter;

        cs.symbols.clear();
        std::cout << "Введіть " << count << " елементів через пробіл:\n";
        for (size_t i = 0; i < count; ++i) {
            T temp;
            if (!(is >> temp)) {
                throw std::runtime_error("Помилка введення значення символу!");
            }
            cs.symbols.push_back(temp);
        }
        return is;
    }

    // Методи роботи з файлами (запис/читання)
    void saveToFile(const std::string& filename) const {
        std::ofstream ofs(filename);
        if (!ofs.is_open()) {
            throw std::runtime_error("Не вдалося відкрити файл " + filename + " для запису!");
        }
        ofs << delimiter << "\n";
        ofs << symbols.size() << "\n";
        for (const auto& sym : symbols) {
            ofs << sym << "\n";
        }
        ofs.close();
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream ifs(filename);
        if (!ifs.is_open()) {
            throw std::runtime_error("Не вдалося відкрити файл " + filename + " для читання!");
        }
        if (!(ifs >> delimiter)) {
            throw std::runtime_error("Помилка читання роздільника з файлу!");
        }
        size_t size;
        if (!(ifs >> size)) {
            throw std::runtime_error("Помилка читання розміру рядка з файлу!");
        }
        symbols.clear();
        for (size_t i = 0; i < size; ++i) {
            T temp;
            if (!(ifs >> temp)) {
                throw std::runtime_error("Помилка читання символу з файлу (файл пошкоджено або неповний)!");
            }
            symbols.push_back(temp);
        }
        ifs.close();
    }
};

// ==============================================================================
// СПЕЦІАЛІЗАЦІЯ ЯК ЗВИЧАЙНИЙ РЯДОК ПРИ СИМВОЛІ ТИПУ char
// ==============================================================================
template <>
class CustomString<char> {
private:
    std::string symbols;
    char delimiter;

public:
    CustomString(char delim = ' ') : delimiter(delim) {}
    CustomString(const std::string& syms, char delim) : symbols(syms), delimiter(delim) {}

    void setDelimiter(char delim) { delimiter = delim; }
    char getDelimiter() const { return delimiter; }
    size_t length() const { return symbols.length(); }

    char& operator[](size_t index) {
        if (index >= symbols.length()) throw std::out_of_range("Індекс поза межами!");
        return symbols[index];
    }

    void append(char sym) { symbols += sym; }
    
    void removeAt(size_t index) {
        if (index >= symbols.length()) throw std::out_of_range("Індекс поза межами!");
        symbols.erase(index, 1);
    }

    CustomString operator+(const CustomString& other) const {
        std::string new_symbols = this->symbols;
        if (!this->symbols.empty() && !other.symbols.empty()) {
            new_symbols += this->delimiter;
        }
        new_symbols += other.symbols;
        return CustomString(new_symbols, this->delimiter);
    }

    std::string mergeToString() const {
        std::string res = "";
        for (size_t i = 0; i < symbols.length(); ++i) {
            res += symbols[i];
            if (i + 1 < symbols.length()) res << delimiter; 
        }
        return symbols; 
    }

    friend std::ostream& operator<<(std::ostream& os, const CustomString<char>& cs) {
        os << cs.symbols; 
        return os;
    }

    friend std::istream& operator>>(std::istream& is, CustomString<char>& cs) {
        std::cout << "Введіть символ-роздільник: ";
        is >> cs.delimiter;
        std::cout << "Введіть звичайний рядок: ";
        is >> cs.symbols;
        return is;
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream ofs(filename);
        if (!ofs.is_open()) throw std::runtime_error("Файл не відкрито!");
        ofs << delimiter << "\n" << symbols;
        ofs.close();
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream ifs(filename);
        if (!ifs.is_open()) throw std::runtime_error("Файл не відкрито!");
        ifs >> delimiter;
        ifs >> symbols;
        ifs.close();
    }
};

// ==============================================================================
// ДЕМОНСТРАЦІЙНІ ФУНКЦІЇ ДЛЯ ТЕСТУВАННЯ ОБВОХ КЛАСІВ
// ==============================================================================
void execute_array_sorting_demo() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "   ДЕМОНСТРАЦІЯ 5) КЛАСУ МАСИВ (ШЕЙКЕР-СОРТУВАННЯ)" << std::endl;
    std::cout << "==================================================" << std::endl;
    
    Array<int> intArray({42, 13, 7, 88, 1, 23});
    std::cout << "Початковий масив: ";
    intArray.print();
    
    intArray.shakerSort();
    std::cout << "Після Шейкер-сорування: ";
    intArray.print();
}

void execute_custom_string_demo() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "   ДЕМОНСТРАЦІЯ 7) КЛАСУ СУПЕР-РЯДОК" << std::endl;
    std::cout << "==================================================" << std::endl;

    try {
        // Тест 1: Рядок, де елементом (символом) є інший рядок (std::string)
        std::cout << "[Тест 1: Рядок із рядків std::string]" << std::endl;
        CustomString<std::string> sentence("---"); // Роздільник "---"
        sentence.append("Слава");
        sentence.append("Україні");
        sentence.append("Героям");
        sentence.append("Слава");
        
        std::cout << "Вміст рядка: " << sentence << std::endl;
        std::cout << "Довжина рядка: " << sentence.length() << " елементів." << std::endl;
        std::cout << "Елемент за індексом [1]: " << sentence[1] << std::endl;
        
        std::cout << "Заміна роздільника на ' * '..." << std::endl;
        sentence.setDelimiter(" * ");
        std::cout << "Новий вигляд рядка: " << sentence << std::endl;

        // Конкатенація
        CustomString<std::string> suffix(" * ");
        suffix.append("Назавжди");
        CustomString<std::string> final_str = sentence + suffix;
        std::cout << "Результат конкатенації: " << final_str << std::endl;

        // Злиття
        std::cout << "Злиття в єдиний рядок: " << final_str.mergeToString() << std::endl;

        // Видалення елемента
        std::cout << "Видалення елемента за індексом [2]..." << std::endl;
        final_str.removeAt(2);
        std::cout << "Результат після видалення: " << final_str << std::endl;

        // Робота з файлами
        std::cout << "Збереження рядка у файл 'string_data.txt'..." << std::endl;
        final_str.saveToFile("string_data.txt");

        CustomString<std::string> file_str;
        std::cout << "Читання рядка з файлу 'string_data.txt'..." << std::endl;
        file_str.loadFromFile("string_data.txt");
        std::cout << "Зчитаний з файлу рядок: " << file_str << std::endl;

        // Тест 2: Спеціалізація для типу char
        std::cout << "\n[Тест 2: Спеціалізація для типу char]" << std::endl;
        CustomString<char> charStr("Hello", ',');
        std::cout << "Рядок char: " << charStr << " | Довжина: " << charStr.length() << std::endl;

        // Ініціювання помилки виходу за межі
        std::cout << "\n[Тест 3: Виклик помилки (Вихід за межі)]" << std::endl;
        std::cout << charStr[99] << std::endl;

    } catch (const std::out_of_range& e) {
        std::cerr << "[Перехоплено виключення діапазону]: " << e.what() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "[Перехоплено системне виключення]: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[Перехоплено загальне виключення]: " << e.what() << std::endl;
    }
}

// ==============================================================================
// ГОЛОВНА ФУНКЦІЯ
// ==============================================================================
int main() {
    setlocale(LC_ALL, "uk_UA.UTF-8");

    execute_array_sorting_demo();
    execute_custom_string_demo();

    return 0;
}