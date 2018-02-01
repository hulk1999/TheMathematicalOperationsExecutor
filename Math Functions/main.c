#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 500

//////////////////// Declaration /////////////////////

///// Functionalities /////

// Conversion
int convertCharToInt(char inputChar);
char convertIntToChar(int inputNum);

// Shifting
void shiftLeft(char* inputRealNum);
void shiftRight(char* inputRealNum); // Remember to give inputRealNum[0] a value

void pushBack(char* inputRealNum, char newChar);
void popBack(char* inputRealNum);
void eliminateRightZero(char* inputRealNum);
void eliminateLeftZero(char* inputRealNum);

void balanceNumOfDigits(char* realBigNum, char* realSmallNum);

// Others
int isRealNumber(char* inputRealNum);
int min2Int(int a, int b);
int max2Int(int a, int b);
int isGreater(char* realNum1, char* realNum2);

void multiplyByNum(int Num, char* realNum, char* result);
void multiplyTenfold(char* realNum);
void divideTenfold(char* realNum);

void swapDigits(char* digitNum1, char* digitNum2);
void swapStrings(char* realNum1, char* realNum2);

///// Math Operations /////
void addRealNum(char* realNum1, char* realNum2, char* result);
void subtractRealNum(char* realNum1, char* realNum2, char* result);
void multiplyRealNum(char* realNum1, char* realNum2, char* result);
void divideRealNum(char* realNum1, char* realNum2, char* result);

/* TODO
	void powerRealNum(char* realNum1, char* realNum2, char* result);
*/
//////////////////////////////////////////////////////


////////////////////////////////////////////////////// MAIN //////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
	char inputNum1[MAX_LENGTH], inputNum2[MAX_LENGTH], result[MAX_LENGTH];
	strcpy(result, "");
	do
	{
	scanf("%s %s", &inputNum1, &inputNum2);
//	addRealNum(inputNum1, inputNum2, result);
//	printf("Sum: %s\n\n", result);
//	subtractRealNum(inputNum1, inputNum2, result);
//	printf("Difference: %s\n\n", result);
//	multiplyRealNum(inputNum1, inputNum2, result);
//	printf("Product: %s\n\n", result);
	divideRealNum(inputNum1, inputNum2, result);
//	printf("Quotient: %s\n\n", result);
//	strcpy(inputNum1, "9999999999999999999999999999999.99999999999999999999999");
//	strcpy(inputNum2, "9999999999999999999999999999999.99999999999999999999999");
	
	} while(1);
	return 0;
}


////////////////////////////////////////////////////// Conversion //////////////////////////////////////////////////////
int convertCharToInt(char inputChar)
{
	return (int)inputChar - 48;
}
char convertIntToChar(int inputNum)
{
	return (char)(inputNum + 48);
}

////////////////////////////////////////////////////// Shifting //////////////////////////////////////////////////////

// Shifting string
void shiftLeft(char* inputRealNum)
{
	int numLength = strlen(inputRealNum);
	int count;
	for(count = 0; count < numLength - 1; count++)
	{
		inputRealNum[count] = inputRealNum[count + 1];
	}
	inputRealNum[numLength - 1] = '\0';

}

// inputRealNum[0] = '0' by default
void shiftRight(char* inputRealNum)
{
	int count, numLength = strlen(inputRealNum);
	char tempRealNum[numLength + 1];
	for(count = 0; count < numLength; count++)
	{
		tempRealNum[count + 1] = inputRealNum[count];
	}
	tempRealNum[numLength + 1] = '\0';
	tempRealNum[0] = '0';
	strcpy(inputRealNum, tempRealNum);
}

void pushBack(char* inputRealNum, char newChar)
{
	char tempNum[MAX_LENGTH];
	int count, numLength = strlen(inputRealNum);
	for(count = 0; count < numLength; count++) tempNum[count] = inputRealNum[count];
	tempNum[numLength] = newChar;
	tempNum[numLength + 1] = '\0';
	strcpy(inputRealNum, tempNum);
}
void popBack(char* inputRealNum)
{
	int numLength = strlen(inputRealNum);
	inputRealNum[numLength - 1] = '\0';		
}

// Change 1.000000000 to 1 
void eliminateRightZero(char* inputRealNum)
{
//	printf("Input eliminateRightZero: %s\n", inputRealNum);
	int numLength = strlen(inputRealNum);
	int dotPosition = isRealNumber(inputRealNum);
	if(dotPosition == 0) return;
	while(numLength >= dotPosition && (inputRealNum[numLength] == '0' || inputRealNum[numLength] == '\0' 
										|| inputRealNum[numLength] == '.')) 
	{
		inputRealNum[numLength] = '\0'; 
		numLength--;
	}
//	printf("Output eliminateRightZero: %s\n", inputRealNum);
}
// Change 00001 to 1
void eliminateLeftZero(char* inputRealNum)
{
//	printf("Input eliminateLeftZero: %s\n", inputRealNum);
	int count, numLength, dotPosition;
	numLength = strlen(inputRealNum);
	dotPosition = isRealNumber(inputRealNum);
	while(inputRealNum[0] == '0' &&  isRealNumber(inputRealNum) > 1 + (inputRealNum[0] == '-'))
	{
		shiftLeft(inputRealNum);
		numLength = strlen(inputRealNum);
	}
//	printf("Output eliminateLeftZero: %s\n", inputRealNum);
}
// change 123.456 + 0 to 123.456 + 000.000
void balanceNumOfDigits(char* realNum1, char* realNum2)
{
//	printf("Input balanceNumOfDigits: %s %s\n", realNum1, realNum2);
	if(realNum1[0] == '-')
	{
		shiftLeft(realNum1);
		balanceNumOfDigits(realNum1, realNum2);
		shiftRight(realNum1);
		realNum1[0] = '-';
		return;
	}
	if(realNum2[0] == '-')
	{
		shiftLeft(realNum2);
		balanceNumOfDigits(realNum1, realNum2);
		shiftRight(realNum2);
		realNum2[0] = '-';
		return;
	}
	if(strlen(realNum1) == 0) strcpy(realNum1, "0");
	if(strlen(realNum2) == 0) strcpy(realNum2, "0");
	if(!isRealNumber(realNum1)) 
	{
		pushBack(realNum1, '.');
		pushBack(realNum1, '0');
	}
	if(!isRealNumber(realNum2))
	{
		pushBack(realNum2, '.');
		pushBack(realNum2, '0');
	}
	// Dealing with integer part
	int dotPosition1 = isRealNumber(realNum1);
	int dotPosition2 = isRealNumber(realNum2);
	while(dotPosition1 < dotPosition2)
	{
		shiftRight(realNum1);
		dotPosition1++;
	}
	while(dotPosition2 < dotPosition1)
	{
		shiftRight(realNum2);
		dotPosition2++;
	}
	// Dealing with the floating points
	while(strlen(realNum1) < strlen(realNum2)) pushBack(realNum1, '0');
	while(strlen(realNum1) > strlen(realNum2)) pushBack(realNum2, '0');
	
//	printf("Output balanceNumOfDigits: %s %s\n", realNum1, realNum2);
}

////////////////////////////////////////////////////// Others //////////////////////////////////////////////////////
// Returns the position of '.' 
int isRealNumber(char* inputRealNum)
{
	int count;
	for(count = 0; count < strlen(inputRealNum); count++) 
	{
		if(inputRealNum[count] == '.') return count;
	}
	return 0; // inputRealNum is an integer
}

int min2Int(int a, int b)
{
	if (a < b) return a;
	return b;
}

int max2Int(int a, int b)
{
	if (a > b) return a;
	return b;
}

// Returns 1 if realNum1 > realNum2 else return 0
int isGreater(char* realNum1, char* realNum2)
{
//	printf("Input isGreater: %s %s\n", realNum1, realNum2);
	if(realNum1[0] == '-' && realNum2[0] == '-')
	{
		shiftLeft(realNum1);
		shiftLeft(realNum2);
		return isGreater(realNum2, realNum1);
	}
	if(realNum1[0] == '-') return 0;
	if(realNum2[0] == '-') return 1;
	
	balanceNumOfDigits(realNum1, realNum2);
	int checker = 0, numLength = strlen(realNum1);
	while(checker < numLength)
	{
		if(realNum1[checker] != realNum2[checker])
		{
			if(realNum1[checker] > realNum2[checker]) 
			{
//				printf("%s is greater than %s\n", realNum1, realNum2);
//				printf("Because %c > %c\n", realNum1[checker], realNum2[checker]);
				return 1;
			}
			else 
			{
//				printf("%s is smaller than %s\n", realNum1, realNum2);
//				printf("Because %c < %c\n", realNum1[checker], realNum2[checker]);
				return 0;
			}
		}
		checker++;
	}
//	printf("%s is equal to %s\n", realNum1, realNum2);
	return 0;
}

void multiplyByNum(int Num, char* realNum, char* result)
{
//	printf("Input multiplyByNum: %d %s %s\n", Num, realNum, result);
	if(Num == 0) strcpy(result, "0");
	else 
	{
		int count;
		char tempResult[MAX_LENGTH];
		strcpy(tempResult, "0");
		for(count = 0; count < Num; count++) addRealNum(tempResult, realNum, tempResult);
		addRealNum(result, tempResult, result);
	}
//	printf("Output multiplyByNum: %d %s %s\n", Num, realNum, result);
}
void multiplyTenfold(char* realNum)
{
	eliminateRightZero(realNum);
	int dotPosition = isRealNumber(realNum);
	if(dotPosition) 
	{
		swapDigits(&realNum[dotPosition], &realNum[dotPosition + 1]);	
		eliminateRightZero(realNum);
		eliminateLeftZero(realNum);
	}
	else
	{
		int numLength = strlen(realNum);
		int count;
		char tempNum[MAX_LENGTH];
		for(count = 0; count < numLength; count++) tempNum[count] = realNum[count];
		tempNum[numLength] = '0';
		tempNum[numLength + 1] = '\0';
		strcpy(realNum, tempNum); 	
	}
}

void divideTenfold(char* realNum)
{
	eliminateRightZero(realNum);
	int dotPosition = isRealNumber(realNum);
	if(dotPosition) 
	{
		swapDigits(&realNum[dotPosition], &realNum[dotPosition - 1]);	
		if(realNum[0] == '.') shiftRight(realNum);
		eliminateRightZero(realNum);
		eliminateLeftZero(realNum);
	}
	else
	{
		int count, numLength = strlen(realNum);
		char tempNum[numLength + 1];
		for(count = 0; count < numLength - 1; count++) tempNum[count] = realNum[count];
		tempNum[numLength - 1] = '.';
		tempNum[numLength] = realNum[numLength - 1];
		tempNum[numLength + 1] = '\0';
		if(tempNum[0] == '.') shiftRight(tempNum);
		strcpy(realNum, tempNum);
	}
}

void swapDigits(char* digitNum1, char* digitNum2)
{
	char tempChar = *digitNum1;
	*digitNum1 = *digitNum2;
	*digitNum2 = tempChar;
}

void swapStrings(char* realNum1, char* realNum2)
{
	char tempStr[strlen(realNum1)];
	strcpy(tempStr, realNum1);
	strcpy(realNum1, realNum2);
	strcpy(realNum2, tempStr);
}
////////////////////////////////////////////////////// Math Operations //////////////////////////////////////////////////////

//Calculate realNum1 - realNum2 with both realNum1 >= 0 and realNum2 >= 0
void subtractRealNum(char* realNum1, char* realNum2, char* result)
{
//	printf("Input subtractRealNum: %s %s %s\n", realNum1, realNum2, result);
	if(strlen(realNum2) == 0) 
	{
		strcpy(result, realNum1);
		return;
	}
	if(strlen(realNum1) == 0) 
	{
		strcpy(result, realNum2);
		return;
	}
	
	if(realNum1[0] == '-' && realNum2[0] == '-')
	{
		shiftLeft(realNum1);
		shiftLeft(realNum2);
		subtractRealNum(realNum2, realNum1, result);
		return;
	}
	if(realNum1[0] == '-')
	{
		shiftLeft(realNum1);
		addRealNum(realNum1, realNum2, result);
		shiftRight(result);
		result[0] = '-';
		return;
	}
	if(realNum2[0] == '-')
	{
		shiftLeft(realNum2);
		addRealNum(realNum1, realNum2, result);
		return;
	}
	if(isGreater(realNum2, realNum1)) 
	{
		subtractRealNum(realNum2, realNum1, result);
		shiftRight(result);
		result[0] = '-';
		return;
	}

	balanceNumOfDigits(realNum1, realNum2);
	int numLength = strlen(realNum1) - 1; 					 // Not calculate '\0' - '\0'			
	int tempNum = 0, carry = 0, resultDotPosition = 0;
	strcpy(result, "");
	char tempResult[MAX_LENGTH];
	tempResult[strlen(realNum1)] = '\0';
//	printf("\n%s\n%s\n\n", realNum1, realNum2);
	// Caculate difference
	while(numLength >= 0)
	{
		if(realNum1[numLength] != '.' && realNum2[numLength] != '.')
		{
			tempNum = convertCharToInt(realNum1[numLength]) - convertCharToInt(realNum2[numLength]) - carry;
			if(tempNum < 0) 
			{
				carry = 1;
				tempNum = tempNum + 10;
			}
			else
			{
				carry = 0;
			}
			tempResult[numLength] = convertIntToChar(tempNum);
		}
		else
		{
			tempResult[numLength] = '.';
			resultDotPosition = numLength;
		}
		numLength--;
	}
	
	eliminateRightZero(tempResult);
	eliminateLeftZero(tempResult);	
	strcpy(result, tempResult);
//	printf("Output subtractRealNum: %s %s %s\n", realNum1, realNum2, result);
}
//Calculate the sum of 2 real numbers
void addRealNum(char* realNum1, char* realNum2, char* result)
{
//	printf("Input addRealNum: %s %s %s\n", realNum1, realNum2, result);
	if(realNum1[0] == '-' && realNum2[0] == '-')
	{
		shiftLeft(realNum1);
		shiftLeft(realNum2);
		addRealNum(realNum1, realNum2, result);
		shiftRight(result);
		result[0] = '-';
		return;
	}
	if(realNum1[0] == '-')
	{
		shiftLeft(realNum1);
		subtractRealNum(realNum2, realNum1, result);
		return;
	}
	if(realNum2[0] == '-')
	{
		shiftLeft(realNum2);
		subtractRealNum(realNum1, realNum2, result);
		return;
	}
	if(strlen(realNum1) == 0) 
	{
		strcpy(result, realNum2);
		return;
	}

	balanceNumOfDigits(realNum1, realNum2);
	int numLength = strlen(realNum1) - 1; 					 // Not calculate '\0' + '\0'			
	int tempNum = 0, carry = 0, resultDotPosition = 0;
	strcpy(result, "");
	char tempResult[MAX_LENGTH];
	tempResult[strlen(realNum1)] = '\0';
	// Caculate Sum
	while(numLength >= 0)
	{
		if(realNum1[numLength] != '.' && realNum2[numLength] != '.')
		{
			tempNum = convertCharToInt(realNum1[numLength]) + convertCharToInt(realNum2[numLength]) + carry;
			if(tempNum > 9) 
			{
				carry = 1;
				tempNum = tempNum % 10;
			}
			else
			{
				carry = 0;
			}
			tempResult[numLength] = convertIntToChar(tempNum);
		}
		else
		{
			tempResult[numLength] = '.';
			resultDotPosition = numLength;
		}
		numLength--;
	}
	if(carry != 0) 
	{
		shiftRight(tempResult);
		tempResult[0] = '1';
	}
	
	eliminateRightZero(tempResult);
	eliminateLeftZero(tempResult);	
	strcpy(result, tempResult);
//	printf("Output addRealNum: %s %s %s\n", realNum1, realNum2, result);
}

// Multiply of 2 real numbers
// Change 123.456 * 456.789 to 123456 * 456789 / 1000000
// 123 * 345 = 100 * 345 + 20 * 345 + 3 * 345  
void multiplyRealNum(char* realNum1, char* realNum2, char* result)
{
//	printf("Input multiplyRealNum: %s %s %s\n", realNum1, realNum2, result);
	if(realNum1[0] == '-' && realNum2[0] == '-')
	{
		shiftLeft(realNum1);
		shiftLeft(realNum2);
	}
	else
	{
		if(realNum1[0] == '-') 
		{
			shiftLeft(realNum1);
			multiplyRealNum(realNum1, realNum2, result);
			shiftRight(result);
			result[0] = '-';
			return;
		}
		if(realNum2[0] == '-') 
		{
			shiftLeft(realNum2);
			multiplyRealNum(realNum1, realNum2, result);
			shiftRight(result);
			result[0] = '-';
			return;
		}
	}
	if(realNum1 == "0" || realNum2 == "0") 
	{
		strcpy(result, "0"); 
		return;
	}
	int dotPosition1 = isRealNumber(realNum1);
	int dotPosition2 = isRealNumber(realNum2);		
	int divider = 0;
	while(isRealNumber(realNum1))
	{
		multiplyTenfold(realNum1);
		divider++;
	}
	while(isRealNumber(realNum2))
	{
		multiplyTenfold(realNum2);
		divider++;
	}
	int numLength1 = strlen(realNum1), count, count2;
	char finalResult[MAX_LENGTH], tempResult[MAX_LENGTH];
	strcpy(finalResult, "0");
	for(count = 0; count < numLength1; count++)
	{
		strcpy(tempResult, "0");
		multiplyByNum(convertCharToInt(realNum1[count]), realNum2, tempResult);	
//		printf("finalResult:%s tempResult:%s\n", finalResult, tempResult);
		for(count2 = 0; count2 < numLength1 - count; count2++) multiplyTenfold(tempResult);
//		printf("finalResult:%s tempResult:%s\n", finalResult, tempResult);
//		printf("Debugger!\n");
		addRealNum(finalResult, tempResult, finalResult);
//		printf("Debugger!\n");
	}	
	for(count = 0; count <= divider; count++) divideTenfold(finalResult);
	eliminateRightZero(finalResult);
	strcpy(result, finalResult);
//	printf("Output multiplyRealNum: %s %s %s %d\n", realNum1, realNum2, result, divider);
}
void divideRealNum(char* realNum1, char* realNum2, char* result)
{
	char divider[MAX_LENGTH];
	int numLength = strlen(realNum1);
	int count = 0, quotient = 0;
	strcpy(result, "0");
	strcpy(divider, "0");
	
	while(count < numLength)
	{
		printf("Count: %d, numLength: %d\n", count, numLength);
		printf("divider: %s, count: %d\n", divider, count);
		while(isGreater(realNum2, divider) && count < numLength)
		{
			pushBack(divider, realNum1[count]);
			count++;
		}
		printf("divider: %s, count: %d\n", divider, count);
		quotient = 0;
		while(isGreater(divider, realNum2))
		{
			quotient++;
			subtractRealNum(divider, realNum2, divider);
		}
		pushBack(result, convertIntToChar(quotient));
	}
	printf("%d %s %s",quotient, divider, result);
}
