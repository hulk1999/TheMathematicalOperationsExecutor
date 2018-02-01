#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

// function abs() sucks
double absoluteVal(double num){
	if (num < 0) return - num;
	return num;
}

double getNum(){
	double num;
	scanf("%lf", &num);
	return num;
}

double y(double x, int degree, double a[100][100]){
	double result = 0;
	int i;
	for (i = 1; i <= degree + 1; i++) result += a[degree][i] * pow(x, degree - i + 1);
	return result;
}

double findSolution(int degree, double left, double right, double a[100][100]){
	
	double middle = (left + right) / 2;
	double yMiddle = y(middle, degree, a);
	double yLeft = y(left, degree, a);
	double yRight = y(right, degree, a);
	
	if (yMiddle * yLeft <= 0){
		if (absoluteVal(middle - left) < 0.0000000000001) return middle;
		return findSolution(degree, left, middle, a);
	}
	else{
		if (absoluteVal(middle - right) < 0.0000000000001) return middle;
		return findSolution(degree, middle, right, a);		
	}
}

void solveNthDegreeEquation(int num){
	
	double a[100][100]; // a stores the coefficents
	int i, j;
			
	// get coefficients
	for (i = 1; i <= num + 1; i++) a[num][i] = getNum();
	
	// derivatives
	for (i = num - 1; i >= 1; i--)
		for (j = 1; j <= i + 1; j++)
			a[i][j] = a[i + 1][j] * (i - j + 2);
	
	// solve
	double solution[100][100];
	int step = 1000, start, end, solutionNum[100];
	for (i = 0; i <= num; i++) solutionNum[i] = 0;
	for (i = 1; i <= num; i++){
		
		// start stores the status of y when x -> - infinity; end when x -> + infinity
		// start & end = 1 if y -> + infinity; -1 otherwise
		start = 1; end = 1;
		if (((i % 2 == 0) && (a[i][1] < 0)) || ((i % 2 == 1) && (a[i][1] > 0))) start = -1;
		if (((i % 2 == 0) && (a[i][1] < 0)) || ((i % 2 == 1) && (a[i][1] < 0))) end = -1;
	
		// if current equation has no extremum, make pseudo-extremum when x = 0
		if (solutionNum[i - 1] == 0){
			solutionNum[i - 1] = 1;
			solution[i - 1][1] = 0;
		}
		
		// make left pseudo-extremum
		solution[i - 1][0] = solution[i - 1][1];
		while (y(solution[i - 1][0], i, a) * start < 0)
			solution[i - 1][0] -= step;
		
		// make right pseudo-extremum
		solution[i - 1][solutionNum[i - 1] + 1] = solution[i - 1][solutionNum[i - 1]];
		while (y(solution[i - 1][solutionNum[i - 1] + 1], i, a) * end < 0)
			solution[i - 1][solutionNum[i - 1] + 1] += step;
		
		// find solutions
		for (j = 0; j <= solutionNum[i - 1]; j++){
			if ((y(solution[i - 1][j], i, a) == 0) && (j > 0)){
				solutionNum[i]++;
				solution[i][solutionNum[i]] = solution[i - 1][j];
				if (absoluteVal(solution[i][solutionNum[i]] - solution[i][solutionNum[i] - 1]) < 0.00001) solutionNum[i]--;
			}
			if (y(solution[i - 1][j], i, a) * y(solution[i - 1][j + 1], i, a) < 0){
				solutionNum[i]++;
				solution[i][solutionNum[i]] = findSolution(i, solution[i - 1][j], solution[i - 1][j + 1], a);
				if (absoluteVal(solution[i][solutionNum[i]] - solution[i][solutionNum[i] - 1]) < 0.00001) solutionNum[i]--;
			}
		}
	}
	// print out
	if (solutionNum[num] == 0) printf("No solution");
	else for (i = 1; i <= solutionNum[num]; i++) printf("%8.2lf", solution[num][i]);
}

int main(){
	solveNthDegreeEquation(3);
	return 0;
}
