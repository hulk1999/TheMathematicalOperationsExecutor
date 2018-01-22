#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

double getNum(){
	double num;
	scanf("%lf", &num);
	return num;
}

void showArray(int num, double a[50][50]){
	int x, y;
	for (y = 1; y <= num; y++){
		for (x = 1; x <= num + 1; x++) printf("%20.2lf", a[x][y]);
		printf("\n");
	}
}

void getInput(int num, double a[50][50]){
	int x, y;
	for (y = 1; y <= num; y++)
	for (x = 1; x <= num + 1; x++)
		a[x][y] = getNum();
}

int hasSolution(int num, double a[50][50]){
	int i;
	for (i = 1; i <= num; i++) if (a[i][i] == 0) return 0;
	return 1;
}

int solveSetOfEquations(int num){
	
	double a[50][50];
	int i, j, k;
	double ratio;
	
	getInput(num, a);
	
	for (i = 1; i < num; i++){
		for (j = i + 1; j <= num; j++){
			ratio = - a[i][j] / a[i][i];
			for (k = i; k <= num + 1; k++)
				a[k][j] += a[k][i] * ratio;
		}
	}
	
	if (!(hasSolution(num, a))) return 0;
	
	double solution[50];
	solution[num] = a[num + 1][num] / a[num][num];
	for (i = num; i >= 1; i--){
		for (j = num; j >= i + 1; j--) a[num + 1][i] -= a[j][i] * solution[j];
		solution[i] = a[num + 1][i] / a[i][i];
	}
	
	for (i = 1; i <= num; i++) printf("%10.2lf", solution[i]);
	
	return 1;
}

int main(){
	solveSetOfEquations(3);
	return 0;
}
