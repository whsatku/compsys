#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 100

int A[N][N], B[N][N], C[N][N];

void initialize(int matrix[N][N]){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			matrix[i][j] = rand() % 100;
		}
	}
}

void print_matrix(int matrix[N][N]){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
}

void mul(int a[N][N], int b[N][N], int out[N][N]){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			int sum = 0;

			for(int k = 0; k < N; k++){
				sum += a[i][k] * b[k][j];
			}

			out[i][j] = sum;
		}
	}
}

int main(){
	srand(time(NULL));

	initialize(A);
	initialize(B);

	mul(A, B, C);

	print_matrix(A);
	printf("\n");
	print_matrix(B);
	printf("\n");
	print_matrix(C);

	return 0;
}