#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Point {
private:
    double x, y;
    static int count; // статичний лічильник

public:
    Point(double x = 0, double y = 0) {
        this->x = x;
        this->y = y;
        count++;
    }

    static int counter() {
        return count;
    }

    double getX() const { return x; }
    double getY() const { return y; }
};

// ініціалізація статичного члена
int Point::count = 0;

// функція для обчислення відстані між двома точками
double distance(const Point& a, const Point& b) {
    return sqrt(pow(a.getX() - b.getX(), 2) +
                pow(a.getY() - b.getY(), 2));
}

int main() {
    vector<Point> polygon;
    char answer;

    do {
        double x, y;
        cout << "Введiть координати точки (x y): ";
        cin >> x >> y;

        polygon.push_back(Point(x, y));

        cout << "Ввести вершину? (y/n): ";
        cin >> answer;

    } while (answer == 'y' || answer == 'Y');

    int n = Point::counter();
    cout << "Кiлькiсть вершин: " << n << endl;

    if (n < 3) {
        cout << "Недостатньо точок для багатокутника." << endl;
        return 0;
    }

    double perimeter = 0;

    for (int i = 0; i < n - 1; i++) {
        perimeter += distance(polygon[i], polygon[i + 1]);
    }

    // замикання багатокутника
    perimeter += distance(polygon[n - 1], polygon[0]);

    cout << "Периметр багатокутника: " << perimeter << endl;

    return 0;
}