//-----------------------------------------------declaration------------------------------------------------------------------//

// functions for creating interface
void highlightSolveSetOfEquations(int x0, int y0, int x0S, int x, double* solution, int secondColor);
void unhighlightSolveSetOfEquations(int x0, int y0, int x0S, int x, double* solution, int firstColor);

// get coefiicents
void getCoefficient(int x0, int y0, int x, int y, double a[50][50], int firstColor, int secondColor);

// functions for solving
int hasSolutionSetOfEquations(int num, double a[50][50]);
void solveSetOfNEquations(int num, int firstColor, int secondColor);

//----------------------------------------------------------------------------------------------------------------------------//

// get coefiicents
void getCoefficient(int x0, int y0, int x, int y, double a[50][50], int firstColor, int secondColor){
	textColor(secondColor);
	int isNum;
	char isEnter;
	do{
		goToXY(x0 + 15 + min2Int(x - 1, 3)*15, y0 + 6 + min2Int(y - 1, 1)* 2); printf("           ");
		goToXY(x0 + 19 + min2Int(x - 1, 3)*15, y0 + 6 + min2Int(y - 1, 1)* 2);
		fflush(stdin);
		isNum = scanf("%lf", &a[x][y]);
		scanf("%c", &isEnter);
	} while ((isNum != 1) || (isEnter != '\n'));
	textColor(firstColor);
}

// highlight current part
void highlightSolveSetOfEquations(int x0, int y0, int x0S, int x, double* solution, int secondColor){
	textColor(secondColor);
	goToXY(x0 + 15 + (x - x0S)*15, y0 + 15); printf("           ");
	goToXY(x0 + 15 + (x - x0S)*15, y0 + 15); printf("%9.4lf", solution[x]);
	goToXY(119, 29);
}

// unhighlight current part
void unhighlightSolveSetOfEquations(int x0, int y0, int x0S, int x, double* solution, int firstColor){
	textColor(firstColor);
	goToXY(x0 + 15 + (x - x0S)*15, y0 + 15); printf("           ");
	goToXY(x0 + 15 + (x - x0S)*15, y0 + 15); printf("%9.4lf", solution[x]);
}

// check if the set has solution
int hasSolutionSetOfEquations(int num, double a[50][50]){
	int i;
	for (i = 1; i <= num; i++) if (a[i][i] == 0) return 0;
	return 1;
}

// solve set of n equations
void solveSetOfNEquations(int num, int firstColor, int secondColor){
	start: num = num;
	
	int x0 = 25, y0 = 10;
	goToXY(x0, y0); printf("SOLVING SET OF %u EQUATIONS", num);
	goToXY(x0, y0 + 2); printf("Input:");
	
	// get input
	double a[50][50];
	int i, j, k, m, x0C, y0C;
	for (i = 1; i <= num; i++)
		for (j = 1; j <= num + 1; j++){
			
			// delete previous contents
			goToXY(0, y0 + 6);
			for (k = 1; k <= 120*4; k++) printf(" ");
			
			// print new contents
			x0C = max2Int(j - 3, 1); y0C = max2Int(i - 1, 1);
			
			for (k = x0C; k <= min(x0C + 3, num + 1); k++){
				goToXY(x0 + 15 + (k - x0C)*15, y0 + 4); printf("%6.0u", k);
			}
			for (k = y0C; k <= y0C + 1; k++){
				goToXY(x0 + 12, y0 + 6 + (k - y0C)*2); printf("%u", k);
			}
			for (m = y0C; m <= min2Int(y0C + 1, i); m++){
				for (k = x0 + 15; k <= 120; k++){
					goToXY(k, y0 + 8); printf(" ");
				}
				for (k = x0C; k <= x0C + 3; k++)
					if (((m < i) || (k < j)) && (k <= num + 1)){
						goToXY(x0 + 15 + (k - x0C)*15, y0 + 6 + (m - y0C)* 2); printf("           ");
						goToXY(x0 + 15 + (k - x0C)*15, y0 + 6 + (m - y0C)* 2); printf("%8.2lf", a[k][m]);
					}
			}
			
			// scan for coefficient
			getCoefficient(x0, y0, j, i, a, firstColor, secondColor);
		}
	// print last coefficent
	goToXY(x0 + 15 + (j - x0C - 1)*15, y0 + 6 + (i - y0C - 1)* 2);
	for (k = 1; k <= 120; k++) printf(" ");
	goToXY(x0 + 15 + (j - x0C - 1)*15, y0 + 6 + (i - y0C - 1)* 2); printf("%8.2lf", a[num + 1][num]);
	
	// SOLVE
	// make triangle
	double ratio;
	for (i = 1; i < num; i++){
		for (j = i + 1; j <= num; j++){
			ratio = - a[i][j] / a[i][i];
			for (k = i; k <= num + 1; k++)
				a[k][j] += a[k][i] * ratio;
		}
	}
	
	// check if has solution
	if (!(hasSolutionSetOfEquations(num, a))) goto infiniteSolution;
	
	// get solutions
	double solution[50];
	solution[num] = a[num + 1][num] / a[num][num];
	for (i = num; i >= 1; i--){
		for (j = num; j >= i + 1; j--) a[num + 1][i] -= a[j][i] * solution[j];
		solution[i] = a[num + 1][i] / a[i][i];
	}
	
	// print solutions
	int x = 1, x0S = 1;
	goToXY(x0, y0 + 11); printf("Solutions:");
	char ch = 75;
	do{
		
		if ((ch == 75) || (ch == 77)){
			for (k = x0S; k <= min(x0S + num - 1, x0S + 3); k++){
				goToXY(x0 + 15 + (k - x0S)*15, y0 + 13); printf("%6u", k);
				goToXY(x0 + 15 + (k - x0S)*15, y0 + 15); printf("%9.4lf", solution[k]);
			}
			highlightSolveSetOfEquations(x0, y0, x0S, x, solution, secondColor);
		}
		
		ch = getch();
		
		// esc
		if (ch == 27) return;
		
		// arrow keys
		if (ch == 4294967264){
			ch = getch();
			
			// arrow left
			if (ch == 75){
				unhighlightSolveSetOfEquations(x0, y0, x0S, x, solution, firstColor);
				x--;
				if (x == 0) x = 1;
				if (x < x0S) x0S -= 1;
			}
			
			// arrow right
			if (ch == 77){
				unhighlightSolveSetOfEquations(x0, y0, x0S, x, solution, firstColor);
				x++;
				if (x == num + 1) x = num;
				if (x > x0S + 3) x0S += 1;
			}
		}
		
		// enter
		if (ch == 13){
			textColor(firstColor);
			goToXY(x0, y0 + 11); for (i = 1; i <= 120*5; i++) printf(" ");
			goto start;
		}
		
	} while (1);

	infiniteSolution:
	goToXY(x0, y0 + 11); printf("Solutions:    Infinite");
	goToXY(119, 29);
	do{
		ch = getch();
		if (ch == 13){
			textColor(firstColor);
			goToXY(x0, y0 + 11); for (i = 1; i <= 120*5; i++) printf(" ");
			goto start;
		}
	} while (ch != 27);
	return;
}
