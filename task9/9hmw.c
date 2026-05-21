#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define EPS 1e-9

// =====================================================================
// ЗАВДАННЯ 9.5: ДЕТЕРМІНАНТ ТА РАНГ (Цілі числа)
// =====================================================================

int** allocate_matrix_int(int rows, int cols) {
    int **matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    return matrix;
}

void free_matrix_int(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) free(matrix[i]);
    free(matrix);
}

void solve_9_5() {
    int n, m;
    printf("\n--- Задача 9.5: Ранг та детермінант ---\n");
    printf("Введіть розміри матриці (рядки стовпці): ");
    scanf("%d %d", &n, &m);

    int **mat = allocate_matrix_int(n, m);
    printf("Введіть елементи матриці:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) scanf("%d", &mat[i][j]);

    // Для обчислень переводимо в double (метод Гаусса)
    double **temp = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        temp[i] = (double*)malloc(m * sizeof(double));
        for (int j = 0; j < m; j++) temp[i][j] = (double)mat[i][j];
    }

    double det = (n == m) ? 1.0 : 0.0;
    int rank = 0;
    int row = 0;

    for (int col = 0; col < m && row < n; col++) {
        int pivot = row;
        for (int i = row + 1; i < n; i++)
            if (fabs(temp[i][col]) > fabs(temp[pivot][col])) pivot = i;

        if (fabs(temp[pivot][col]) < EPS) {
            det = 0;
            continue;
        }

        // Міняємо рядки
        double *ptr = temp[pivot]; temp[pivot] = temp[row]; temp[row] = ptr;
        if (pivot != row) det = -det;
        
        det *= temp[row][col];
        rank++;

        for (int i = 0; i < n; i++) {
            if (i != row) {
                double factor = temp[i][col] / temp[row][col];
                for (int j = col; j < m; j++) temp[i][j] -= factor * temp[row][col];
            }
        }
        row++;
    }

    if (n == m) printf("Детермінант: %.2lf\n", det);
    else printf("Матриця не квадратна, детермінант не визначений.\n");
    printf("Ранг матриці: %d\n", rank);

    for (int i = 0; i < n; i++) free(temp[i]);
    free(temp);
    free_matrix_int(mat, n);
}

// =====================================================================
// ЗАВДАННЯ 9.9.д: ДОДАВАННЯ РЯДКА В ПОЧАТОК (Дійсні числа)
// =====================================================================

double** allocate_matrix_double(int rows, int cols) {
    double **matrix = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (double*)malloc(cols * sizeof(double));
        for (int j = 0; j < cols; j++) matrix[i][j] = (rand() % 100) / 10.0;
    }
    return matrix;
}

void print_matrix_double(double **mat, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) printf("%6.2lf ", mat[i][j]);
        printf("\n");
    }
}

// Функція для пункту (д): Додати рядок в початок
double** add_row_at_beginning(double **mat, int *rows, int cols) {
    int n = *rows;
    // 1. Перевиділяємо пам'ять для масиву вказівників (на 1 більше)
    double **new_mat = (double**)realloc(mat, (n + 1) * sizeof(double*));
    if (!new_mat) return mat;

    // 2. Зсуваємо всі існуючі рядки вниз
    for (int i = n; i > 0; i--) {
        new_mat[i] = new_mat[i - 1];
    }

    // 3. Виділяємо пам'ять для нового нульового рядка
    new_mat[0] = (double*)malloc(cols * sizeof(double));
    printf("Введіть %d елементів для нового першого рядка: ", cols);
    for (int j = 0; j < cols; j++) scanf("%lf", &new_mat[0][j]);

    (*rows)++;
    return new_mat;
}

void solve_9_9_d() {
    int n, m;
    printf("\n--- Задача 9.9.д: Додавання рядка в початок ---\n");
    printf("Початкові розміри (N M): ");
    scanf("%d %d", &n, &m);

    srand(time(NULL));
    double **mat = allocate_matrix_double(n, m);

    printf("Початкова матриця:\n");
    print_matrix_double(mat, n, m);

    mat = add_row_at_beginning(mat, &n, m);

    printf("Оновлена матриця:\n");
    print_matrix_double(mat, n, m);

    for (int i = 0; i < n; i++) free(mat[i]);
    free(mat);
}

// =====================================================================
int main() {
    int choice;
    do {
        printf("\nВиберіть задачу:\n1. 9.5 (Детермінант/Ранг)\n2. 9.9.д (Додати рядок в початок)\n0. Вихід\nВаш вибір: ");
        scanf("%d", &choice);
        if (choice == 1) solve_9_5();
        else if (choice == 2) solve_9_9_d();
    } while (choice != 0);

    return 0;
}