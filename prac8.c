#include <stdio.h>

#define MAX_SIZE 25

void input_matrix(double matrix[MAX_SIZE][MAX_SIZE], int m, int n) {
    printf("Введіть елементи матриці %dx%d по одному:\n", m, n);
    
    for (int i = 0; i < m; i++) {
        printf("Рядок [%d]: ", i);
        for (int j = 0; j < n; j++) {
            
            scanf("%lf", &matrix[i][j]);
        }
    }
}
void print_matrix(double matrix[MAX_SIZE][MAX_SIZE], int m, int n) {
        for(int i = 0; i < m; i++) {
            for(int j = 0; j <  n; j++){
                printf("%lf ",  matrix[i][j]);
            }
            printf("\n");
        }
}
void transpose1(double matrix[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {

            double temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
}
 void transpose2(double matrix_in[MAX_SIZE][MAX_SIZE], double matrix_out[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix_out[i][j] = matrix_in[j][i];
        }
    }
}
double finder(double matrix[MAX_SIZE][MAX_SIZE], int k, int m, int n){
    int result = 0;
    for(int i = 0; i < m; i++) {
        int j = i-k;
        if((j<n)&&(j>=0)) {
              result += matrix[i][j];
        }
    }
    return result;
}
int main(){
   double matrix[MAX_SIZE][MAX_SIZE];
    int n, m;
    printf("Введіть розміри матриці\n");
    scanf("%d", &n);
    scanf("%d", &m);
    //double matrixT[MAX_SIZE][MAX_SIZE] = {{1,2}, {3,4}};
    //double matrixT_out[MAX_SIZE][MAX_SIZE];
    //int size = 4;
    input_matrix(matrix, m , n);
    print_matrix(matrix, m , n);
    //transpose2(matrixT, matrixT_out, size);
    //print_matrix(matrixT_out, size, size);
    double y = finder(matrix, 1, m, n);
    printf("%lf", y);
    
}