#include <stdio.h>

struct Point {
    double x;
    double y;
};

struct Rectangle {
    struct Point p1;
    struct Point p2;
};

void inputRectangle(struct Rectangle *r) {
    printf("Введіть x та y першої вершини: ");
    scanf("%lf %lf", &r->p1.x, &r->p1.y);
    printf("Введіть x та y другої вершини: ");
    scanf("%lf %lf", &r->p2.x, &r->p2.y);
}

void outputRectangle(struct Rectangle r) {
    printf("Прямокутник заданий точками: (%.2f, %.2f) та (%.2f, %.2f)\n", 
           r.p1.x, r.p1.y, r.p2.x, r.p2.y);
}

int main() {
    struct Rectangle rect;
    inputRectangle(&rect);
    outputRectangle(rect);
    return 0;
}