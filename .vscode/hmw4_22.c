#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, count = 0;

    printf("Введіть кількість чисел n: ");
    if (scanf("%d", &n) != 1 || n < 3) {
        printf("Для порівняння з обома сусідами потрібно мінімум 3 числа.\n");
        return 0;
    }
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Помилка пам'яті.\n");
        return 1;
    }

    printf("Введіть %d цілих чисел:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    for (int i = 1; i < n - 1; i++) {
        if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) {
            count++;
        }
    }

    printf("Кількість чисел, більших за своїх сусідів: %d\n", count);

    free(arr); 
    return 0;
}