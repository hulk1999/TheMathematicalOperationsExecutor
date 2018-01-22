#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_LENGTH 500

void numToChar(int num, char* pCh){
	if (num <= 9) *pCh = num + '0';
	else *pCh = num - 10 + 'A';
}

void charToNum(char ch, int* pNum){
	if (ch <= '9') *pNum = ch - '0';
	else *pNum = ch - 'A' + 10;
}

void stringToNum(char str[MAX_LENGTH], int* pNum){
	*pNum = 0;
	int length = strlen(str);
	int i, tmp;
	for (i = 0; i < length; i++){
		charToNum(str[length - i - 1], &tmp);
		*pNum += tmp * pow(10, i);
	}
}

void numToString(int num, char str[MAX_LENGTH]){
	int i;
	for (i = 1; ; i++) if (num / pow(10, i) < 1) break;
	int length = i;
	str[length] = '\0';
	for (i = length - 1; i >= 0; i--){
		numToChar(num % 10, &str[i]);
		num /= 10;
	}
}

void convertFrom10(char strIn[MAX_LENGTH], int base, char strOut[MAX_LENGTH]){
	
	int num, stack[MAX_LENGTH];
	stringToNum(strIn, &num);
	int i = 0;
	while (num > 0){
		stack[i] = num % base;
		num /= base;
		i++;
	}
	
	int length = i;
	strOut[length] = '\0';
	for (i-- ; i >= 0; i--) numToChar(stack[i], &strOut[length - i - 1]);
}

void convertTo10(char strIn[MAX_LENGTH], int base, char strOut[MAX_LENGTH]){
	
	int length = strlen(strIn);
	
	int dotPos = length;
	int i;
	for (i = 0; i < length; i++)
		if (strIn[i] == '.'){
			dotPos = i;
			break;
		}
	
	int num = 0, tmp;
	for (i = 0; i < dotPos; i++){
		charToNum(strIn[dotPos - i - 1], &tmp);
		num += tmp * pow(base, i);
	}
	numToString(num, strOut);	
}

int main(){
	char str[500];
	convertFrom10("10", 1, str);
	//convertTo10("F0", 16, str);
	puts(str);
	return 0;
}
