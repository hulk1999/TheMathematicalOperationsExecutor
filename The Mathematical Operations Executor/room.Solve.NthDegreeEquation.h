//-----------------------------------------------declaration------------------------------------------------------------------//

// functions for creating interface
void highlightSolveNthDegreeEquation(int x0, int y0, int x0S, int x, int degree, double solution[100][100], int secondColor);
void unhighlightSolveNthDegreeEquation(int x0, int y0, int x0S, int x, int degree, double solution[100][100], int firstColor);

// get coefiicents
void getCoefficientDegree(int x0, int y0, int x, int degree, double a[100][100], int firstColor, int secondColor);

// functions for solving
double y(double x, int degree, double a[100][100]);
double findSolution(int degree, double left, double right, double a[100][100]);
void solveNthDegreeEquation(int num, int firstColor, int secondColor);

//----------------------------------------------------------------------------------------------------------------------------//

// function abs() doesn't work for double
double absoluteVal(double num){
	if (num < 0) return - num;
	return num;
}

// get coefiicents
void getCoefficientDegree(int x0, int y0, int x, int degree, double a[100][100], int firstColor, int secondColor){
	textColor(secondColor);
	int isNum;
	char isEnter;
	do{
		goToXY(x0 + 15 + min2Int(x - 1, 3)*15, y0 + 6); printf("           ");
		goToXY(x0 + 19 + min2Int(x - 1, 3)*15, y0 + 6);
		fflush(stdin);
		isNum = scanf("%lf", &a[degree][x]);
		scanf("%c", &isEnter);
	} while (((isNum != 1) || (isEnter != '\n')) || ((x == 1) && (a[degree][x] == 0)));
	textColor(firstColor);
}

// highlight current part
void highlightSolveNthDegreeEquation(int x0, int y0, int x0S, int x, int degree, double solution[100][100], int secondColor){
	textColor(secondColor);
	goToXY(x0 + 15 + (x - x0S)*15, y0 + 13); printf("           ");
	goToXY(x0 + 15 + (x - x0S)*15, y0 + 13); printf("%9.4lf", solution[degree][x]);
	goToXY(119, 29);
}

// unhighlight current part
void unhighlightSolveNthDegreeEquation(int x0, int y0, int x0S, int x, int degree, double solution[100][100], int firstColor){
	textColor(firstColor);
	goToXY(x0 + 15 + (x - x0S)*15, y0 + 13); printf("           ");
	goToXY(x0 + 15 + (x - x0S)*15, y0 + 13); printf("%9.4lf", solution[degree][x]);
}

// get value of y = f(x)
double y(double x, int degree, double a[100][100]){
	double result = 0;
	int i;
	for (i = 1; i <= degree + 1; i++) result += a[degree][i] * pow(x, degree - i + 1);
	return result;
}

// find solutions
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

// solve n-th degree equation
void solveNthDegreeEquation(int num, int firstColor, int secondColor){
	start: num = num;
	
	int x0 = 25, y0 = 10;
	goToXY(x0, y0);
	if (num == 1) printf("SOLVING 1ST DEGREE EQUATION");
	if (num == 2) printf("SOLVING 2ND DEGREE EQUATION");
	if (num > 2) printf("SOLVING %dTH DEGREE EQUATION", num);
	goToXY(x0, y0 + 2); printf("Input:");
	
	// get input
	double a[100][100];
	int i, j, k, m, x0C;
	for (i = 1; i <= num + 1; i++){
			
		// delete previous contents
		goToXY(0, y0 + 6);
		for (k = 1; k <= 120*2; k++) printf(" ");
			
		// print new contents
		x0C = max2Int(i - 3, 1);
			
		for (k = x0C; k <= min(x0C + 3, num + 1); k++){
			goToXY(x0 + 15 + (k - x0C)*15, y0 + 4); printf("%6u", k);
		}

		for (k = x0C; k <= x0C + 3; k++)
			if (k <= i){
				goToXY(x0 + 15 + (k - x0C)*15, y0 + 6); printf("           ");
				goToXY(x0 + 15 + (k - x0C)*15, y0 + 6); printf("%8.2lf", a[num][k]);
			}
			
		// scan for coefficient
		getCoefficientDegree(x0, y0, i, num, a, firstColor, secondColor);
	}
	
	// print last coefficent
	goToXY(x0 + 15 + (i - x0C - 1)*15, y0 + 6);
	for (k = 1; k <= 120; k++) printf(" ");
	goToXY(x0 + 15 + (i - x0C - 1)*15, y0 + 6); printf("%8.2lf", a[num][num + 1]);
	
	// SOLVE
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
	
	// check if has solution
	if (solutionNum[num] == 0) goto noSolution;
	
	// print solutions
	int x = 1, x0S = 1;
	goToXY(x0, y0 + 9); printf("Solutions:");
	char ch = 75;
	do{
		
		if ((ch == 75) || (ch == 77)){
			for (k = x0S; k <= min(x0S + solutionNum[num] - 1, x0S + 3); k++){
				goToXY(x0 + 15 + (k - x0S)*15, y0 + 11); printf("%6u", k);
				goToXY(x0 + 15 + (k - x0S)*15, y0 + 13); printf("%9.4lf", solution[num][k]);
			}
			highlightSolveNthDegreeEquation(x0, y0, x0S, x, num, solution, secondColor);
		}
		
		ch = getch();
		
		// esc
		if (ch == 27) return;
		
		// arrow keys
		if (ch == 4294967264){
			ch = getch();
			
			// arrow left
			if (ch == 75){
				unhighlightSolveNthDegreeEquation(x0, y0, x0S, x, num, solution, firstColor);
				x--;
				if (x == 0) x = 1;
				if (x < x0S) x0S -= 1;
			}
			
			// arrow right
			if (ch == 77){
				unhighlightSolveNthDegreeEquation(x0, y0, x0S, x, num, solution, firstColor);
				x++;
				if (x == solutionNum[num] + 1) x = solutionNum[num];
				if (x > x0S + 3) x0S += 1;
			}
		}
		
		// enter
		if (ch == 13){
			textColor(firstColor);
			goToXY(x0, y0 + 9); for (i = 1; i <= 120*5; i++) printf(" ");
			goto start;
		}
	
	} while (1);
	
	noSolution:
	goToXY(x0, y0 + 9); printf("Solutions:    None");
	goToXY(119, 29);
	do{
		ch = getch();
		if (ch == 13){
			textColor(firstColor);
			goToXY(x0, y0 + 9); for (i = 1; i <= 120*5; i++) printf(" ");
			goto start;
		}
	} while (ch != 27);
	return;
}
