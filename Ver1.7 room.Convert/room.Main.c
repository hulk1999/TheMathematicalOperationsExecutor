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

// create interface for room.Main
void createInterface(int x0, int y0, int step, int option, char** str, int firstColor){
	
	// print title
	textColor(firstColor);
	system("cls");
	goToXY(6, 3); printf("Welcome to");
	goToXY(20, 5); printf("THE");
	goToXY(25, 1); printf("	       .__               .__          __");
	goToXY(25, 2); printf("  ____ _____  |  |   ____  __ __|  | _____ _/  |_  ___________");
	goToXY(25, 3); printf("_/ ___\\\\__  \\ |  | _/ ___\\|  |  \\  | \\__  \\\\   __\\/  _ \\_  __ \\");
	goToXY(25, 4); printf("\\  \\___ / __ \\|  |_\\  \\___|  |  /  |__/ __ \\|  | (  <_> )  | \\/");
	goToXY(25, 5); printf(" \\___  >____  /____/\\___  >____/|____(____  /__|  \\____/|__|   ");
	goToXY(25, 6); printf("     \\/     \\/          \\/                \\/");
	goToXY(40, 7); printf("An ordinary calculator just like any others, but now you have to write");
	goToXY(40, 8); printf("       thousands of lines of code and take days of debugging to get it.");
	goToXY(40, 10); printf("Now what /*da hell*/ do you want to do?");
	
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

// roomMain main
void roomMain(){
	
	// declare vars
	int x0 = 46, y0 = 14, step = 2, option = 7, firstColor = 15, secondColor = 240;
	
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

void main(){
	roomMain();
	return 0;
}
