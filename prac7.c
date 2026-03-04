#include <stdio.h>
void task1(){
    int arr1[5] = {1, 2, 3, 4, 5};
    int counter = 0;
    float x;
    printf("Введіть число: ");
    scanf("%f", &x);
    for (int i = 0; i < 5; i++) {
    if (arr1[i] < x) {
        counter++;
    }
}
    
printf("Кількість елементів менших за %.2f: %d\n", x, counter);

}
void task2(){
    int arr2[4] = {5, 112, 4, 3};
    for(int i = 3; i >= 0; i--){
        printf("%d ", arr2[i]);
    }  
}
void task3(){
    double arr3[10] = {0,0,0,0,0,0,0,0,0,0};
    for(int i = 0; i < 10; i++){
        printf("Введіть число: ");
        scanf("%lf", &arr3[i]);

    }
    printf("Ви ввели: ");
    for(int i = 0; i < 10; i++){
        
         printf("%2.2f ", arr3[i]);

    }

}
void findMax(double arr[], int len){
    double max = arr[0];
    for(int i = 1; i < len; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    printf("Максимальне значення: %2.2f\n", max);

}
void task4(){
    double arr4[5] = {0,0,0,0,0,};
    for(int i = 0; i < 5; i++){
        printf("Введіть число: ");
        scanf("%lf", &arr4[i]);

    }
    findMax(arr4, 5);
}
void task5(){
    int odd_counter = 0;
    int even_counter = 0;
    double arr5[50] = {};
    for(int i = 0; i < 50; i++){
        printf("Введіть число: ");
        scanf("%lf", &arr5[i]);
        if (arr5[i] == 0) {
            break;
        }
        if((int)arr5[i] % 2 == 0){
            even_counter++;
        } else {
            odd_counter++;
        }

    }
printf("Кількість парних чисел: %d\n", even_counter);
printf("Кількість непарних чисел: %d\n", odd_counter);
}

#define MAX_SIZE 20

void input_vector(double vec[], int n) {
    printf("Введіть %d елементів вектора:\n", n);
    for (int i = 0; i < n; i++) {
        printf("[%d] = ", i);
        scanf("%lf", &vec[i]); 
    }
}

void output_vector(double vec[], int n) {
    printf("(");
    for (int i = 0; i < n; i++) {
        printf("%.2f", vec[i]); 
        if (i < n - 1) printf(", ");
    }
    printf(")\n");
}

void add_vectors(double v1[], double v2[], double res[], int n) {
    for (int i = 0; i < n; i++) {
        res[i] = v1[i] + v2[i];
    }
}

double dot_product(double v1[], double v2[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += v1[i] * v2[i];
    }
    return sum;
}

int main() {
    int n;
    double vectorA[MAX_SIZE], vectorB[MAX_SIZE], vectorSum[MAX_SIZE];

    printf("Введіть розмірність векторів (n < 20): ");
    scanf("%d", &n);
    printf("\n--- Введення вектора A ---\n");
    input_vector(vectorA, n);

    printf("\n--- Введення вектора B ---\n");
    input_vector(vectorB, n);

    printf("\nВаші вектори:\n");
    printf("A: "); output_vector(vectorA, n);
    printf("B: "); output_vector(vectorB, n);

    add_vectors(vectorA, vectorB, vectorSum, n);
    printf("\nСума векторів (A + B): ");
    output_vector(vectorSum, n);

    double scalar = dot_product(vectorA, vectorB, n);
    printf("Скалярний добуток (A * B) = %.4f\n", scalar);

    return 0;
}