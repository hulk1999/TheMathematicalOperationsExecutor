#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#include "function.Display.h"
#include "function.Math.h"
#include "function.CalculateExpression.h"

#define MAX_LENGTH 500

void printFirstLineTable(int num){
	int i;
	printf("%c", 218);
	for (i = 1; i < num; i++) printf("%c%c%c%c%c%c%c%c", 196, 196, 196, 196, 196, 196, 196, 194);
	printf("%c%c%c%c%c%c%c%c", 196, 196, 196, 196, 196, 196, 196, 191);
}

void printMiddleLineTable(int num){
	int i;
	printf("%c", 195);
	for (i = 1; i < num; i++) printf("%c%c%c%c%c%c%c%c", 196, 196, 196, 196, 196, 196, 196, 197);
	printf("%c%c%c%c%c%c%c%c", 196, 196, 196, 196, 196, 196, 196, 180);
}

void printLastLineTable(int num){
	int i;
	printf("%c", 192);
	for (i = 1; i < num; i++) printf("%c%c%c%c%c%c%c%c", 196, 196, 196, 196, 196, 196, 196, 193);
	printf("%c%c%c%c%c%c%c%c", 196, 196, 196, 196, 196, 196, 196, 217);
}

void printContentLineTable(int xStart, int xEnd, int y, char* str[8][6]){
	int i;
	printf("%c", 179);
	for (i = xStart; i <= xEnd; i++) printf("%s%c", str[i][y], 179);
}

// create interface for room.Calculate
void createInterfaceCalculate(int x0, int y0, char* str[8][6], int firstColor){
	
	// print title
	textColor(firstColor);
	system("cls");
	goToXY(0, 0); printf("Press Esc to back");
	goToXY(40, 2); printf("           __         __     __");
	goToXY(40, 3); printf(" _______ _/ /_____ __/ /__ _/ /____  ____");
	goToXY(40, 4); printf("/ __/ _ `/ / __/ // / / _ `/ __/ _ \\/ __/");
	goToXY(40, 5); printf("\\__/\\_,_/_/\\__/\\_,_/_/\\_,_/\\__/\\___/_/");
 	
 	// print screen section
 	int i;
 	goToXY(x0, y0 - 4); printf("%c", 218); for (i = 1; i <= 57; i++) printf("%c", 196); printf("%c", 191);
 	goToXY(x0, y0 - 3); printf("%c", 179); goToXY(x0 + 58, y0 - 3); printf("%c", 179);
 	goToXY(x0, y0 - 2); printf("%c", 179); goToXY(x0 + 58, y0 - 2); printf("%c", 179);
 	goToXY(x0, y0 - 1); printf("%c", 192); for (i = 1; i <= 57; i++) printf("%c", 196); printf("%c", 217);
 	
 	// print number section
	goToXY(x0, y0); printFirstLineTable(5);
	for (i = 1; i <= 2; i++){
		goToXY(x0, y0 + i*2 - 1); printContentLineTable(1, 5, i, str);
		goToXY(x0, y0 + i*2); printMiddleLineTable(5);
	}
	goToXY(x0, y0 + 4); printLastLineTable(5);
	
	// print advance operator section
	goToXY(x0, y0 + 5); printFirstLineTable(5);
	for (i = 3; i <= 5; i++){
		goToXY(x0, y0 + i*2); printContentLineTable(1, 5, i, str);
		goToXY(x0, y0 + i*2 + 1); printMiddleLineTable(5);
	}
	goToXY(x0, y0 + 11); printLastLineTable(5);
	
	// print equal sign section
	goToXY(x0 + 42, y0); printFirstLineTable(2);
	for (i = 1; i <= 2; i++){
		goToXY(x0 + 42, y0 + i*2 - 1); printContentLineTable(6, 7, i, str);
		goToXY(x0 + 42, y0 + i*2); printMiddleLineTable(2);
	}
	goToXY(x0 + 42, y0 + 4); printLastLineTable(2);

	// print basic operator section
	goToXY(x0 + 42, y0 + 5); printFirstLineTable(2);
	for (i = 3; i <= 5; i++){
		goToXY(x0 + 42, y0 + i*2); printContentLineTable(6, 7, i, str);
		goToXY(x0 + 42, y0 + i*2 + 1); printMiddleLineTable(2);
	}
	goToXY(x0 + 42, y0 + 11); printLastLineTable(2);
	
	goToXY(119, 29);
}

// highlight current part
void highlightCalculate(int x0, int y0, int x, int y, char* str[8][6], int secondColor){
	
	// highligh
	textColor(secondColor);
	int dx = 0, dy = 0;
	if (x > 5) dx = 2;
	if (y > 2) dy = 1;
	goToXY(x0 + (x - 1)*8 + 1 + dx, y0 + y*2 - 1 + dy);
	printf("%s", str[x][y]);
	
	// move the cusor to the bottom right corner
	goToXY(119, 29);
}

// unhighlight current part
void unhighlightCalculate(int x0, int y0, int x, int y, char* str[8][6], int firstColor){
	
	// unhighligh
	textColor(firstColor);
	int dx = 0, dy = 0;
	if (x > 5) dx = 2;
	if (y > 2) dy = 1;
	goToXY(x0 + (x - 1)*8 + 1 + dx, y0 + y*2 - 1 + dy);
	printf("%s", str[x][y]);
}

// room.Calculate main
void roomCalculate(int firstColor, int secondColor){
	
	// declare vars
	int x0 = 30, y0 = 13, column = 7, row = 5; 
	char strReal[35][50], tmp = '\0';
	char* str[8][6]; // store address of those strings
	
	// assign all the strings '\0'
	int i, j;
	for (i = 0; i <= column + 1; i++)
		for (j = 0; j <= row + 1; j++) str[i][j] = &tmp;
	
	// assign values to the strings	
	strcpy(&strReal[1][0], "   1   "); 
	strcpy(&strReal[2][0], "   2   ");
	strcpy(&strReal[3][0], "   3   ");
	strcpy(&strReal[4][0], "   4   ");
	strcpy(&strReal[5][0], "   5   ");
	strcpy(&strReal[6][0], "   6   ");
	strcpy(&strReal[7][0], "   7   ");
	strcpy(&strReal[8][0], "   8   ");
	strcpy(&strReal[9][0], "   9   ");
	strcpy(&strReal[10][0], "   0   ");
	strcpy(&strReal[11][0], "   ^   ");
	strcpy(&strReal[12][0], "   s   "); strReal[12][3] = 251; // sqrt
	strcpy(&strReal[13][0], "   <   ");
	strcpy(&strReal[14][0], "   >   ");  
	strcpy(&strReal[15][0], "   !   ");
	strcpy(&strReal[16][0], "  sin  ");
	strcpy(&strReal[17][0], "  cos  ");
	strcpy(&strReal[18][0], "  abs  ");
	strcpy(&strReal[19][0], "  log  ");
	strcpy(&strReal[20][0], "  ln   ");
	strcpy(&strReal[21][0], "  tan  ");
	strcpy(&strReal[22][0], "  cot  ");
	strcpy(&strReal[23][0], "   (   ");
	strcpy(&strReal[24][0], "   )   ");
	strcpy(&strReal[25][0], "   e   ");
	strcpy(&strReal[26][0], "   .   ");
	strcpy(&strReal[27][0], "   =   ");
	strcpy(&strReal[28][0], "   p   "); strReal[28][3] = 227; // pi
	strcpy(&strReal[29][0], "  ans  ");
	strcpy(&strReal[30][0], "  DEL  ");
	strcpy(&strReal[31][0], "  AC   ");
	strcpy(&strReal[32][0], "   x   ");
	strcpy(&strReal[33][0], "   /   ");
	strcpy(&strReal[34][0], "   +   ");
	strcpy(&strReal[35][0], "   -   ");
	
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
	str[1][3] = &strReal[11][0];
	str[2][3] = &strReal[12][0];
	str[3][3] = &strReal[13][0];
	str[4][3] = &strReal[14][0];
	str[5][3] = &strReal[15][0];
	str[1][4] = &strReal[16][0];
	str[2][4] = &strReal[17][0];
	str[3][4] = &strReal[18][0];
	str[4][4] = &strReal[19][0];
	str[5][4] = &strReal[20][0];
	str[1][5] = &strReal[21][0];
	str[2][5] = &strReal[22][0];
	str[3][5] = &strReal[23][0];
	str[4][5] = &strReal[24][0];
	str[5][5] = &strReal[25][0];
	str[6][1] = &strReal[26][0];
	str[7][1] = &strReal[27][0];
	str[6][2] = &strReal[28][0];
	str[7][2] = &strReal[29][0];
	str[6][3] = &strReal[30][0];
	str[7][3] = &strReal[31][0];
	str[6][4] = &strReal[32][0];
	str[7][4] = &strReal[33][0];
	str[6][5] = &strReal[34][0];
	str[7][5] = &strReal[35][0];
	
	// create interface
	createInterfaceCalculate(x0, y0, str, firstColor);
	
	// store calculator memory
	char screenLine[MAX_LENGTH], ans[MAX_LENGTH] = "0", ansM[MAX_LENGTH] = "0", key[10];
	screenLine[0] = '\0';
	int screenLineLength = 0, ansLength, keyLength, cursor = 0, start = 0, end = 0;
	
	// using arrow keys to control
	int x = 1, y = 0; // store coordinates
	int isScreen = 1;
	char ch;
	do{
		
		textColor(firstColor);
		end = min2Int(screenLineLength - 1, start + 51);
		
		goToXY(x0 + 3, y0 - 3); for (i = start; i <= end; i++) printf("%c", screenLine[i]);
		for (i = x0 + 3 + end - start + 1; i <= x0 + 57; i++) printf(" ");
		
		goToXY(x0 + 1, y0 - 3);
		if (start > 0) printf("< ..");
		else printf(" ");
		
		goToXY(x0 + 54, y0 - 3);
		if (end < screenLineLength - 1) printf(".. >");
		else{ goToXY(x0 + 55, y0 - 3); printf("   "); }
		
		goToXY(x0 + 3 + cursor - start, y0 - 3);
		
		ch = getch();
		loopWithoutGetch:
		
		// esc
		if (ch == 27) return;
		
		// enter
		if (ch == 13){
			if ((x == 1) && (y == 1)) strcpy(key, "1");
			if ((x == 2) && (y == 1)) strcpy(key, "2");
			if ((x == 3) && (y == 1)) strcpy(key, "3");
			if ((x == 4) && (y == 1)) strcpy(key, "4");
			if ((x == 5) && (y == 1)) strcpy(key, "5");
			if ((x == 1) && (y == 2)) strcpy(key, "6");
			if ((x == 2) && (y == 2)) strcpy(key, "7");
			if ((x == 3) && (y == 2)) strcpy(key, "8");
			if ((x == 4) && (y == 2)) strcpy(key, "9");
			if ((x == 5) && (y == 2)) strcpy(key, "0");
			if ((x == 1) && (y == 3)) strcpy(key, "^");
			if ((x == 2) && (y == 3)){ // sqrt
				strcpy(key, "s");
				key[0] = 251;
			}
			if ((x == 3) && (y == 3)){ // arrow left
				ch = 75;
				goto arrowLeft;
			}
			if ((x == 4) && (y == 3)){ // arrow right
				ch = 77;
				goto arrowRight;
			}
			if ((x == 5) && (y == 3)) strcpy(key, "!");
			if ((x == 1) && (y == 4)) strcpy(key, "sin(");
			if ((x == 2) && (y == 4)) strcpy(key, "cos(");
			if ((x == 3) && (y == 4)) strcpy(key, "abs(");
			if ((x == 4) && (y == 4)) strcpy(key, "log(");
			if ((x == 5) && (y == 4)) strcpy(key, "ln(");
			if ((x == 1) && (y == 5)) strcpy(key, "tan(");
			if ((x == 2) && (y == 5)) strcpy(key, "cot(");
			if ((x == 3) && (y == 5)) strcpy(key, "(");
			if ((x == 4) && (y == 5)) strcpy(key, ")");
			if ((x == 5) && (y == 5)) strcpy(key, "e");
			if ((x == 6) && (y == 1)) strcpy(key, ".");
			if ((x == 7) && (y == 1)) goto calculate; // =
			if ((x == 6) && (y == 2)){ // pi
				strcpy(key, "p");
				key[0] = 227;
			}
			if ((x == 7) && (y == 2)) strcpy(key, "ans");
			if ((x == 6) && (y == 3)){ // DEL
				ch = 8;
				goto backSpace;
			}
			if ((x == 7) && (y == 3)){ // AC
				screenLineLength = 0;
				cursor = 0;
				start = 0;
				continue;
			}
			if ((x == 6) && (y == 4)) strcpy(key, "x");
			if ((x == 7) && (y == 4)) strcpy(key, "/");
			if ((x == 6) && (y == 5)) strcpy(key, "+");
			if ((x == 7) && (y == 5)) strcpy(key, "-");
			
			if (y != 0){
				keyLength = strlen(key);
				for (i = screenLineLength - 1; i >= cursor; i--) screenLine[i + keyLength] = screenLine[i];
				for (i = cursor; i <= cursor + keyLength - 1; i++) screenLine[i] = key[i - cursor];
				cursor += keyLength;
				screenLineLength += keyLength;
				while (cursor >= start + 53) start++;
			}
			else{
				calculate:
				screenLine[screenLineLength] = '\0';
				calExpression(screenLine, ans, ansM);
				if ((ans[0] == 'M') || (ans[0] == 'S')) strcpy(ansM, "0");
				else strcpy(ansM, ans);
				ansLength = strlen(ans);
				goToXY(max2Int(x0 + 3, x0 + 54 - ansLength), y0 - 2);
				for (i = 0; i <= min2Int(ansLength - 1, 51); i++) printf("%c", ans[i]);
				ch = getch();
				goToXY(x0 + 3, y0 - 2);
				for (i = 1; i <= 55; i++) printf(" ");
				goto loopWithoutGetch;
			}
		}
		
		// backspace
		backSpace:
		if ((ch == 8) && (cursor > 0)){
			for (i = cursor; i <= screenLineLength - 1; i++) screenLine[i - 1] = screenLine[i];
			screenLineLength--;
			cursor--;
			start = max2Int(start - 1, 0);
		}
		
		// numbers, characters, symbols
		if ((ch >= 32) && (ch <= 126)){
			for (i = screenLineLength - 1; i >= cursor; i--) screenLine[i + 1] = screenLine[i];
			screenLine[cursor] = ch;
			screenLineLength++;
			cursor++;
			if (cursor == start + 53) start++;
		}
		
		// arrow keys
		if (ch == -32){
			if (!isScreen) unhighlightCalculate(x0, y0, x, y, str, firstColor);
			ch = getch();
			
			// arrow up
			if (ch == 72){
				y--;
				if (y == 0) isScreen = 1;
				if (y == -1) y = 0;
			}
			
			// arrow down
			if (ch == 80){
				y++;
				if (y == row + 1) y = row;
				isScreen = 0;
			}
			
			// arrow left
			if (ch == 75){
				if (isScreen){
					arrowLeft:
					cursor--;
					if (cursor == -1) cursor = 0;
					if (cursor < start) start--;
				}
				else{
					x--;
					if (x == 0) x = 1;
				}
			}
			
			// arrow right
			if (ch == 77){
				if (isScreen){
					arrowRight:
					cursor++;
					if (cursor > screenLineLength) cursor--;
					if (cursor >= start + 53) start++;
				}
				else{
					x++;
					if (x == column + 1) x = column;
				}
			}
			if (!isScreen) highlightCalculate(x0, y0, x, y, str, secondColor);
		}
	} while(1);
}

int main(){
	roomCalculate(15, 240);
	return 0;
}
