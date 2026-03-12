#include <stdio.h>
#include <math.h>

// --- Допоміжні функції для задачі 6 ---
double get_distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

double get_triangle_area(double a, double b, double c) {
    double p = (a + b + c) / 2.0;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

// --- Задачі ---

void task1() {
    printf("\n--- Задача 1: Косинус ---\n");
    double x;
    printf("Введіть x (в радіанах): ");
    scanf("%lf", &x);
    printf("cos(%g) = %f\n", x, cos(x));
}

void task2() {
    printf("\n--- Задача 2: Гіпотенуза ---\n");
    double a, b;
    printf("Введіть катети a та b: ");
    scanf("%lf %lf", &a, &b);
    double c = sqrt(a * a + b * b);
    printf("Гіпотенуза c = %.2f\n", c);
}

void task3() {
    printf("\n--- Задача 3: Площа за 3 сторонами ---\n");
    double a, b, c;
    printf("Введіть сторони a, b, c: ");
    scanf("%lf %lf %lf", &a, &b, &c);
    if (a + b > c && a + c > b && b + c > a) {
        printf("Площа S = %.2f\n", get_triangle_area(a, b, c));
    } else {
        printf("Трикутник із такими сторонами не існує.\n");
    }
}

void task4() {
    printf("\n--- Задача 4: Оптимізовані многочлени ---\n");
    double x;
    printf("Введіть x: ");
    scanf("%lf", &x);

    // а) y = x^4 + 2x^2 + 1 = (x^2 + 1)^2
    double x2 = x * x;
    double res_a = pow(x2 + 1, 2);
    
    // б) y = x^4 + x^3 + x^2 + x + 1 (Схема Горнера)
    double res_b = (((x + 1) * x + 1) * x + 1) * x + 1;

    // в) y = (x + 1)^5
    double res_v = pow(x + 1, 5);

    // г) y = x^9 + x^3 + 1
    double x3 = x * x * x;
    double res_g = x3 * x3 * x3 + x3 + 1;

    // д) y = 16x^4 + 8x^3 + 4x^2 + 2x + 1
    double res_d = (((16 * x + 8) * x + 4) * x + 2) * x + 1;

    // е) y = x^5 + x^3 + x
    double res_e = ((x2 + 1) * x2 + 1) * x;

    printf("a) %g; b) %g; v) %g; g) %g; d) %g; e) %g\n", 
            res_a, res_b, res_v, res_g, res_d, res_e);
}

void task5() {
    printf("\n--- Задача 5: Функція Розенброка ---\n");
    double rosenbrock(double x, double y) {
        return 100 * pow(x * x - y, 2) + pow(x - 1, 2);
    };

    double pairs[3][2] = {{1, 1}, {0, 0}, {1.2, 1.5}};
    for (int i = 0; i < 3; i++) {
        double x = pairs[i][0], y = pairs[i][1];
        printf("f(%g, %g) = %f\n", x, y, rosenbrock(x, y));
    }
}

void task6() {
    printf("\n--- Задача 6: Площа за координатами ---\n");
    double x1, y1, x2, y2, x3, y3;
    
    printf("Введіть координати точки A (x y): ");
    scanf("%lf %lf", &x1, &y1);
    
    // Пропуск рядка реалізується логікою вводу користувачем або getchar()
    printf("Введіть координати точки B (x y): ");
    scanf("%lf %lf", &x2, &y2);
    
    printf("Введіть координати точки C (x y): ");
    scanf("%lf %lf", &x3, &y3);

    double a = get_distance(x1, y1, x2, y2);
    double b = get_distance(x2, y2, x3, y3);
    double c = get_distance(x3, y3, x1, y1);

    printf("Площа трикутника: %.2f\n", get_triangle_area(a, b, c));
}

int main() {
    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    return 0;
}