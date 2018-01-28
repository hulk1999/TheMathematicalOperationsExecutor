#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 500


/// TODO Rewrite blanceNumOfDigits so that it won't swap the numbers!!

//////////////////// Declaration /////////////////////

///// Functionalities /////

// Conversion
int convertCharToInt(char inputChar);
char convertIntToChar(int inputNum);

// Shifting
void shiftLeft(char* inputRealNum);
void shiftRight(char* inputRealNum);

void eliminateRightZero(char* inputRealNum);
void eliminateLeftZero(char* inputRealNum);

void balanceNumOfDigits(char* realBigNum, char* realSmallNum);

// Others
int isRealNumber(char* inputRealNum);
int min2Int(int a, int b);
int max2Int(int a, int b);
int isGreater(char* realNum1, char* realNum2);
void swapStrings(char* realNum1, char* realNum2);

///// Math Operations /////
void addRealNum(char* realNum1, char* realNum2, char* result);
void subtractRealNum(char* realNum1, char* realNum2, char* result);

/* TODO
	void multiplyRealNum(char* realNum1, char* realNum2, char* result);
	void divideRealNum(char* realNum1, char* realNum2, char* result);
	void powerRealNum(char* realNum1, char* realNum2, char* result);
*/
//////////////////////////////////////////////////////


////////////////////////////////////////////////////// MAIN //////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
	char inputNum1[MAX_LENGTH], inputNum2[MAX_LENGTH], result[MAX_LENGTH];
	do
	{
	scanf("%s %s", &inputNum1, &inputNum2);
	addRealNum(inputNum1, inputNum2, result);
	printf("%s\n\n", result);
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
void shiftRight(char* inputRealNum)
{
	int count, numLength = strlen(inputRealNum);
	char tempRealNum[numLength + 1];
	for(count = 0; count < numLength; count++)
	{
		tempRealNum[count + 1] = inputRealNum[count];
	}
	tempRealNum[numLength + 1] = '\0';
	strcpy(inputRealNum, tempRealNum);
}
// Change 1.000000000 to 1
void eliminateRightZero(char* inputRealNum)
{
	int numLength = strlen(inputRealNum);
	int dotPosition = isRealNumber(inputRealNum);
	if(dotPosition == 0) return;
	while(numLength >= dotPosition && (inputRealNum[numLength] == '0' || inputRealNum[numLength] == '\0' 
										|| inputRealNum[numLength] == '.')) 
	{
		inputRealNum[numLength] = '\0'; 
		numLength--;
	}
}
// Change 00001 to 1
void eliminateLeftZero(char* inputRealNum)
{
	int count, numLength, dotPosition;
	numLength = strlen(inputRealNum);
	dotPosition = isRealNumber(inputRealNum);
	while(inputRealNum[0] == '0' && dotPosition + 2 <= numLength )
	{
		shiftLeft(inputRealNum);
		numLength = strlen(inputRealNum);
	}
}
// change 123.456 + 0 to 123.456 + 000.000
void balanceNumOfDigits(char* realLongNum, char* realShortNum)
{
	printf("Input balanceNumOfDigits: %s %s\n", realLongNum, realShortNum);
	// Dealing with the integer part
	int bigLength = strlen(realLongNum), smallLength = strlen(realShortNum);
	if(isRealNumber(realLongNum)) 
	{
		do 
		{
			bigLength--;
		}while(realLongNum[bigLength] != '.');
	}
	if(isRealNumber(realShortNum))
	{
		do
		{
			smallLength--;
		}while(realShortNum[smallLength] != '.');
	}
	
	if(bigLength < smallLength) 
	{
	balanceNumOfDigits(realShortNum, realLongNum);
	swapStrings(realShortNum, realLongNum); // This prevents changing the original values
	return;
	}
	
	char tempNum[bigLength];
	int count, digitDifference = bigLength - smallLength;
	
	// Initialize the temporary result by adding digitDifference 0 to the left
	for(count = 0; count < digitDifference; count++) tempNum[count] = '0';
	bigLength = strlen(realShortNum) + digitDifference;
	for(count = digitDifference; count < bigLength; count++) tempNum[count] = realShortNum[count - digitDifference];
	tempNum[count] = '\0';
	strcpy(realShortNum, tempNum);

	// Dealing with the floating points
	if(isRealNumber(realLongNum) || isRealNumber(realShortNum)) 
	{
		bigLength = strlen(realLongNum), smallLength = strlen(realShortNum);
		if(!isRealNumber(realLongNum)) realLongNum[bigLength] = '.';
		if(!isRealNumber(realShortNum)) realShortNum[smallLength] = '.';
	}
	
	if(isRealNumber(realLongNum) && isRealNumber(realShortNum))
	{
		bigLength = strlen(realLongNum), smallLength = strlen(realShortNum);
		while(bigLength > smallLength)	
		{
			realShortNum[smallLength] = '0';
			smallLength++; 
		}
		while(bigLength < smallLength)
		{
			realLongNum[bigLength] = '0';
			bigLength++;
		}
		realLongNum[bigLength] = '\0';
		realShortNum[smallLength] = '\0';
	}
	printf("Output balanceNumOfDigits: %s %s\n", realLongNum, realShortNum);
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
	printf("Input isGreater: %s %s\n", realNum1, realNum2);
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
				printf("%s is greater than %s\n", realNum1, realNum2);
//				printf("Because %c > %c\n", realNum1[checker], realNum2[checker]);
				return 1;
			}
			else 
			{
				printf("%s is smaller than %s\n", realNum1, realNum2);
//				printf("Because %c < %c\n", realNum1[checker], realNum2[checker]);
				return 0;
			}
		}
		checker++;
	}
//	printf("%s is equal to %s\n", realNum1, realNum2);
	return 0;
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
	printf("Input subtractRealNum: %s %s %s\n", realNum1, realNum2, result);
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
	
	if(isGreater(realNum2, realNum1)) 
	{
		printf("%s is greater than %s\n", realNum2, realNum1);
		subtractRealNum(realNum2, realNum1, result);
		shiftRight(result);
		result[0] = '-';
		return;
	}

	eliminateRightZero(realNum1);
	eliminateLeftZero(realNum1);	
	eliminateRightZero(realNum2);
	eliminateLeftZero(realNum2);
		
	balanceNumOfDigits(realNum1, realNum2);
	int numLength = strlen(realNum1) - 1; 					 // Not calculate '\0' - '\0'			
	int tempNum = 0, carry = 0, resultDotPosition = 0;
	
	char* tempResult = (char* ) calloc(strlen(realNum1) + 1, sizeof(char));
	
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
	printf("Output subtractRealNum: %s %s %s\n", realNum1, realNum2, result);
}
//Calculate the sum of 2 positive real numbers
void addRealNum(char* realNum1, char* realNum2, char* result)
{
//	printf("Input addRealNum: %s %s %s\n", realNum1, realNum2, result);
	
	if(realNum1[0] == '-' && realNum2[0] == '-')
	{
		shiftLeft(realNum1);
		shiftLeft(realNum2);
		addRealNum(realNum1, realNum2, result);
		subtractRealNum(result, "", result);
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

	eliminateRightZero(realNum1);
	eliminateLeftZero(realNum1);	
	eliminateRightZero(realNum2);
	eliminateLeftZero(realNum2);
		
	balanceNumOfDigits(realNum1, realNum2);
	int numLength = strlen(realNum1) - 1; 					 // Not calculate '\0' + '\0'			
	int tempNum = 0, carry = 0, resultDotPosition = 0;
	
	char* tempResult = (char* ) calloc(strlen(realNum1) + 1, sizeof(char));
	
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
		numLength = strlen(tempResult);
		do 
		{
			tempResult[numLength] = tempResult[numLength - 1];
			numLength--;
		} while(numLength > 0);
		tempResult[0] = convertIntToChar(carry);
	}
	
	eliminateRightZero(tempResult);
	eliminateLeftZero(tempResult);	
	strcpy(result, tempResult);
//	printf("Output addRealNum: %s %s %s\n", realNum1, realNum2, result);
}

