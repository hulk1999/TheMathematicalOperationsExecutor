#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

//#include "room.Calculate.h"
//#include "room.Solve.h"
//#include "room.Convert.h"
#include "room.Settings.h"
#include "room.Credits.h"
//#include "room.Dinosaur.h"
#include "function.Display.h"

int firstColor = 15; secondColor = 240;

void initialize(char* str[8], char str1[50], char str2[50], char str3[50], char str4[50], char str5[50], char str6[50], char str7[50]){
	str[1] = str1;
	str[2] = str2;
	str[3] = str3;
	str[4] = str4;
	str[5] = str5;
	str[6] = str6;
	str[7] = str7;
}

void createInterface(int x0, int y0, int step, int option, char* str[8]){
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
	
	int i;
	for (i = 1; i <= option; i++){
		goToXY(x0, y0 + (i - 1)*step);
		printf("%s", str[i]);
	}
}

void highlight(int x0, int y0, int step, int num, char* str[8]){
	textColor(secondColor);
	goToXY(x0, y0 + (num - 1)*step);
	printf("%s", str[num]);
	goToXY(119, 29); // move the cusor to the bottom right corner
}

void unhighlight(int x0, int y0, int step, int num, char* str[8]){
	textColor(firstColor);
	goToXY(x0, y0 + (num - 1)*step);
	printf("%s", str[num]);	
}

void roomMain(){
	
	int x0 = 46, y0 = 14, step = 2, option = 7;
	char str1[50] = " CALCULATE EXPRESSIONS ",
		 str2[50] = "    SOLVE EQUATIONS    ",
		 str3[50] = "    CONVERT NUMBERS    ",
		 str4[50] = "       SETTINGS        ",
		 str5[50] = "     VIEW  CREDITS     ",
		 str6[50] = "  PLAY WITH  DINOSAUR  ",
		 str7[50] = "         EXIT          ";
	char* str[8]; // stores address of those strings
	
	initialize(str, str1, str2, str3, str4, str5, str6, str7);
	createInterface(x0, y0, step, option, str);
	
	highlight(x0, y0, step, 1, str);
	int i = 1;
	char ch;
	do{
		ch = getch();
		// the function getch() pushes 2 values to the buffer when it comes to
		// arrow keys. first is 4294967264 and the second is 72, 75, 77 or 80
		// depends on whether the key is up, left, right or down.
		if (ch == 4294967264){
			unhighlight(x0, y0, step, i, str);
			ch = getch();
			if (ch == 72){ // arrow up
				i--;
				if (i == 0) i = option;
			}
			if (ch == 80){ // arrow down
				i++;
				if (i == option + 1) i = 1;
			}
			highlight(x0, y0, step, i, str);
		}
		if (ch == 13){ // '\n'
			switch (i){
//				case 1: roomCalculate(); break;
//				case 2: roomSolve();     break;
//				case 3: roomConvert();   break;
				case 4: roomSettings();  break;
				case 5: roomCredits();   break;
//				case 6: roomDinosaur();  break;
				case 7:
					textColor(firstColor);
					system("cls");
					exit(0);
					break;
				default: break;
			}
			createInterface(x0, y0, step, option, str);
			i = 1;
			highlight(x0, y0, step, i, str);
		}
	} while (1);
}

void main(){
	roomMain();
	char s[10][10];
	// strings stored as columns
	//printf("%u %u", &s[1][1], &s[2][1]);
	return 0;
}
