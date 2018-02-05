#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_LENGTH 500


// TODO MATH ERROR!

//////////////////// Declaration /////////////////////

///// Functionalities /////

// Conversion
int convertCharToInt(char inputChar);
char convertIntToChar(int inputNum);

double convertStringToFloat(char* inputChar);
void convertFloatToString(double inputFloat, char* result);

// Shifting
void shiftLeft(char* inputRealNum);
void shiftRight(char* inputRealNum); // Default: inputRealNum[0] = '0'

void pushBack(char* inputRealNum, char newChar);
void popBack(char* inputRealNum);
void eliminateRightZero(char* inputRealNum);
void eliminateLeftZero(char* inputRealNum);
void eliminateAllZeros(char* inputRealNum);

void balanceNumOfDigits(char* realBigNum, char* realSmallNum);

// Others
int isRealNumber(char* inputRealNum);
int min2Int(int a, int b);
int max2Int(int a, int b);
int compareRealNum(char* realNum1	, char* realNum2);

void multiplyByNum(int Num, char* realNum, char* result);
void multiplyTenfold(char* realNum);
void divideTenfold(char* realNum);

void swapDigits(char* digitNum1, char* digitNum2);
void swapStrings(char* realNum1, char* realNum2);

///// Math Operations /////
void addRealNum(char* realNum1, char* realNum2, char* result); // It's best not to pass literal strings such as ""123.456"" to the parameters
void subtractRealNum(char* realNum1, char* realNum2, char* result);
void multiplyRealNum(char* realNum1, char* realNum2, char* result);
void divideRealNum(char* dividend, char* divisor, char* result);
void powerRealNum(char* realNum1, char* realNum2, char* result);

//////////////////////////////////////////////////////


////////////////////////////////////////////////////// MAIN //////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
	char inputNum1[MAX_LENGTH], inputNum2[MAX_LENGTH], result[MAX_LENGTH];
	strcpy(result, "");
	do
	{
	scanf("%s %s", &inputNum1, &inputNum2);

	addRealNum(inputNum1, inputNum2, result);
	printf("%s + %s = %s\n\n", inputNum1, inputNum2, result);
	
	subtractRealNum(inputNum1, inputNum2, result);
	printf("%s - %s = %s\n\n", inputNum1, inputNum2, result);
	
	multiplyRealNum(inputNum1, inputNum2, result);
	printf("%s * %s = %s\n\n", inputNum1, inputNum2, result);
	
	divideRealNum(inputNum1, inputNum2, result);
	printf("%s / %s = %s\n\n", inputNum1, inputNum2, result);

	powerRealNum(inputNum1, inputNum2, result);
	printf("%s ^ %s = %s\n\n", inputNum1, inputNum2, result);
	
//	scanf("%s", &inputNum1);	
//	float fl = convertStringToFloat(inputNum1);
//	printf("%lf\n", convertStringToFloat(inputNum1));
//	convertFloatToString(fl, inputNum2);
//	printf("%s\n\n", inputNum2);
//	printf("%s\n\n", inputNum2);
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


double convertStringToFloat(char* inputChar)
{
	int count = 0, negative = 0;
	double result = 0;

	if(inputChar[0] == '-')
	{
		negative = 1;
		shiftLeft(inputChar);
		
	}
	if(strcmp(inputChar, "0") == 0) return 0.0;
	if(!isRealNumber(inputChar))
	{
		pushBack(inputChar, '.');
		pushBack(inputChar, '0');
	}
	
	int numLength = strlen(inputChar);
	int multiplyer, dotPosition = isRealNumber(inputChar);;
	for(count = 0; count < numLength; count++) 
	{
		multiplyer = dotPosition - count;
		if(inputChar[count] != '.')
			result += convertCharToInt(inputChar[count]) * pow(10, multiplyer - (multiplyer > 0));
	}
	if(negative)
	{
		result = - result;
		shiftRight(inputChar);
		inputChar[0] = '-';
	}
	return result;
}

void convertFloatToString(double inputFloat, char* result)
{
	snprintf(result, MAX_LENGTH, "%lf", inputFloat); // stdlib.h
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
	int negative = (inputRealNum[0] == '-');
	if(!isRealNumber(inputRealNum)) return;
	if(negative) shiftLeft(inputRealNum);
	
	int dotPosition = isRealNumber(inputRealNum);
	while(numLength >= dotPosition && (inputRealNum[numLength] == '0' || inputRealNum[numLength] == '\0' 
										|| inputRealNum[numLength] == '.')) 
	{
		inputRealNum[numLength] = '\0'; 
		numLength--;
	}
	
	if(negative && (strcmp(inputRealNum, "0") != 0) )
	{
		shiftRight(inputRealNum);
		inputRealNum[0] = '-';
	}
//	printf("Output eliminateRightZero: %s\n", inputRealNum);
}
// Change 00001 to 1
void eliminateLeftZero(char* inputRealNum)
{
//	printf("Input eliminateLeftZero: %s\n", inputRealNum);
	int count, negative = 0, numLength = strlen(inputRealNum);
	if(inputRealNum[0] == '-') 
	{
		shiftLeft(inputRealNum);
		negative = 1;
	}
	
	if(inputRealNum[0] == '.') shiftRight(inputRealNum);
	
	while(inputRealNum[0] == '0' &&  isRealNumber(inputRealNum) > 1) shiftLeft(inputRealNum);
	if(!isRealNumber(inputRealNum))
	while(inputRealNum[0] == '0' &&  strlen(inputRealNum) > 1) shiftLeft(inputRealNum);
	
	if(negative)
	{
		shiftRight(inputRealNum);
		inputRealNum[0] = '-'; 
	}
//	printf("Output eliminateLeftZero: %s\n", inputRealNum);
}

void eliminateAllZeros(char* inputRealNum)
{
	eliminateLeftZero(inputRealNum);
	eliminateRightZero(inputRealNum);
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

// Returns 1 if realNum1 > realNum2 
// Returns 0 if realNum1 == realNum2;
// Returns -1 if realNum1 < realNum2
int compareRealNum(char* realNum1, char* realNum2)
{
//	printf("Input compareRealNum: %s %s\n", realNum1, realNum2);
	
	if(realNum1[0] == '-' && realNum2[0] == '-')
	{
		shiftLeft(realNum1);
		shiftLeft(realNum2);
		return compareRealNum(realNum2, realNum1);
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
				eliminateAllZeros(realNum1);
				eliminateAllZeros(realNum2);
				return 1;
			}
			else 
			{
				eliminateAllZeros(realNum1);
				eliminateAllZeros(realNum2);
				return -1;
			}
		}
		checker++;
	}
	eliminateAllZeros(realNum1);
	eliminateAllZeros(realNum2);
	return 0;
}

void multiplyByNum(int Num, char* realNum, char* result)
{
//	printf("Input multiplyByNum: %d %s %s\n", Num, realNum, result);
	
	char resultSaver[MAX_LENGTH];
	if(Num == 0) strcpy(result, "0");
	else 
	{
		int count;
		char tempResult[MAX_LENGTH];
		strcpy(tempResult, "0");
		for(count = 0; count < Num; count++) 
		{
			addRealNum(tempResult, realNum, resultSaver);
			strcpy(tempResult, resultSaver);
		}
		addRealNum(result, tempResult, resultSaver);
		strcpy(result, resultSaver);
	}
//	printf("Output multiplyByNum: %d %s %s\n", Num, realNum, result);
}
void multiplyTenfold(char* realNum)
{
	int dotPosition = isRealNumber(realNum);
	if(dotPosition) 
	{
		swapDigits(&realNum[dotPosition], &realNum[dotPosition + 1]);	
		if(dotPosition + 1 == strlen(realNum) - 1) realNum[dotPosition + 1] = '\0';
	}
	else
	{
		pushBack(realNum, '0');
	}
	eliminateAllZeros(realNum);
}

void divideTenfold(char* realNum)
{
//	printf("Input divideTenfold: %s\n", realNum);
	eliminateRightZero(realNum);
	int dotPosition = isRealNumber(realNum);
	if(dotPosition) 
	{
		swapDigits(&realNum[dotPosition], &realNum[dotPosition - 1]);	
		if(realNum[0] == '.') shiftRight(realNum);
	}
	else
	{
		char tempChar = realNum[strlen(realNum) - 1];
		realNum[strlen(realNum) - 1] = '.';
		pushBack(realNum, tempChar);
	}
	eliminateAllZeros(realNum);
//	printf("Output divideTenfold: %s\n", realNum);
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

//Calculate the sum of 2 real numbers
void addRealNum(char* realNum1, char* realNum2, char* result)
{
//	printf("Input addRealNum: %s %s %s\n", realNum1, realNum2, result);
	eliminateAllZeros(realNum1);
	eliminateAllZeros(realNum2);
	
	char originalValue1[MAX_LENGTH], originalValue2[MAX_LENGTH];
	strcpy(originalValue1, realNum1);
	strcpy(originalValue2, realNum2);

	if(realNum1[0] == '-' && realNum2[0] == '-')
	{
		shiftLeft(realNum1);
		shiftLeft(realNum2);
		addRealNum(realNum1, realNum2, result);
		shiftRight(result);
		result[0] = '-';
		strcpy(realNum1, originalValue1);
	 	strcpy(realNum2, originalValue2);
		return;
	}
	if(realNum1[0] == '-')
	{
		shiftLeft(realNum1);
		subtractRealNum(realNum2, realNum1, result);
		strcpy(realNum1, originalValue1);
		strcpy(realNum2, originalValue2);
		return;
	}
	if(realNum2[0] == '-')
	{
		shiftLeft(realNum2);
		subtractRealNum(realNum1, realNum2, result);
		strcpy(realNum1, originalValue1);
		strcpy(realNum2, originalValue2);
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
	
	strcpy(realNum1, originalValue1);
	strcpy(realNum2, originalValue2);
	
	eliminateAllZeros(tempResult);	
	strcpy(result, tempResult);
//	printf("Output addRealNum: %s %s %s\n", realNum1, realNum2, result);
}

//Calculate realNum1 - realNum2 
void subtractRealNum(char* realNum1, char* realNum2, char* result)
{
//	printf("Input subtractRealNum: %s %s %s\n", realNum1, realNum2, result);
	eliminateAllZeros(realNum1);
	eliminateAllZeros(realNum2);

	char originalValue1[MAX_LENGTH], originalValue2[MAX_LENGTH];
	strcpy(originalValue1, realNum1);
	strcpy(originalValue2, realNum2);

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
		strcpy(realNum1, originalValue1);
		strcpy(realNum2, originalValue2);
		return;
	}
	if(realNum1[0] == '-')
	{
		shiftLeft(realNum1);
		addRealNum(realNum1, realNum2, result);
		shiftRight(result);
		result[0] = '-';
		strcpy(realNum1, originalValue1);
		strcpy(realNum2, originalValue2);
		return;
	}
	if(realNum2[0] == '-')
	{
		shiftLeft(realNum2);
		addRealNum(realNum1, realNum2, result);
		strcpy(realNum1, originalValue1);
		strcpy(realNum2, originalValue2);
		return;
	}
	if(compareRealNum(realNum2, realNum1) == 1) 
	{
		subtractRealNum(realNum2, realNum1, result);
		shiftRight(result);
		result[0] = '-';
		strcpy(realNum1, originalValue1);
		strcpy(realNum2, originalValue2);
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
	
	strcpy(realNum1, originalValue1);
	strcpy(realNum2, originalValue2);
	
	eliminateAllZeros(tempResult);	
	strcpy(result, tempResult);
//	printf("Output subtractRealNum: %s %s %s\n", realNum1, realNum2, result);
}

// Multiply of 2 real numbers
// Change 123.456 * 456.789 to 123456 * 456789 / 1000000
// 123 * 345 = 100 * 345 + 20 * 345 + 3 * 345  
void multiplyRealNum(char* realNum1, char* realNum2, char* result)
{
//	printf("Input multiplyRealNum: %s %s %s\n", realNum1, realNum2, result);
	eliminateAllZeros(realNum1);
	eliminateAllZeros(realNum2);

	char originalValue1[MAX_LENGTH], originalValue2[MAX_LENGTH];
	strcpy(originalValue1, realNum1);
	strcpy(originalValue2, realNum2);


	if(realNum1[0] == '-' && realNum2[0] == '-')
	{
		shiftLeft(realNum1);
		shiftLeft(realNum2);
		multiplyRealNum(realNum1, realNum2, result);
		strcpy(realNum1, originalValue1);
		strcpy(realNum2, originalValue2);
		return;
	}
	else
	{
		if(realNum1[0] == '-') 
		{
			shiftLeft(realNum1);
			multiplyRealNum(realNum1, realNum2, result);
			shiftRight(result);
			result[0] = '-';
			strcpy(realNum1, originalValue1);
			strcpy(realNum2, originalValue2);
			return;
		}
		if(realNum2[0] == '-') 
		{
			shiftLeft(realNum2);
			multiplyRealNum(realNum1, realNum2, result);
			shiftRight(result);
			result[0] = '-';
			strcpy(realNum1, originalValue1);
			strcpy(realNum2, originalValue2);
			return;
		}
	}
	if(strcmp(realNum1, "0") == 0 || strcmp(realNum2, "0") == 0)
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
//	printf("DB: %s %s %d\n", realNum1, realNum2, divider);
	int numLength1 = strlen(realNum1), count, count2;
	char finalResult[MAX_LENGTH], tempResult[MAX_LENGTH], resultSaver[MAX_LENGTH];
	strcpy(finalResult, "0");
	for(count = 0; count < numLength1; count++)
	{
		strcpy(tempResult, "0");
		multiplyByNum(convertCharToInt(realNum1[count]), realNum2, tempResult);	
//		printf("1 multiplyRealNum: %s\n", tempResult);
		for(count2 = 0; count2 < numLength1 - count; count2++) multiplyTenfold(tempResult);
//		printf("2 multiplyRealNum: %s\n", tempResult);
		addRealNum(finalResult, tempResult, resultSaver);
		strcpy(finalResult, resultSaver);
//		printf("3 multiplyRealNum: %s\n", finalResult);
	}	
	for(count = 0; count <= divider; count++) 
	{
	divideTenfold(finalResult);
//	printf("finalResult %s\n", finalResult);
	}
	strcpy(realNum1, originalValue1);
	strcpy(realNum2, originalValue2);
	
	eliminateAllZeros(finalResult);
	strcpy(result, finalResult);
//	printf("Output multiplyRealNum: %s %s %s\n", realNum1, realNum2, result);
}

void divideRealNum(char* dividend, char* divisor, char* result)
{
	eliminateAllZeros(dividend);
	eliminateAllZeros(divisor);
	
	char originalValue1[MAX_LENGTH], originalValue2[MAX_LENGTH];
	strcpy(originalValue1, dividend);
	strcpy(originalValue2, divisor);
	
	if(dividend[0] == '-' && divisor[0] == '-')
	{
		shiftLeft(dividend);
		shiftLeft(divisor);
		divideRealNum(dividend, divisor, result);
		strcpy(dividend, originalValue1);
		strcpy(divisor, originalValue2);
		return;
	}
	else
	{
		if(dividend[0] == '-') 
		{
			shiftLeft(dividend);
			divideRealNum(dividend, divisor, result);
			shiftRight(result);
			result[0] = '-';
			strcpy(dividend, originalValue1);
			strcpy(divisor, originalValue2);
			return;
		}
		if(divisor[0] == '-') 
		{
			shiftLeft(divisor);
			divideRealNum(dividend, divisor, result);
			shiftRight(result);
			result[0] = '-';
			strcpy(dividend, originalValue1);
			strcpy(divisor, originalValue2);
			return;
		}
	}
	if(strcmp(divisor, "0") == 0)
	{
		strcpy(result, "MATH ERROR! (Divided by Zero!)");
		strcpy(dividend, originalValue1);
		strcpy(divisor, originalValue2);
		return;
	}
	
	int tenFold = 0;
	
	while(isRealNumber(dividend))
	{
		multiplyTenfold(dividend);
		tenFold--;
	}
	while(isRealNumber(divisor))
	{
		multiplyTenfold(divisor);
		tenFold++;
	}
	
	char carrier[MAX_LENGTH], tempResult[MAX_LENGTH], finalResult[MAX_LENGTH];
	int numLength = strlen(dividend);
	int count = 0, quotient = 0;
	strcpy(result, "0");
	strcpy(tempResult, "0");
	strcpy(finalResult, "");
	strcpy(carrier, "0");
	
	while(compareRealNum(divisor, carrier) == 1 && count < numLength && dividend[count] != '\0')
	{
		eliminateAllZeros(dividend);
		pushBack(carrier, dividend[count]);
		count++;
		quotient = 0;
		while(compareRealNum(carrier, divisor) != -1) 
		{
			quotient++;
//			printf("Before: %s\n", carrier);
			subtractRealNum(carrier, divisor, tempResult);
			strcpy(carrier, tempResult);
//			printf("After: %s\n", carrier);	
		} 
		pushBack(finalResult, convertIntToChar(quotient));	
	}
	if(carrier[0] != '0') 
	{
		pushBack(finalResult, '.');
		numLength = strlen(finalResult);
			while(compareRealNum(divisor, carrier) == 1 && numLength < MAX_LENGTH && carrier[0] != '0')
			{
				pushBack(carrier, '0');
				numLength++;
				quotient = 0;
				while(compareRealNum(carrier, divisor) != -1) 
				{
					quotient++;
					subtractRealNum(carrier, divisor, tempResult);
					strcpy(carrier, tempResult);
				} 
				pushBack(finalResult, convertIntToChar(quotient));	
			}		
	}
	
	if(tenFold > 0)
	{
		for(count = 0; count < tenFold; count++) multiplyTenfold(finalResult);
	}
	else
	{
		for(count = 0; count > tenFold; count--) divideTenfold(finalResult);
	}
	strcpy(dividend, originalValue1);
	strcpy(divisor, originalValue2);
	
	eliminateAllZeros(finalResult);
	strcpy(result, finalResult);
}

void powerRealNum(char* realNum1, char* realNum2, char* result)
{
	eliminateAllZeros(realNum1);
	eliminateAllZeros(realNum2);
	if((strcmp(realNum1, "0") == 0) && (strcmp(realNum2, "0") == 0))
	{
		strcpy(result, "MATH ERROR!(0^0)");
		return;
	}
	int negative = 0;
	if(realNum2[0] == '-')
	{
		negative = 1;
		shiftLeft(realNum2);
	}
	if(isRealNumber(realNum2)) 
	{
		float floatTempResult = pow(convertStringToFloat(realNum1), convertStringToFloat(realNum2));
		convertFloatToString(floatTempResult, result);
		return;
	}
	else
	{
		char count[MAX_LENGTH];
		char tempResult[MAX_LENGTH], resultSaver[MAX_LENGTH];
		char numberOne[MAX_LENGTH];
		strcpy(count, "0");
		strcpy(tempResult, "1");
		strcpy(numberOne, "1");

		while(compareRealNum(realNum2, count) > 0)
		{
			multiplyRealNum(tempResult, realNum1, resultSaver);
			strcpy(tempResult, resultSaver);
			addRealNum(count, numberOne, resultSaver);
			strcpy(count, resultSaver);
//			printf("%s %s\n", count, tempResult);
		}
		if(negative)
		{
			shiftRight(realNum2);
			realNum2[0] = '-';
			divideRealNum(numberOne, tempResult, resultSaver);
			strcpy(tempResult, resultSaver);
		}
		strcpy(result, tempResult);
	}	
}
