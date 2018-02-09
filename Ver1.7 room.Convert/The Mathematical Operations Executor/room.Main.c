#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#include "room.Calculate.h"
#include "room.Solve.h"
#include "room.Convert.h"
#include "room.Settings.h"
#include "room.Credits.h"
#include "room.Dinosaur.h"

#include "function.Display.h"
#include "function.CalculateExpression.h"
#include "function.Math.h"

//-----------------------------------------------declaration------------------------------------------------------------------//

// functions for creating interface
void createInterface(int x0, int y0, int step, int option, char** str, int firstColor);
void highlight(int x0, int y0, int step, int num, char** str, int secondColor);
void unhighlight(int x0, int y0, int step, int num, char** str, int firstColor);

// room.Main main
void roomMain();

//----------------------------------------------------------------------------------------------------------------------------//

// create interface for room.Main
void createInterface(int x0, int y0, int step, int option, char** str, int firstColor){
	
	// print title
	textColor(firstColor);
	system("cls");
	
	goToXY(10, 1); printf(" ________");
	goToXY(10, 2); printf("/_  __/ /  ___");
	goToXY(10, 3); printf(" / / / _ \\/ -_)");
	goToXY(10, 4); printf("/_/ /_//_/\\__/");

	goToXY(26, 1); printf("   __  ___     __  __                  __  _          __");
	goToXY(26, 2); printf("  /  |/  /__ _/ /_/ /  ___ __ _  ___ _/ /_(_)______ _/ /");
	goToXY(26, 3); printf(" / /|_/ / _ `/ __/ _ \\/ -_)  ' \\/ _ `/ __/ / __/ _ `/ /");
	goToXY(26, 4); printf("/_/  /_/\\_,_/\\__/_//_/\\__/_/_/_/\\_,_/\\__/_/\\__/\\_,_/_/");
	
	goToXY(30, 5); printf("  ____                    __  _  ");
	goToXY(30, 6); printf(" / __ \\___  ___ _______ _/ /_(_)__  ___  ___");
	goToXY(30, 7); printf("/ /_/ / _ \\/ -_) __/ _ `/ __/ / _ \\/ _ \\(_-<");
	goToXY(30, 8); printf("\\____/ .__/\\__/_/  \\_,_/\\__/_/\\___/_//_/___/");
	goToXY(30, 9); printf("    /_/");

	goToXY(76, 5); printf("   ____                  __");
	goToXY(76, 6); printf("  / __/_ _____ ______ __/ /____  ____");
	goToXY(76, 7); printf(" / _/ \\ \\ / -_) __/ // / __/ _ \\/ __/");
	goToXY(76, 8); printf("/___//_\\_\\\\__/\\__/\\_,_/\\__/\\___/_/");
	
	// print menu
	int i;
	for (i = 1; i <= option; i++){
		goToXY(x0, y0 + (i - 1)*step);
		printf("%s", str[i]);
	}
}

// highlight current part
void highlight(int x0, int y0, int step, int num, char** str, int secondColor){

	textColor(secondColor);
	goToXY(x0, y0 + (num - 1)*step);
	printf("%s", str[num]);
	
	// move the cusor to the bottom right corner
	goToXY(119, 29);
}

// unhighlight current part
void unhighlight(int x0, int y0, int step, int num, char** str, int firstColor){
	textColor(firstColor);
	goToXY(x0, y0 + (num - 1)*step);
	printf("%s", str[num]);	
}

// room.Main main
void roomMain(){
	
	// declare vars
	int x0 = 46, y0 = 12, step = 2, option = 7, firstColor, secondColor, size;
	
	// get colors and size
	FILE *memory = fopen("memory.txt", "r");
	fscanf(memory, "%d %d %d", &firstColor, &secondColor, &size);
	fclose(memory);
	
	// assign values to the strings
	char str1[50] = " CALCULATE EXPRESSIONS ",
		 str2[50] = "    SOLVE EQUATIONS    ",
		 str3[50] = "    CONVERT NUMBERS    ",
		 str4[50] = "       SETTINGS        ",
		 str5[50] = "     VIEW  CREDITS     ",
		 str6[50] = "  PLAY WITH  DINOSAUR  ",
		 str7[50] = "         EXIT          ";
	char* str[8]; // store addresses of those strings
	
	// store addresses
	str[1] = str1;
	str[2] = str2;
	str[3] = str3;
	str[4] = str4;
	str[5] = str5;
	str[6] = str6;
	str[7] = str7;
	
	// set console size to 120 column : 30 rows
	setConsoleSize(993, 519);
	fontSize(size / 2, size);
	
	// create interface
	createInterface(x0, y0, step, option, str, firstColor);
	
	// using arrow keys to control
	highlight(x0, y0, step, 1, str, secondColor);
	int i = 1; // store coordinates
	char ch;
	do{
		ch = getch();
		// the function getch() pushes 2 values to the buffer when it comes to
		// arrow keys. first is 4294967264 and the second is 72, 75, 77 or 80
		// depends on whether the key is up, left, right or down.
		
		// arrow keys
		if (ch == 4294967264){
			unhighlight(x0, y0, step, i, str, firstColor);
			ch = getch();
			
			// arrow up
			if (ch == 72){
				if (i == 6){
					goToXY(x0 + 30, y0 + 5*step); printf("                            ");
				}
				i--;
				if (i == 0) i = option;
			}
			
			// arrow down
			if (ch == 80){
				if (i == 6){
					goToXY(x0 + 30, y0 + 5*step); printf("                            ");
				}
				i++;
				if (i == option + 1) i = 1;
			}
			
			// special print for dinosaur
			if (i == 6){
				goToXY(x0 + 30, y0 + 5*step); printf("Screw it! Math is for nerds!");
			}
			
			highlight(x0, y0, step, i, str, secondColor);
		}
		
		// enter
		if (ch == 13){
			switch (i){
				case 1: roomCalculate(firstColor, secondColor); break;
				case 2: roomSolve(firstColor, secondColor); break;
				case 3: roomConvert(firstColor, secondColor); break;
				case 4: roomSettings(&firstColor, &secondColor); break;
				case 5: roomCredits(firstColor, secondColor); break;
				case 6: roomDinosaur(firstColor, secondColor); break;
				case 7:
					textColor(firstColor);
					system("cls");
					exit(0);
					break;
				default: break;
			}
			createInterface(x0, y0, step, option, str, firstColor);
			i = 1;
			highlight(x0, y0, step, i, str, secondColor);
		}
	} while (1);
}

int main(){
	roomMain();
	return 0;
}
