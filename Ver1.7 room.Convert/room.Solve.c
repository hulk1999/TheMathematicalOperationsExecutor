#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#include "function.Display.h"
#include "function.Math.h"
#include "function.String.h"

int firstColorSo, secondColorSo;

// create interface for room.Solve
void createInterfaceSolve(int x0, int y0, int step, int row, char* str[6][3]){
	
	// print title
	textColor(firstColorSo);
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
void highlightSolve(int x0, int y0, int step, int x, int y, char* str[6][3]){
	
	// highlight
	textColor(secondColorSo);
	if (x == 1) goToXY(x0, y0 + (y - 1)*step);
	else goToXY(16 + x*16, y0 + (y - 1)*step);
	printf("%s", str[x][y]);
	
	// move the cusor to the bottom right corner
	goToXY(119, 29);
}

// unhighlight current part
void unhighlightSolve(int x0, int y0, int step, int x, int y, char* str[6][3]){
	
	// unhighlight
	textColor(firstColorSo);
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
void deleteNthDegreeEquation(int y0, int step, char* str[6][3]){
	textColor(0);
	int x;
	for (x = 2; x <= 5; x++){
		goToXY(16 + x*16, y0);
		printf("%s", str[x][1]);
	}
	textColor(firstColorSo);
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
void deleteSetOfNEquations(int y0, int step, char* str[6][3]){
	textColor(0);
	int x;
	for (x = 2; x <= 5; x++){
		goToXY(16 + x*16, y0 + step);
		printf("%s", str[x][2]);
	}
	textColor(firstColorSo);
}

int inputDegree(int* pX){
}

int inputSetNum(int* pX){
}

void solveNthDegreeEquation(int num){
}

void solveSetOfNEquations(int num){
	int x0 = 6, y0 = 8;
	goToXY(x0, y0); printf("SOLVING SET OF %u EQUATIONS", num);
	goToXY(x0, y0 + 2); printf("Input coefficients for %u equations, %u coefficients each: ", num, num + 1);
	goToXY(x0, y0 + num + 4); printf("Solutions: "); getchar();
}

// room.Solve main
void roomSolve(int pFirstColor, int pSecondColor){
	
	// assign color
	firstColorSo = pFirstColor;
	secondColorSo = pSecondColor;
	
	// declare vars
	int x0 = 15, y0 = 12, step = 6, row = 2, column = 5;
	char strReal[11][50], tmp = '\0';
	char* str[6][3]; // store address of those strings
	
	// assign all the strings '\0'
	int i, j;
	for (i = 0; i <= column + 1; i++)
		for (j = 0; j <= row + 1; j++) str[i][j] = &tmp;
	
	// assign values to the strings	
	makeStr("  N-TH DEGREE EQUATION   >", &strReal[1][0]); 
	makeStr("      2      ", &strReal[2][0]);
	makeStr("      3      ", &strReal[3][0]);
	makeStr("      4      ", &strReal[4][0]);
	makeStr("    other    ", &strReal[5][0]);
	makeStr("  SET OF N EQUATIONS     >", &strReal[6][0]);
	makeStr("      2      ", &strReal[7][0]);
	makeStr("      3      ", &strReal[8][0]);
	makeStr("      4      ", &strReal[9][0]);
	makeStr("    other    ", &strReal[10][0]);
	
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
	createInterfaceSolve(x0, y0, step, row, str);
	
	// using arrow keys to control
	highlightSolve(x0, y0, step, 1, 1, str);
	int x = 1, y = 1; // store coordinates
	char ch;
	do{
		ch = getch();
		
		// esc
		if (ch == 27) return;
		
		// arrow keys
		if (ch == 4294967264){
			unhighlightSolve(x0, y0, step, x, y, str);
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
									case 1: deleteNthDegreeEquation(y0, step, str); break;
									case 2: deleteSetOfNEquations(y0, step, str); break;
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
						case 1: if (inputDegree(&x) == -1) return; break;
						case 2: if (inputSetNum(&x) == -1) return; break;
						default: break;
					}
					unhighlightSolve(x0, y0, step, x, y, str);
				}
			}
			
			highlightSolve(x0, y0, step, x, y, str);
		}
		
		// enter
		if ((ch == 13) && (x >= 2)){
			
			// delete menu
			textColor(0);
			for (i = 1; i <= row; i++){
				goToXY(x0, y0 + (i - 1)*step);
				printf("%s", str[1][i]);
			}
			textColor(firstColorSo);

			// n-th degree equation section
			if (y == 1){
				deleteNthDegreeEquation(y0, step, str);
				solveNthDegreeEquation(x);
			}
			
			// set of n equations section
			if (y == 2){
				deleteSetOfNEquations(y0, step, str);
				solveSetOfNEquations(x);
			}
			
			// print menu, reset
			for (i = 1; i <= row; i++){
				goToXY(x0, y0 + (i - 1)*step);
				printf("%s", str[1][i]);
			}
			highlightSolve(x0, y0, step, 1, 1, str);
			x = 1; y = 1;
		}
	} while (1);
}

int main(){
	roomSolve(15, 240);
	return 0;
}
