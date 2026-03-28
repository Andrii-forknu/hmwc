#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846
#define M_E  2.71828182845904523536

void task1() {
    printf("--- Задача 1 ---\n");
    printf("2 + 31 = %d\n", 2 + 31);
    printf("45 * 54 - 11 = %d\n", 45 * 54 - 11);
    printf("15 / 4 = %d\n", 15 / 4);
    printf("15.0 / 4 = %.1f\n", 15.0 / 4);
    printf("67 %% 5 = %d\n", 67 % 5);
    printf("(2 * 45.1 + 3.2) / 2 = %.2f\n\n", (2 * 45.1 + 3.2) / 2);
}

void task2() {
    printf("--- Задача 2 ---\n");
    float f1 = 1e-4f;
    double d2 = 24.33e5;
    double d3 = M_PI;
    double d4 = M_E;
    double d5 = sqrt(5);
    long double ld6 = log(100);

    printf("10^-4: %.2f\n", f1);
    printf("24.33E5: %.2f\n", d2);
    printf("pi: %.2f\n", d3);
    printf("e: %.2f\n", d4);
    printf("sqrt(5): %.2f\n", d5);
    printf("ln(100): %.2Lf\n\n", ld6);
}

void task3() {
    printf("--- Задача 3 ---\n");
    int a;
    printf("Введіть цифру a: ");
    scanf("%d", &a);
    printf("- %d - %d - %d\n", a, a, a);
    printf("%d | %d | %d\n", a, a, a);
    printf("- %d - %d - %d\n\n", a, a, a);
}

void task4() {
    printf("--- Задача 4 ---\n");
    double m1 = 5.972e24; 
    double m2 = 7.347e22; 
    double r = 3.844e8;   
    double gamma = 6.673e-11;
    double F = gamma * (m1 * m2) / (r * r);
    printf("F=%e\n\n", F);
}

void task5() {
    printf("--- Задача 5 ---\n");
    double x;
    printf("Введіть дійсне число x: ");
    scanf("%le", &x);

    double x2 = x * x;
    double x4 = x2 * x2;
    printf("a) x^4 = %g\n", x4);

    
    double x3 = x2 * x;
    double x6 = x3 * x3;
    printf("b) x^6 = %g\n", x6);

    
    double x9 = x6 * x3;
    printf("v) x^9 = %g\n", x9);

    double x5 = x3 * x2;
    double x10 = x5 * x5;
    double x15 = x10 * x5;
    printf("g) x^15 = %g\n", x15);

    
    double x7 = x4 * x2 * x;
    double x14 = x7 * x7;
    double x28 = x14 * x14;
    printf("d) x^28 = %g\n", x28);

    
    double r2 = x * x;
    double r4 = r2 * r2;
    double r8 = r4 * r4;
    double r16 = r8 * r8;
    double r32 = r16 * r16;
    double r64 = r32 * r32;
    printf("e) x^64 = %g\n\n", r64);
}

void task6() {
    printf("--- Задача 6 ---\n");
    double C;
    printf("Введіть температуру в Цельсіях (C): ");
    scanf("%lf", &C);
    double F = 9.0 * C / 5.0 + 32.0;
    printf("F=%g\n\n", F);
}

void task7() {
    printf("--- Задача 7 ---\n");
    double x;
    printf("Введіть x: ");
    scanf("%lf", &x);

    // Без math.h
    int int_part = (int)x;
    double frac_part = x - int_part;
    
    // З math.h
    double i_part, f_part;
    f_part = modf(x, &i_part);

    printf("Ціла частина: %d (без), %.0f (з)\n", int_part, i_part);
    printf("Дробова частина: %f (без), %f (з)\n", frac_part, f_part);
    printf("Найменше ціле >= x (ceil): %.0f\n", ceil(x));
    printf("Найбільше ціле <= x (floor): %.0f\n", floor(x));
    printf("Округлене значення (round): %.0f\n\n", round(x));
}

void task8() {
    printf("--- Задача 8 ---\n");
    double a, b;
    printf("Введіть перше число:\n");
    scanf("%lf", &a);
    printf("Введіть друге число:\n");
    scanf("%lf", &b);
    printf("Різниця: %.4f\n", a - b);
    printf("Добуток: %.4f\n\n", a * b);
}

void task9() {
    printf("--- Задача 9 ---\n");
    double a, b;
    printf("Введіть два числа через пробіл: ");
    scanf("%lf %lf", &a, &b);
    double avg = (a + b) / 2.0;
    double harmonic = 2.0 / (1.0 / a + 1.0 / b);
    printf("Середнє арифметичне: %f (наук: %e)\n", avg, avg);
    printf("Середнє гармонійне: %f (наук: %e)\n", harmonic, harmonic);
}

int main() {
   
    
    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    task7();
    task8();
    task9();

    return 0;
}