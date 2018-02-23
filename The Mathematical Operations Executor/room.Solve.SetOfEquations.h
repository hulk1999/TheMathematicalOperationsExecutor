//-----------------------------------------------declaration------------------------------------------------------------------//

// functions for creating interface
void highlightSolveSetOfEquations(int x0, int y0, int x0S, int x, double* solution, int secondColor);
void unhighlightSolveSetOfEquations(int x0, int y0, int x0S, int x, double* solution, int firstColor);

// get coefiicents
int getCoefficient(int x0, int y0, int x, int y, double a[50][50], int firstColor, int secondColor);

// functions for solving
void swapRow(int row1, int row2, double a[50][50]);
void solveSetOfNEquations(int num, int firstColor, int secondColor);

//----------------------------------------------------------------------------------------------------------------------------//

// get coefiicents
int getCoefficient(int x0, int y0, int x, int y, double a[50][50], int firstColor, int secondColor){

	textColor(secondColor);
	goToXY(x0 + 15 + min2Int(x - 1, 3)*15, y0 + 6 + min2Int(y - 1, 1)* 2); printf("           ");
	goToXY(x0 + 19 + min2Int(x - 1, 3)*15, y0 + 6 + min2Int(y - 1, 1)* 2);
	
	char ch, numStr[35];
	int count = 0, dot = 0;
	double num;
	do{
		ch = getch();
		
		// esc
		if (ch == 27) return 0;
		
		// backspace
		if ((ch == 8) && (count > 0)){
			if (numStr[count] == '.') dot--;
			count--;
			goToXY(x0 + 19 + min2Int(x - 1, 3)*15 + count, y0 + 6 + min2Int(y - 1, 1)* 2); printf(" ");
			goToXY(x0 + 19 + min2Int(x - 1, 3)*15 + count, y0 + 6 + min2Int(y - 1, 1)* 2);
		}
		
		// numbers
		if ((ch >= '0') && (ch <= '9') && (count <= 29)){
			goToXY(x0 + 19 + min2Int(x - 1, 3)*15 + count, y0 + 6 + min2Int(y - 1, 1)* 2); printf("%c", ch);
			count++;
			numStr[count] = ch;
		}
		
		// dot
		if ((ch == '.') && (count > 0) && (count <= 29) && (numStr[count] != '-') && (dot == 0)){
			goToXY(x0 + 19 + min2Int(x - 1, 3)*15 + count, y0 + 6 + min2Int(y - 1, 1)* 2); printf("%c", ch);
			count++;
			numStr[count] = ch;
			dot++;
		}
		
		// minus
		if ((ch == '-') && (count == 0)){
			goToXY(x0 + 19 + min2Int(x - 1, 3)*15 + count, y0 + 6 + min2Int(y - 1, 1)* 2); printf("%c", ch);
			count++;
			numStr[count] = ch;
		}
		
		// enter
		if (ch == 13){
			if ((count > 0) && (numStr[count] != '.') && (numStr[count] != '-')){
				numStr[++count] = '\0';
				shiftLeft(numStr);
				a[x][y] = convertStringToDouble(numStr);
				textColor(firstColor);
				return 1;
			}
		}	
	} while (1);
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

// swap 2 equation's position
void swapRow(int row1, int row2, double a[50][50]){
	int i;
	double tmp;
	for (i = 1; i <= 49; i++){
		tmp = a[i][row1];
		a[i][row1] = a[i][row2];
		a[i][row2] = tmp;
	}
}

// solve set of n equations
void solveSetOfNEquations(int num, int firstColor, int secondColor){
	startOfSolve: num = num;
	
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
			if (getCoefficient(x0, y0, j, i, a, firstColor, secondColor) == 0) return;
		}
	// print last coefficent
	goToXY(x0 + 15 + (j - x0C - 1)*15, y0 + 6 + (i - y0C - 1)* 2);
	for (k = 1; k <= 120; k++) printf(" ");
	goToXY(x0 + 15 + (j - x0C - 1)*15, y0 + 6 + (i - y0C - 1)* 2); printf("%8.2lf", a[num + 1][num]);
	
	// SOLVE
	// make triangle and check for solutions
	int noSolutionCheck, allZeroCheck;
	double ratio;
	for (i = 1; i <= num; i++){
		if (a[i][i] == 0){
			for (j = i + 1; j <= num; j++) if (a[i][j] == 0) swapRow(i, j, a);
			if (a[i][i] == 0){ // no or infinite solutions
				for (k = i; k <= num; k++){
					allZeroCheck = 1;
					for (m = i + 1; m <= num; m++) if (a[m][k] != 0) allZeroCheck = 0;
					if ((allZeroCheck == 1) && (a[num + 1][k] != 0)){
						noSolutionCheck = 1;
						goto noSolution;
					}
				}
				noSolutionCheck = 2;
				goto noSolution;
			}
		}
		else{
			for (j = i + 1; j <= num; j++){
				ratio = - a[i][j] / a[i][i];
				for (k = i; k <= num + 1; k++)
				a[k][j] += a[k][i] * ratio;
			}
		}
	}
	
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
		if (ch == -32){
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
			goto startOfSolve;
		}
		
	} while (1);
	
	// print no or infinite solutions
	noSolution:
	goToXY(x0, y0 + 11);
	if (noSolutionCheck == 1) printf("Solutions:    None");
	else printf("Solutions:    Infinite");
	goToXY(119, 29);
	do{
		ch = getch();
		if (ch == 13){
			textColor(firstColor);
			goToXY(x0, y0 + 11); for (i = 1; i <= 120*5; i++) printf(" ");
			goto startOfSolve;
		}
	} while (ch != 27);
	return;
}
