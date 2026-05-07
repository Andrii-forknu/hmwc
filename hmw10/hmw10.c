#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ==========================================================
// СТРУКТУРИ ТА ФУНКЦІЇ ДЛЯ ЗАВДАННЯ 10.6.б (ЧАС)
// ==========================================================

typedef struct {
    int hours;
    int minutes;
    int seconds;
} Time;

void inputTime(Time *t) {
    printf("Введіть час (години хвилини секунди): ");
    scanf("%d %d %d", &t->hours, &t->minutes, &t->seconds);
}

void printTime(Time t) {
    printf("Поточний час: %02d:%02d:%02d\n", t.hours, t.minutes, t.seconds);
}

void solve_Task_10_6() {
    printf("\n--- Виконання завдання 10.6.б (Час) ---\n");
    Time t;
    inputTime(&t);
    printTime(t);
}

// ==========================================================
// СТРУКТУРИ ТА ФУНКЦІЇ ДЛЯ ЗАВДАННЯ 10.16.б, в (СТУДЕНТИ)
// ==========================================================

typedef struct {
    char surname[50];
    int group;
    int grades[3]; // Оцінка_1, Оцінка_2, Оцінка_3
} Student;

// б) Пошук предмета, складеного найгірше
void findWorstSubject(Student *students, int n) {
    double total_scores[3] = {0, 0, 0};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            total_scores[j] += students[i].grades[j];
        }
    }

    int worstIdx = 0;
    for (int j = 1; j < 3; j++) {
        if (total_scores[j] < total_scores[worstIdx]) {
            worstIdx = j;
        }
    }

    printf("\n[Результат б]: Предмет №%d складено найгірше (середній бал: %.2f)\n", 
           worstIdx + 1, total_scores[worstIdx] / n);
}

// в) Пошук студентів, що склали все вище за задану оцінку
void findHighAchievers(Student *students, int n) {
    int threshold;
    printf("\nВведіть порогову оцінку для пошуку (всі оцінки мають бути вище неї): ");
    scanf("%d", &threshold);

    printf("Студенти, які склали всі іспити вище ніж %d:\n", threshold);
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (students[i].grades[0] > threshold && 
            students[i].grades[1] > threshold && 
            students[i].grades[2] > threshold) {
            printf("- %s (Група: %d)\n", students[i].surname, students[i].group);
            found = 1;
        }
    }
    if (!found) printf("Таких студентів не знайдено.\n");
}

void solve_Task_10_16() {
    int n;
    printf("\n--- Виконання завдання 10.16 (Студенти) ---\n");
    printf("Введіть кількість студентів (N): ");
    scanf("%d", &n);

    // Динамічне виділення пам'яті для масиву структур
    Student *students = (Student*)malloc(n * sizeof(Student));
    if (!students) return;

    for (int i = 0; i < n; i++) {
        printf("Студент %d (Прізвище Група Оцінка1 Оцінка2 Оцінка3): ", i + 1);
        scanf("%s %d %d %d %d", students[i].surname, &students[i].group, 
              &students[i].grades[0], &students[i].grades[1], &students[i].grades[2]);
    }

    findWorstSubject(students, n);
    findHighAchievers(students, n);

    free(students);
}

// ==========================================================
// ГОЛОВНА ФУНКЦІЯ (МЕНЮ)
// ==========================================================

int main() {
    int choice;
    while (1) {
        printf("\n========== ГОЛОВНЕ МЕНЮ ==========\n");
        printf("1. Завдання 10.6.б (Час: ввід/вивід)\n");
        printf("2. Завдання 10.16.б,в (Студенти: пошук)\n");
        printf("0. Вихід\n");
        printf("Ваш вибір: ");
        
        if (scanf("%d", &choice) != 1) break;
        if (choice == 0) break;

        switch (choice) {
            case 1:
                solve_Task_10_6();
                break;
            case 2:
                solve_Task_10_16();
                break;
            default:
                printf("Невірний вибір. Спробуйте ще раз.\n");
        }
    }

    printf("Програму завершено.\n");
    return 0;
}