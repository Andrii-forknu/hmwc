#include <iostream>
#include <string>
#include <stack>
#include <stdexcept>

// ==============================================================================
// ВЛАСНИЙ ПРОСТІР ІМЕН З КЛАСАМИ ТА ФУНКЦІЯМИ
// ==============================================================================
namespace MyNamespace {

    // --------------------------------------------------------------------------
    // ЗАВДАННЯ 1: Шаблонна функція пошуку максимуму
    // --------------------------------------------------------------------------
    template <typename T>
    T get_max(const T& a, const T& b) {
        return (a > b) ? a : b;
    }

    // Клас Раціональний дріб
    class Rational {
    private:
        int nominator;
        int denominator;
    public:
        Rational(int n = 0, int d = 1) : nominator(n), denominator(d) {
            if (denominator == 0) denominator = 1;
        }

        // Щоб шаблонна функція get_max запрацювала для цього класу,
        // необхідно обов'язково визначити (перевантажити) оператор >
        bool operator>(const Rational& other) const {
            return static_cast<double>(nominator) / denominator > 
                   static_cast<double>(other.nominator) / other.denominator;
        }

        friend std::ostream& operator<<(std::ostream& os, const Rational& r) {
            os << r.nominator << "/" << r.denominator;
            return os;
        }
    };

    // --------------------------------------------------------------------------
    // ЗАВДАННЯ 2: Власна реалізація шаблону класу Стек (динамічний вузловий)
    // --------------------------------------------------------------------------
    template <typename T>
    class Stack {
    private:
        struct Node {
            T data;
            Node* next;
            Node(const T& val, Node* n = nullptr) : data(val), next(n) {}
        };
        Node* head = nullptr;
        int count = 0;

    public:
        Stack() = default;
        
        ~Stack() {
            while (!empty()) {
                pop();
            }
        }

        // Заборона копіювання для безпеки роботи з пам'яттю
        Stack(const Stack&) = delete;
        Stack& operator=(const Stack&) = delete;

        void push(const T& val) {
            head = new Node(val, head);
            count++;
        }

        void pop() {
            if (!empty()) {
                Node* temp = head;
                head = head->next;
                delete temp;
                count--;
            }
        }

        T top() const {
            if (empty()) throw std::underflow_error("Стек порожній!");
            return head->data;
        }

        bool empty() const {
            return head == nullptr;
        }

        int size() const {
            return count;
        }
    };

    // Функція введення чисел до першого нуля через власний Стек
    int read_into_custom_stack(Stack<int>& out_stack) {
        int val;
        int elements_count = 0;
        while (std::cin >> val && val != 0) {
            out_stack.push(val);
            elements_count++;
        }
        return elements_count;
    }

    // Аналогічна функція для іншого типу чисел (наприклад, double) через стандартний std::stack
    template <typename T>
    int read_into_stl_stack(std::stack<T>& out_stack) {
        T val;
        int elements_count = 0;
        while (std::cin >> val && val != 0) {
            out_stack.push(val);
            elements_count++;
        }
        return elements_count;
    }
}

// ==============================================================================
// ГОЛОВНА ФУНКЦІЯ ДЛЯ ДЕМОНСТРАЦІЇ ТА ПЕРЕВІРКИ
// ==============================================================================
int main() {
    // --------------------------------------------------------------------------
    // ПЕРЕВІРКА ЗАВДАННЯ 1
    // --------------------------------------------------------------------------
    std::cout << "--- Перевірка завдання 1 (get_max) ---\n";
    std::cout << "Максимум int (5, 10): " << MyNamespace::get_max(5, 10) << "\n";
    std::cout << "Максимум double (5.7, 2.3): " << MyNamespace::get_max(5.7, 2.3) << "\n";

    // Відповідь на питання "Чи запрацює вона для рядків?":
    // Так, запрацює за замовчуванням, оскільки для std::string оператор > перевантажений лексикографічно.
    std::string s1 = "Apple", s2 = "Banana";
    std::cout << "Максимум std::string (Apple, Banana): " << MyNamespace::get_max(s1, s2) << "\n";

    // Перевірка для типу Раціональний дріб
    MyNamespace::Rational r1(1, 2), r2(3, 4); 
    std::cout << "Максимум Rational (1/2, 3/4): " << MyNamespace::get_max(r1, r2) << "\n\n";

    // --------------------------------------------------------------------------
    // ПЕРЕВІРКА ЗАВДАННЯ 2
    // --------------------------------------------------------------------------
    std::cout << "--- Перевірка завдання 2 (Стек та введення до 0) ---\n";
    
    MyNamespace::Stack<int> custom_int_stack;
    std::cout << "Введіть цілі числа (введіть 0 для завершення):\n";
    int count_ints = MyNamespace::read_into_custom_stack(custom_int_stack);
    
    std::cout << "Кількість введених елементів: " << count_ints << "\n";
    std::cout << "Елементи з власного Стеку (в зворотному порядку): ";
    while (!custom_int_stack.empty()) {
        std::cout << custom_int_stack.top() << " ";
        custom_int_stack.pop();
    }
    std::cout << "\n\n";

    // Перевірка роботи за допомогою стандартного класу std::stack з STL (для типу double)
    std::stack<double> stl_double_stack;
    std::cout << "Введіть дійсні числа double (введіть 0 для завершення):\n";
    int count_doubles = MyNamespace::read_into_stl_stack(stl_double_stack);
    
    std::cout << "Кількість введених елементів: " << count_doubles << "\n";
    std::cout << "Елементи зі стандартного std::stack: ";
    while (!stl_double_stack.empty()) {
        std::cout << stl_double_stack.top() << " ";
        stl_double_stack.pop();
    }
    std::cout << "\n";

    return 0;
}