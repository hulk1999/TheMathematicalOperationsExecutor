#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

#include "function.Display.h"

int firstColor = 15, secondColor = 240;

void makeStr(char strIn[50], char strOut[50]){
	int i = 0;
	while (strIn[i] != '\0'){
		strOut[i] = strIn[i];
		i++;
	}
	strOut[i] = '\0';
}

void createInterfaceSettings(int x0, int y0, int step, int row, char* str[6][5]){
	textColor(firstColor);
	system("cls");
	goToXY(0, 0); printf("Press Esc to back");
	goToXY(42, 2); printf("	     __  __  _");
	goToXY(42, 3); printf("  ___ ___ / /_/ /_(_)__  ___ ____");
	goToXY(42, 4); printf(" (_-</ -_) __/ __/ / _ \\/ _ `(_-<");
	goToXY(42, 5); printf("/___/\\__/\\__/\\__/_/_//_/\\_, /___/");
	goToXY(42, 6); printf("                       /___/");
	goToXY(119, 29);
	
	int i;
	for (i = 1; i <= row; i++){
		goToXY(x0, y0 + (i - 1)*step);
		printf("%s", str[1][i]);
	}
}

void highlightSettings(int x0, int y0, int step, int x, int y, char* str[6][5]){
	if ((x >= 2) && (y <= 2)) textColor(128 + 16*(x - 2 + 4*(y-1))); // set appropriate color
	else textColor(secondColor);
	if (x == 1) goToXY(x0, y0 + (y - 1)*step);
	else goToXY(16 + x*16, y0 + (y - 1)*step);
	printf("%s", str[x][y]);
	goToXY(119, 29); // move the cusor to the bottom right corner
}

void unhighlightSettings(int x0, int y0, int step, int x, int y, char* str[6][5]){
	if ((x >= 2) && (y <= 2)) textColor(4*(y - 1) + x + 6); // set appropriate color
	else textColor(firstColor);
	if (x == 1) goToXY(x0, y0 + (y - 1)*step);
	else goToXY(16 + x*16, y0 + (y - 1)*step);
	printf("%s", str[x][y]);
}

void printColor(int y0, int step, char* str[6][5]){
	int x, y;
	for (x = 2; x <= 5; x++)
		for (y = 1; y <= 2; y++){
			textColor(4*(y - 1) + x + 6); // set appropriate color
			goToXY(16 + x*16, y0 + (y - 1)*step);
			printf("%s", str[x][y]);
		}
}

void deleteColor(int y0, int step, char* str[6][5]){
	textColor(0);
	int x, y;
	for (x = 2; x <= 5; x++)
		for (y = 1; y <= 2; y++){
			goToXY(16 + x*16, y0 + (y - 1)*step);
			printf("%s", str[x][y]);
		}
	textColor(firstColor);
}

void printSize(int y0, int step, char* str[6][5]){
	int x, y = 3;
	for (x = 2; x <= 5; x++){
		goToXY(16 + x*16, y0 + (y - 1)*step);
		printf("%s", str[x][y]);
	}
}

void deleteSize(int y0, int step, char* str[6][5]){
	textColor(0);
	int x, y = 3;
	for (x = 2; x <= 5; x++){
		goToXY(16 + x*16, y0 + (y - 1)*step);
		printf("%s", str[x][y]);
	}
	textColor(firstColor);
}

void printMusic(int y0, int step, char* str[6][5]){
	int x = 2, y = 4;
	goToXY(16 + x*16, y0 + (y - 1)*step);
	printf("%s", str[x][y]);
}

void deleteMusic(int y0, int step, char* str[6][5]){
	textColor(0);
	int x = 2, y = 4;
	goToXY(16 + x*16, y0 + (y - 1)*step);
	printf("%s", str[x][y]);
	textColor(firstColor);
}

void roomSettings(){
	int x0 = 22, y0 = 10, step = 3, row = 4, column = 5;
	char strReal[17][50], tmp = '\0';
	char* str[6][5]; // stores address of those strings
	
	int i, j;
	for (i = 0; i <= 6; i++)
		for (j = 0; j <= 5; j++) str[i][j] = &tmp;
		
	makeStr("       COLOR      >", &strReal[1][0]); 
	makeStr("    boring   ", &strReal[2][0]);
	makeStr("    shark    ", &strReal[3][0]);
	makeStr("    matrix   ", &strReal[4][0]);
	makeStr("     sky     ", &strReal[5][0]);
	makeStr("    devil    ", &strReal[6][0]);
	makeStr("  melancholy ", &strReal[7][0]);
	makeStr("  sunflower  ", &strReal[8][0]);
	makeStr("     pure    ", &strReal[9][0]);
	makeStr("       SIZE       >", &strReal[10][0]);
	makeStr("    small    ", &strReal[11][0]);
	makeStr("    medium   ", &strReal[12][0]);
	makeStr("    large    ", &strReal[13][0]);
	makeStr("    other    ", &strReal[14][0]);  
	makeStr("       MUSIC      >", &strReal[15][0]);
	makeStr("    Nah I'm just kidding :))    ", &strReal[16][0]);
	
	str[1][1] = &strReal[1][0];
	str[2][1] = &strReal[2][0];
	str[3][1] = &strReal[3][0];
	str[4][1] = &strReal[4][0];
	str[5][1] = &strReal[5][0];
	str[2][2] = &strReal[6][0];
	str[3][2] = &strReal[7][0];
	str[4][2] = &strReal[8][0];
	str[5][2] = &strReal[9][0];
	str[1][3] = &strReal[10][0];
	str[2][3] = &strReal[11][0];
	str[3][3] = &strReal[12][0];
	str[4][3] = &strReal[13][0];
	str[5][3] = &strReal[14][0];
	str[1][4] = &strReal[15][0];
	str[2][4] = &strReal[16][0];
	
	createInterfaceSettings(x0, y0, step, row, str);
	
	highlightSettings(x0, y0, step, 1, 1, str);
	int x = 1, y = 1;
	char ch;
	do{
		ch = getch();
		if (ch == 27) return; // esc
		if (ch == 13){ // enter
			if ((x >= 2) && (y <= 2)){
				firstColor = 4*(y - 1) + x + 6;
				secondColor = 128 + 16*(x - 2 + 4*(y-1));
				createInterfaceSettings(x0, y0, step, row, str);
				highlightSettings(x0, y0, step, 1, 1, str);
				x = 1; y = 1;
			}
			if ((x >= 2) && (y == 3)){
				switch (x){
					case 2: fontSize(6, 12); break;
					case 3: fontSize(8, 16); break;
					case 4: fontSize(11, 22); break;
//					case 5:
//						int t = getFontSize();
//						fontSize(t, 2*t);
//						break;
					default: break;
				}
			}
		}
		if (ch == 4294967264){ // arrow keys
			unhighlightSettings(x0, y0, step, x, y, str);
			ch = getch();
			if (ch == 72){ // arrow up
				y--;
					 if (y == 0) y = 1;
				else if ((y == 2) && (x == 1)) y = 1;
				else if ((y == 2) && (x != 1)) y = 3;
				else if ((y == 3) && (x != 1)) y = 4;
			}
			if (ch == 80){ // arrow down
				y++;
					 if (y == row + 1) y = row;
				else if ((y == 2) && (x == 1)) y = 3;
				else if ((y == 3) && (x != 1)) y = 2;
				else if ((y == 4) && (x != 1)) y = 3;
			}
			if (ch == 75){ // arrow left
				x--;
					 if (x == 0) x = 1;
				else if ((x == 1) && (y == 2)){
					x = 1;
					y = 1;
					deleteColor(y0, step, str);
				}
				else if (x == 1) switch (y){
									case 1: deleteColor(y0, step, str); break;
									case 3: deleteSize(y0, step, str); break;
									case 4: deleteMusic(y0, step, str); break;
									default: break;
								 }
			}
			if (ch == 77){ // arrow right
				x++;
					 if (x == 6) x = 5;
				else if ((x == 3) && (y == 4)) x = 2;
				else if (x == 2) switch (y){
									case 1: printColor(y0, step, str); break;
									case 3: printSize(y0, step, str); break;
									case 4: printMusic(y0, step, str); break;
									default: break;
								 }
			}
			highlightSettings(x0, y0, step, x, y, str);
		}
	} while (1);
}

int main(){
	roomSettings();
	return 0;
}
