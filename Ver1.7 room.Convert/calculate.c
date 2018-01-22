#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>

#include "operation.Plus.h"

#define MAX_LENGTH 500

void minusRealNum(char *pStrIn1, char *pStrIn2, char *pStrOut){
}

void multiply(char *pStrIn1, char *pStrIn2, char *pStrOut){
}

void devide(char *pStrIn1, char *pStrIn2, char *pStrOut){
}

void power(char *pStrIn1, char *pStrIn2, char *pStrOut){
}

// make strOut = strIn[start] to strIn[end]
void makeStr(char *pStrIn, char *pStrOut, int start, int end){
	int i;
	for (i = start; i <= end; i++) *(pStrOut + i - start) = *(pStrIn + i);
	*(pStrOut + end - start + 1) = '\0';
}

// calculate expression
void calExpression(char* pStrIn, char* pStrOut){
	// initialize
	int length = strlen(pStrIn);
	int countBracket = 0;
	int i;
	
	// case "( )" such as "(3+4/6)"
	// delete brackets, return "3+4/6"
	if ((*pStrIn == '(') && (*(pStrIn + length - 1) == ')')){
		countBracket = 1;
		for (i = 1; i < length; i++){
			if (*(pStrIn + i) == '(') countBracket++;
			if (*(pStrIn + i) == ')') countBracket--;
			if (countBracket == 0) break;
		}
		if (i == length - 1){
			// make string
			char str[MAX_LENGTH];
			makeStr(pStrIn, str, 1, length - 2);
			// recursion
			calExpression(str, pStrOut);
			return;
		}
	}

	// case + -
	for (i = 0; i < length; i++){
		// count bracket
		if (*(pStrIn + i) == '(') countBracket++;
		if (*(pStrIn + i) == ')') countBracket--;
		// check + -
		if (((*(pStrIn + i) == '+') || (*(pStrIn + i) == '-')) && (countBracket == 0)){
			// make strings
			char strIn1[MAX_LENGTH], strIn2[MAX_LENGTH], strOut1[MAX_LENGTH], strOut2[MAX_LENGTH];
			makeStr(pStrIn, strIn1, 0, i - 1);
			makeStr(pStrIn, strIn2, i + 1, length - 1);
			// recursion
			calExpression(strIn1, strOut1);
			calExpression(strIn2, strOut2); // strOut1 and strOut2 are numbers

			// calculate
			if (*(pStrIn + i) == '+') addRealNum(strOut1, strOut2, pStrOut);
			else minusRealNum(strOut1, strOut2, pStrOut);
			// exit
			return;
		}
	}
	
	// case * /
	for (i = 0; i < length; i++){
		// count bracket
		if (*(pStrIn + i) == '(') countBracket++;
		if (*(pStrIn + i) == ')') countBracket--;
		// check + -
		if (((*(pStrIn + i) == '*') || (*(pStrIn + i) == '/')) && (countBracket == 0)){
			// make strings
			char strIn1[MAX_LENGTH], strIn2[MAX_LENGTH], strOut1[MAX_LENGTH], strOut2[MAX_LENGTH];
			makeStr(pStrIn, strIn1, 0, i - 1);
			makeStr(pStrIn, strIn2, i + 1, length - 1);
			// recursion
			calExpression(strIn1, strOut1);
			calExpression(strIn2, strOut2);
			// calculate
			if (*(pStrIn + i) == '*') multiply(strOut1, strOut2, pStrOut);
			else devide(strOut1, strOut2, pStrOut);
			// exit
			exit(0);
		}
	}
	
	// case ^
	for (i = 0; i < length; i++){
		// count bracket
		if (*(pStrIn + i) == '(') countBracket++;
		if (*(pStrIn + i) == ')') countBracket--;
		// check + -
		if ((*(pStrIn + i) == '^') && (countBracket == 0)){
			// make strings
			char strIn1[MAX_LENGTH], strIn2[MAX_LENGTH], strOut1[MAX_LENGTH], strOut2[MAX_LENGTH];
			makeStr(pStrIn, strIn1, 0, i - 1);
			makeStr(pStrIn, strIn2, i + 1, length - 1);
			// recursion
			calExpression(strIn1, strOut1);
			calExpression(strIn2, strOut2);
			// calculate
			power(strOut1, strOut2, pStrOut);
			// exit
			exit(0);
		}
	}
	
	// case number
	makeStr(pStrIn, pStrOut, 0, length - 1);
}

int main(){
	char strIn[MAX_LENGTH] = "1+9";
	char strOut[MAX_LENGTH];
	//calExpression(strIn, strOut);
	char str1[100] = "11", str2[100] = "97";
	addRealNum(str1, str2, strOut);
	puts(strOut);
	return 0;
}
