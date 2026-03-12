#include <stdio.h>
#include <stdlib.h>

void task_21() {
    printf("\n--- Задача 21: Мінімальні елементи у перший рядок ---\n");
    int n, m;
    printf("Введіть кількість рядків (n) та стовпців (m): ");
    if (scanf("%d %d", &n, &m) != 2) return;

    // Динамічне виділення пам'яті для матриці
    double **matrix = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double *)malloc(m * sizeof(double));
    }

    printf("Введіть елементи матриці %dx%d:\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }

    // Алгоритм переміщення мінімумів
    for (int j = 0; j < m; j++) {
        int min_row_idx = 0;
        // Шукаємо індекс рядка з мінімальним елементом у поточному стовпці j
        for (int i = 1; i < n; i++) {
            if (matrix[i][j] < matrix[min_row_idx][j]) {
                min_row_idx = i;
            }
        }

        // Якщо мінімум не в першому рядку (індекс 0), міняємо їх місцями
        if (min_row_idx != 0) {
            double temp = matrix[0][j];
            matrix[0][j] = matrix[min_row_idx][j];
            matrix[min_row_idx][j] = temp;
        }
    }

    printf("\nОброблена матриця (мінімуми стовпців у першому рядку):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%8.2f ", matrix[i][j]);
        }
        printf("\n");
    }

    // Звільнення пам'яті
    for (int i = 0; i < n; i++) free(matrix[i]);
    free(matrix);
}

int main() {
    task_21();
    return 0;
}