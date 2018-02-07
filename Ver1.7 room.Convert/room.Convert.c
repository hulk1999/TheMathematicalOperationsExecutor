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
	
	// print contents
	goToXY(x0 - 10, y0); printf("Base 10:");
	goToXY(x0 - 10, y0 + step); printf("Base  2:");
	goToXY(x0 - 10, y0 + 2*step); printf("Base  8:");
	goToXY(x0 - 10, y0 + 3*step); printf("Base 16:");
	
	goToXY(x0, y0);
}

// check if input number is valid
int checkNumForConverting(char* numStr, int y){
	int length = strlen(numStr);
	
	// check '-'
	int i, minus = 0;
	if (numStr[0] == '-') minus = 1;
	for (i = 1; i <= length - 1; i++)
		if (numStr[i] == '-') return 0;
	
	// check '.'
	int dot = 0;
	for (i = minus; i <= length - 1; i++)
		if (numStr[i] == '.'){
			if ((i == minus) || (i == length - 1) || (dot == 1)) return 0;
			dot++;
		}
	
	// check digit in each base
	switch (y){
		case 1:
			for (i = 0; i <= length - 1; i++)
				if (!(((numStr[i] >= '0') && (numStr[i] <= '9')) || (numStr[i] == '.') || (numStr[i] == '-'))) return 0;
			break;
		case 2:
			for (i = 0; i <= length - 1; i++)
				if (!(((numStr[i] >= '0') && (numStr[i] <= '1')) || (numStr[i] == '.') || (numStr[i] == '-'))) return 0;
			break;
		case 3:
			for (i = 0; i <= length - 1; i++)
				if (!(((numStr[i] >= '0') && (numStr[i] <= '7')) || (numStr[i] == '.') || (numStr[i] == '-'))) return 0;
			break;
		case 4:
			for (i = 0; i <= length - 1; i++)
				if (!(((numStr[i] >= '0') && (numStr[i] <= '9')) || ((numStr[i] >= 'A') && (numStr[i] <= 'F')) || (numStr[i] == '.') || (numStr[i] == '-'))) return 0;
			break;
		default: break;
	}
	
	eliminateAllZeros(numStr);
	return 1;
}

// convert digit to string
void digitToString(char digit, char* str){
	if ((digit >= '0') && (digit <= '9')){
		str[0] = digit;
		str[1] = '\0';
	}
	else{
		str[0] = '1';
		str[1] = digit - 'A' + '0';
		str[2] = '\0';
	}
}

// convert string to digit
char stringToDigit(char* str){
	if (strlen(str) == 1) return str[0];
	return str[1] - '0' + 'A';
}

// divide for integral
void divideForIntegral(char* strIn1, char* strIn2, char* strOut){
	char tmp[500];
	divideRealNum(strIn1, strIn2, tmp);
	int i;
	for (i = 0; i <= strlen(tmp); i++)
		if (tmp[i] == '.') break;
	int dotPos = i;
	for (i = 0; i < dotPos; i++) strOut[i] = tmp[i];
	strOut[i] = '\0';
}

// divide for fractional
void divideForFractional(char* strIn1, char* strIn2, char* strOut){
	char tmp[500], tmp2[500];
	divideForIntegral(strIn1, strIn2, tmp);
	multiplyRealNum(strIn2, tmp, tmp2);
	subtractRealNum(strIn1, tmp2, strOut);
}

// convert from base 10 to others
int convertFrom10(char* base10, int base, char* output){
	
	// process minus & dot
	int minus = 0, dot = 0, length = strlen(base10);
	if (base10[0] == '-') minus = 1;
	int i;
	for (i = minus; i <= length - 1; i++)
		if (base10[i] == '.'){
			dot = i;
			break;
		}
	if (dot == 0) dot = length;
	
	// convert
	char tmpNum[500], tmpNum2[500], tmpBase[500], tmpDigit[500], tmpDigitArray[500];
	int digitCount = 0;
	itoa(base, tmpBase, 10);
	
	// integral part
	for (i = minus; i <= dot - 1; i++){
		tmpNum[i - minus] = base10[i];
	}
	tmpNum[dot - minus] = '\0';
	if (i - minus + 1 == 0) strcpy(tmpNum, "0");
	while (tmpNum[0] != '0'){
		strcpy(tmpNum2, tmpNum);
		divideForFractional(tmpNum2, tmpBase, tmpDigit);
		tmpDigitArray[digitCount++] = stringToDigit(tmpDigit);
		divideForIntegral(tmpNum2, tmpBase, tmpNum);
	}
	
	// get output integral part
	for (i = digitCount - 1; i >= 0; i--) output[digitCount - i - 1] = tmpDigitArray[i];
	if (digitCount == 0) strcpy(output, "0");
	else output[digitCount] = '\0';
	
	// fractional part
	char tmpOne[500], tmpNum3[500];
	int outNumber = 0;
	strcpy(tmpOne, "1");
	digitCount = 0;
	tmpNum[0] = '0';
	for (i = dot; i <= length - 1; i++){
		tmpNum[i - dot + 1] = base10[i];
	}
	tmpNum[length - dot + 1] = '\0';
	if (dot == length) strcpy(tmpNum, "0");
	while (tmpNum[strlen(tmpNum) - 1] != '0'){
		if (digitCount == 30){
			outNumber = 1;
			break;
		}
		strcpy(tmpNum2, tmpNum);
		multiplyRealNum(tmpNum2, tmpBase, tmpNum3);
		divideForIntegral(tmpNum3, tmpOne, tmpDigit);
		tmpDigitArray[digitCount++] = stringToDigit(tmpDigit);
		subtractRealNum(tmpNum3, tmpDigit, tmpNum);
	}
	
	// get output fractional part
	int lengthOut = strlen(output);
	if (dot != length) output[lengthOut] = '.';
	for (i = 0; i <= digitCount - 1; i++) output[lengthOut + i + 1] = tmpDigitArray[i];
	output[lengthOut + digitCount + 1] = '\0';

	// check for minus
	if (minus){
		strcpy(tmpDigit, "0");
		strcpy(tmpNum, output);
		subtractRealNum(tmpDigit, tmpNum, output);
	}
	
	// check for outnumber
	if (outNumber){
		length = strlen(output);
		output[length] = '.';
		output[length + 1] = '.';
		output[length + 2] = '\0';
	}
}

// convert to base 10 from others
int convertTo10(char* input, int base, char* base10){
	
	// process minus & dot
	int minus = 0, dot = 0, length = strlen(input);
	if (input[0] == '-') minus = 1;
	int i;
	for (i = minus; i <= length - 1; i++)
		if (input[i] == '.'){
			dot = i;
			break;
		}
	if (dot == 0) dot = length;
	
	// convert
	char tmpBase10[500], tmpExponent[500], tmpDigit[500], tmpBase[500], tmpPower[500], tmpMultiply[500];
	itoa(base, tmpBase, 10);
	strcpy(base10, "0");
	
	// integral part
	for (i = dot - 1; i >= minus; i--){
		strcpy(tmpBase10, base10);
		digitToString(input[i], tmpDigit);
		itoa(dot - i - 1, tmpExponent, 10);
		powerRealNum(tmpBase, tmpExponent, tmpPower);
		multiplyRealNum(tmpDigit, tmpPower, tmpMultiply);
		addRealNum(tmpBase10, tmpMultiply, base10);
	}
	
	// fractional part
	for (i = dot + 1; i <= length - 1; i++){
		strcpy(tmpBase10, base10);
		digitToString(input[i], tmpDigit);
		itoa(dot - i, tmpExponent, 10);
		powerRealNum(tmpBase, tmpExponent, tmpPower);
		multiplyRealNum(tmpDigit, tmpPower, tmpMultiply);
		addRealNum(tmpBase10, tmpMultiply, base10);
	}
	
	// check for minus
	if (minus){
		strcpy(tmpDigit, "0");
		strcpy(tmpBase10, base10);
		subtractRealNum(tmpDigit, tmpBase10, base10);
	}
	
	// check for outnumber
	base10[dot + 31] = '.';
	base10[dot + 32] = '.';
	base10[dot + 33] = '\0';
}

// room.Convert main
void roomConvert(int firstColor, int secondColor){
	
	// declare vars
	int x0 = 37, y0 = 12, step = 2, row = 4, y = 1;
	int count = 0;
	int i, j, t;
	char base10[500], base2[500], base8[500], base16[500], numStr[500];
	char* str[5];
	
	base10[0] = '\0'; base2[0] = '\0'; base8[0] = '\0'; base16[0] = '\0';
	str[1] = base10; str[2] = base2; str[3] = base8; str[4] = base16;
	
	// create interface
	createInterfaceConvert(x0, y0, step, firstColor);
	
	// check for esc
	char ch;
	do{
		ch = getch();
		
		// esc
		if (ch == 27) return;
		
		// backspace
		if ((ch == 8) && (count > 0)){
			count--;
			goToXY(x0 + count, y0 + (y - 1)*step); printf(" ");
			goToXY(x0 + count, y0 + (y - 1)*step);
		}
		
		// numbers, minus, dot, A -> F
		if ((((ch >= '0') && (ch <= '9')) || ((ch >= 'A') && (ch <= 'F'))|| (ch == '-') || (ch == '.')) && (count < 50)){
			goToXY(x0 + count, y0 + (y - 1)*step); printf("%c", ch);
			numStr[count] = ch;
			count++;
		}
		
		// arrow keys
		if (ch == 4294967264){
			
			ch = getch();
			
			// print last element
			if ((y != 0) && ((ch == 72) || (ch == 80))){
				goToXY(x0, y0 + (y - 1)*step); for (i = x0; i <= 240; i++) printf(" ");
				goToXY(x0, y0 + (y - 1)*step); printf("%s", str[y]);
			}
			
			// arrow up
			if (ch == 72){
				y--;
				if (y <= 0) y = 1;
				count = 0;
			}
			
			// arrow down
			if (ch == 80){
				y++;
				if (y == row + 1) y = row;
				count = 0;
			}
			
			// get ready for input
			if ((ch == 72) || (ch == 80)){
				goToXY(x0, y0 + (y - 1)*step); for (i = x0; i <= 240; i++) printf(" ");
				goToXY(x0, y0 + (y - 1)*step);
			}
		}
		
		// enter
		if ((ch == 13) && (count > 0)){
			numStr[count] = '\0';
			if (checkNumForConverting(numStr, y)){
				switch (y){
					case 1:
						strcpy(base10, numStr);
						convertFrom10(base10, 2, base2);
						convertFrom10(base10, 8, base8);
						convertFrom10(base10, 16, base16);
						break;
					case 2:
						strcpy(base2, numStr);
						convertTo10(base2, 2, base10);
						convertFrom10(base10, 8, base8);
						convertFrom10(base10, 16, base16);
						break;
					case 3:
						strcpy(base8, numStr);
						convertTo10(base8, 8, base10);
						convertFrom10(base10, 2, base2);
						convertFrom10(base10, 16, base16);
						break;
					case 4:
						strcpy(base16, numStr);
						convertTo10(base16, 16, base10);
						convertFrom10(base10, 2, base2);
						convertFrom10(base10, 8, base8);
						break;
					default: break;
				}
				for (i = 1; i <= 4; i++){
					goToXY(x0, y0 + (i - 1)*step); for (j = x0; j <= 240; j++) printf(" ");
					goToXY(x0, y0 + (i - 1)*step); printf("%s", str[i]);
				}
				goToXY(119, 29);
			}
			
		}
		
	} while(1);
}

int main(){
	roomConvert(15, 240);
	return 0;
}
