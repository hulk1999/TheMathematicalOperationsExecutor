#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

double getNum(){
	double num;
	scanf("%lf", &num);
	return num;
}

void solveNthDegreeEquation(int num){
	
	int i, a[50][50]; // a stores the coefficents
	for (i = 1; i <= num + 1; i++) a[num][i] = getNum();
	
	for (i = num - 1; i >= 1; i--)
		for (j = 1; j <= i + 1; j++){
			a[j][i] = a[j][i+1] * (i - j + 1);
		}
		
	int criticalPoint = 0, step = 1000, start, end;
	for (i = 1; i <= num; i++){
		start = 1; end = 1;
		if (((i % 2 == 0) && (a[1][i] < 0)) || ((i % 2 == 1) && (a[1][i] > 0))) start = -1;
		if (((i % 2 == 0) && (a[1][i] < 0)) || ((i % 2 == 1) && (a[1][i] < 0))) end = -1;
		
	}
}
