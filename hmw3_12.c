#include <stdio.h>

void classify_triangle(double a, double b, double c) {
    if (a + b <= c || a + c <= b || b + c <= a) {
        printf("Трикутник із сторонами %.2f, %.2f, %.2f не існує.\n", a, b, c);
        return;
    }

    double a2 = a * a;
    double b2 = b * b;
    double c2 = c * c;

    if (a2 + b2 == c2 || a2 + c2 == b2 || b2 + c2 == a2) {
        printf("Трикутник прямокутний.\n");
    } else if (a2 + b2 < c2 || a2 + c2 < b2 || b2 + c2 < a2) {
        printf("Трикутник тупокутний.\n");
    } else {
        printf("Трикутник гострокутний.\n");
    }
}
int main() {
    double a, b, c;

    printf("Введіть довжини сторін трикутника (a, b, c): ");
    scanf("%lf %lf %lf", &a, &b, &c);

    classify_triangle(a, b, c);

    return 0;
}