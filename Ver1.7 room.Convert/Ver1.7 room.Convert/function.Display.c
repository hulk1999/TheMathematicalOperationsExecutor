#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

void goToXY(int x, int y){
	HANDLE handle;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordinate = {x, y};
	SetConsoleCursorPosition(handle, coordinate);
}

void textColor(int color){
	HANDLE handle;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);
}
