#include <iostream>
#include <string>
#include <vector>
#include <cctype>

// Функція для пошуку найдовших слів у реченні
std::vector<std::string> getLongestWords(const std::string& sentence) {
    std::vector<std::string> longest_words;
    std::string current_word = "";
    size_t max_length = 0;

    // Лямбда-функція для обробки знайденого слова (щоб не дублювати код)
    auto processWord = [&](const std::string& word) {
        if (word.length() > max_length) {
            // Знайшли нове найдовше слово — оновлюємо максимум і очищаємо масив
            max_length = word.length();
            longest_words.clear();
            longest_words.push_back(word);
        } else if (word.length() == max_length && max_length > 0) {
            // Знайшли слово такої ж максимальної довжини — додаємо до масиву
            longest_words.push_back(word);
        }
    };

    // Проходимо по кожному символу речення
    for (char c : sentence) {
        // isalpha перевіряє, чи є символ літерою (ігнорує пробіли, коми, крапки тощо)
        if (std::isalpha(static_cast<unsigned char>(c))) {
            current_word += c;
        } else {
            // Якщо символ не літера, значить слово закінчилося
            if (!current_word.empty()) {
                processWord(current_word);
                current_word.clear(); // Очищаємо для наступного слова
            }
        }
    }
    
    // Перевіряємо останнє слово, якщо речення закінчилося літерою (без крапки/пробілу)
    if (!current_word.empty()) {
        processWord(current_word);
    }

    return longest_words;
}

int main() {
    // Тестовий рядок (містить два слова довжиною 10 літер: "dictionary" та "programmer")
    std::string text = "A good dictionary is essential for every programmer, absolutely!";
    
    std::cout << "Оригінальне речення: " << text << "\n\n";

    // Отримуємо масив найдовших слів
    std::vector<std::string> result = getLongestWords(text);

    // Виведення результату
    if (result.empty()) {
        std::cout << "У реченні не знайдено латинських слів.\n";
    } else {
        std::cout << "Найдовше слово (або слова) має довжину " << result[0].length() << " літер:\n";
        for (const std::string& word : result) {
            std::cout << "- " << word << "\n";
        }
    }

    return 0;
}