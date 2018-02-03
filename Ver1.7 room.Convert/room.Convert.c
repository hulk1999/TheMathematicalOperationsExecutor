#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#include "function.Display.h"
#include "function.Math.h"
#include "function.String.h"

// create interface for room.Convert
void createInterfaceConvert(int x0, int y0, int step, int firstColor){
	
	// print title
	textColor(firstColor);
	system("cls");
	goToXY(0, 0); printf("Press Esc to back");
	goToXY(24, 2); printf("                   __                                       __");
	goToXY(24, 3); printf("  ___  __ ____ _  / /  ___ ____  _______  ___ _  _____ ____/ /____ ____");
	goToXY(24, 4); printf(" / _ \\/ // /  ' \\/ _ \\/ -_) __/ / __/ _ \\/ _ \\ |/ / -_) __/ __/ -_) __/");
	goToXY(24, 5); printf("/_//_/\\_,_/_/_/_/_.__/\\__/_/    \\__/\\___/_//_/___/\\__/_/  \\__/\\__/_/");
	
	goToXY(x0, y0); printf("Base 10:");
	goToXY(x0, y0 + step); printf("Base  2:");
	goToXY(x0, y0 + 2*step); printf("Base  8:");
	goToXY(x0, y0 + 3*step); printf("Base 16:");
	
	goToXY(119, 29);
}

// room.Convert main
void roomConvert(int firstColor, int secondColor){
	
	// declare vars
	int x0 = 15, y0 = 12, step = 2, row = 2, column = 5;
	
	// create interface
	createInterfaceConvert(x0, y0, step, firstColor);
	
	// check for esc
	char ch;
	do{
		ch = getch();
		
		// esc
		if (ch == 27) return;
	} while(1);
}

int main(){
	roomConvert(15, 240);
	return 0;
}
