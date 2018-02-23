#include "room.Solve.NthDegreeEquation.h"
#include "room.Solve.SetOfEquations.h"

//-----------------------------------------------declaration------------------------------------------------------------------//

// functions for creating interface
void createInterfaceSolve(int x0, int y0, int step, int row, char* str[6][3], int firstColor);
void highlightSolve(int x0, int y0, int step, int x, int y, char* str[6][3], int secondColor);
void unhighlightSolve(int x0, int y0, int step, int x, int y, char* str[6][3], int firstColor);
void printNthDegreeEquation(int y0, int step, char* str[6][3]);
void deleteNthDegreeEquation(int y0, int step, char* str[6][3], int firstColor);
void printSetOfNEquations(int y0, int step, char* str[6][3]);
void deleteSetOfNEquations(int y0, int step, char* str[6][3], int firstColor);

// get optional degree & number of equations
int inputDegree(int* pX, int *pNum, int y0, int step, char* str[6][3], int firstColor, int secondColor);
int inputSetNum(int* pX, int* pNum, int y0, int step, char* str[6][3], int firstColor, int secondColor);

// room.Solve main
void roomSolve(int firstColor, int secondColor);

//----------------------------------------------------------------------------------------------------------------------------//

// create interface for room.Solve
void createInterfaceSolve(int x0, int y0, int step, int row, char* str[6][3], int firstColor){
	
	// print title
	textColor(firstColor);
	system("cls");
	goToXY(0, 0); printf("Press Esc to back");
	goToXY(28, 2); printf("                     __  _                      __");
	goToXY(28, 3); printf(" ___ ___ ___ _____ _/ /_(_)__  ___    ___ ___  / /  _____ ____");
	goToXY(28, 4); printf("/ -_) _ `/ // / _ `/ __/ / _ \\/ _ \\  (_-</ _ \\/ / |/ / -_) __/");
	goToXY(28, 5); printf("\\__/\\_, /\\_,_/\\_,_/\\__/_/\\___/_//_/ /___/\\___/_/|___/\\__/_/");
	goToXY(28, 6); printf("	 /_/");
	goToXY(119, 29);
	
	// print menu
	int i;
	for (i = 1; i <= row; i++){
		goToXY(x0, y0 + (i - 1)*step);
		printf("%s", str[1][i]);
	}
}

// highlight current part
void highlightSolve(int x0, int y0, int step, int x, int y, char* str[6][3], int secondColor){
	
	// highlight
	textColor(secondColor);
	if (x == 1) goToXY(x0, y0 + (y - 1)*step);
	else goToXY(16 + x*16, y0 + (y - 1)*step);
	printf("%s", str[x][y]);
	
	// move the cusor to the bottom right corner
	goToXY(119, 29);
}

// unhighlight current part
void unhighlightSolve(int x0, int y0, int step, int x, int y, char* str[6][3], int firstColor){
	
	// unhighlight
	textColor(firstColor);
	if (x == 1) goToXY(x0, y0 + (y - 1)*step);
	else goToXY(16 + x*16, y0 + (y - 1)*step);
	printf("%s", str[x][y]);
}

// print n-th degree equation section
void printNthDegreeEquation(int y0, int step, char* str[6][3]){
	int x;
	for (x = 2; x <= 5; x++){
		goToXY(16 + x*16, y0);
		printf("%s", str[x][1]);
	}
}

// delete n-th degree equation section
void deleteNthDegreeEquation(int y0, int step, char* str[6][3], int firstColor){
	textColor(0);
	int x;
	for (x = 2; x <= 5; x++){
		goToXY(16 + x*16, y0);
		printf("%s", str[x][1]);
	}
	textColor(firstColor);
}

// print n-th degree equation section
void printSetOfNEquations(int y0, int step, char* str[6][3]){
	int x;
	for (x = 2; x <= 5; x++){
		goToXY(16 + x*16, y0 + step);
		printf("%s", str[x][2]);
	}
}

// delete n-th degree equation section
void deleteSetOfNEquations(int y0, int step, char* str[6][3], int firstColor){
	textColor(0);
	int x;
	for (x = 2; x <= 5; x++){
		goToXY(16 + x*16, y0 + step);
		printf("%s", str[x][2]);
	}
	textColor(firstColor);
}

// get optional degree
int inputDegree(int* pX, int *pNum, int y0, int step, char* str[6][3], int firstColor, int secondColor){
	
	// display
	int x = 96, y = 12;
	textColor(firstColor);
	goToXY(x, y + 1); printf("    input    ");
	textColor(secondColor);
	goToXY(x, y); printf("             ");
	goToXY(x + 5, y);
	
	// get input
	char ch;
	int numStr[3], count = 0, num;
	do{
		ch = getch();
		loopWithoutGetch:
		
		// esc
		if (ch == 27) return 0;
		
		// backspace
		if ((ch == 8) && (count > 0)){
			count--;
			goToXY(x + 6 + count, y); printf(" ");
			goToXY(x + 6 + count, y);
		}
		
		// numbers
		if ((ch >= '0') && (ch <= '9') && (count <= 1)){
			goToXY(x + 6 + count, y); printf("%c", ch);
			count++;
			numStr[count] = ch;
		}
		
		// enter
		if (ch == 13){
			if (count >= 1){
				num = numStr[count] - '0';
				if (count == 2) num += (numStr[1] - '0') * 10;
				if (num <= 1){
					textColor(firstColor);
					goToXY(x, y + 1);
					if (num <= 0) printf("    error!   ");
					else printf("  seriously? ");
					goToXY(119, 29);
					ch = getch();
					goToXY(x, y + 1);
					printf("    input    ");
					goToXY(x + 6 + count, y);
					textColor(secondColor);
					goto loopWithoutGetch;
				}
				else{
					*pNum = num;
					return 1;					
				}
			}
		}
		
		// arrow keys
		if (ch == -32){
			ch = getch();
			
			// arrow left
			if (ch == 75){
				*pNum = 0;
				*pX -= 1;
				textColor(firstColor);
				goToXY(x, y + 1); printf("             ");
				return 1;
			}
		}
	} while (1);
}

// get optional number of equation
int inputSetNum(int* pX, int* pNum, int y0, int step, char* str[6][3], int firstColor, int secondColor){
	
	// display
	int x = 96, y = 18;
	textColor(firstColor);
	goToXY(x, y + 1); printf("    input    ");
	textColor(secondColor);
	goToXY(x, y); printf("             ");
	goToXY(x + 5, y);
	
	// get input
	char ch;
	int numStr[3], count = 0, num;
	do{
		ch = getch();
		loopWithoutGetch:
		
		// esc
		if (ch == 27) return 0;
		
		// backspace
		if ((ch == 8) && (count > 0)){
			count--;
			goToXY(x + 6 + count, y); printf(" ");
			goToXY(x + 6 + count, y);
		}
		
		// numbers
		if ((ch >= '0') && (ch <= '9') && (count <= 1)){
			goToXY(x + 6 + count, y); printf("%c", ch);
			count++;
			numStr[count] = ch;
		}
		
		// enter
		if (ch == 13){
			if (count >= 1){
				num = numStr[count] - '0';
				if (count == 2) num += (numStr[1] - '0') * 10;
				if (num <= 1){
					textColor(firstColor);
					goToXY(x, y + 1);
					if (num <= 0) printf("    error!   ");
					else printf("  seriously? ");
					goToXY(119, 29);
					ch = getch();
					goToXY(x, y + 1);
					printf("    input    ");
					goToXY(x + 6 + count, y);
					textColor(secondColor);
					goto loopWithoutGetch;
				}
				else{
					*pNum = num;
					return 1;					
				}
			}
		}
		
		// arrow keys
		if (ch == -32){
			ch = getch();
			
			// arrow left
			if (ch == 75){
				*pNum = 0;
				*pX -= 1;
				textColor(firstColor);
				goToXY(x, y + 1); printf("             ");
				return 1;
			}
		}
	} while (1);
}

// room.Solve main
void roomSolve(int firstColor, int secondColor){
	
	// declare vars
	int x0 = 15, y0 = 12, step = 6, row = 2, column = 5;
	char strReal[11][50], tmp = '\0';
	char* str[6][3]; // store address of those strings
	
	// assign all the strings '\0'
	int i, j;
	for (i = 0; i <= column + 1; i++)
		for (j = 0; j <= row + 1; j++) str[i][j] = &tmp;
	
	// assign values to the strings	
	strcpy(&strReal[1][0], "  N-TH DEGREE EQUATION   >"); 
	strcpy(&strReal[2][0], "      2      ");
	strcpy(&strReal[3][0], "      3      ");
	strcpy(&strReal[4][0], "      4      ");
	strcpy(&strReal[5][0], "    other    ");
	strcpy(&strReal[6][0], "  SET OF N EQUATIONS     >");
	strcpy(&strReal[7][0], "      2      ");
	strcpy(&strReal[8][0], "      3      ");
	strcpy(&strReal[9][0], "      4      ");
	strcpy(&strReal[10][0], "    other    ");
	
	// store addresses
	str[1][1] = &strReal[1][0];
	str[2][1] = &strReal[2][0];
	str[3][1] = &strReal[3][0];
	str[4][1] = &strReal[4][0];
	str[5][1] = &strReal[5][0];
	str[1][2] = &strReal[6][0];
	str[2][2] = &strReal[7][0];
	str[3][2] = &strReal[8][0];
	str[4][2] = &strReal[9][0];
	str[5][2] = &strReal[10][0];
	
	// create interface
	createInterfaceSolve(x0, y0, step, row, str, firstColor);
	
	// using arrow keys to control
	highlightSolve(x0, y0, step, 1, 1, str, secondColor);
	int num, x = 1, y = 1; // store coordinates
	char ch;
	do{
		ch = getch();
		
		// esc
		if (ch == 27) return;
		
		// arrow keys
		if (ch == -32){
			unhighlightSolve(x0, y0, step, x, y, str, firstColor);
			ch = getch();
			
			// arrow up
			if (ch == 72){
				y--;
					 if (y == 0) y = 1;
				else if ((y == 1) && (x != 1)) y = 2;
			}
			
			// arrow down
			if (ch == 80){
				y++;
					 if (y == row + 1) y = row;
				else if ((y == 2) && (x != 1)) y = 1;
			}
			
			// arrow left
			if (ch == 75){
				x--;
					 if (x == 0) x = 1;
				else if (x == 1) switch (y){
									case 1: deleteNthDegreeEquation(y0, step, str, firstColor); break;
									case 2: deleteSetOfNEquations(y0, step, str, firstColor); break;
									default: break;
								 }
			}
			
			// arrow right
			if (ch == 77){
				x++;
					 if (x == column + 1) x = column;
				else if (x == 2) switch (y){
									case 1: printNthDegreeEquation(y0, step, str); break;
									case 2: printSetOfNEquations(y0, step, str); break;
									default: break;
								 }
				else if (x == 5){
					switch (y){
						case 1:
							if (inputDegree(&x, &num, y0, step, str, firstColor, secondColor) == 0) return;
							if (num > 0){
								x = num;
								goto solve;
							}
							break;
						case 2:
							if (inputSetNum(&x, &num, y0, step, str, firstColor, secondColor) == 0) return;
							if (num > 0){
								x = num;
								goto solve;
							}
							break;
						default: break;
					}
					unhighlightSolve(x0, y0, step, 5, y, str, firstColor);
				}
			}
			
			highlightSolve(x0, y0, step, x, y, str, secondColor);
		}
		
		// enter
		if ((ch == 13) && (x >= 2)){
			solve:
			
			// delete menu
			textColor(0);
			for (i = 1; i <= row; i++){
				goToXY(x0, y0 + (i - 1)*step);
				printf("%s", str[1][i]);
			}
			goToXY(96, 13);
			printf("             ");
			textColor(firstColor);

			// n-th degree equation section
			if (y == 1){
				deleteNthDegreeEquation(y0, step, str, firstColor);
				solveNthDegreeEquation(x, firstColor, secondColor);
			}
			
			// set of n equations section
			if (y == 2){
				deleteSetOfNEquations(y0, step, str, firstColor);
				solveSetOfNEquations(x, firstColor, secondColor);
			}
			
			// print menu, reset
			textColor(firstColor);
			goToXY(0, 10);
			for (i = 1; i < 120*18; i++) printf(" ");
			for (i = 1; i <= row; i++){
				goToXY(x0, y0 + (i - 1)*step);
				printf("%s", str[1][i]);
			}
			highlightSolve(x0, y0, step, 1, 1, str, secondColor);
			x = 1; y = 1;
		}
	} while (1);
}
