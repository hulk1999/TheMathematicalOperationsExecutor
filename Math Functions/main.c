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
void shiftRight(char* inputRealNum); // unfinished

void eliminateRightZero(char* inputRealNum);
void eliminateLeftZero(char* inputRealNum);

void balanceNumOfDigits(char* realBigNum, char* realSmallNum);

// Others
int isRealNumber(char* inputRealNum);
int min2Int(int a, int b);
int max2Int(int a, int b);

///// Math Operations /////
void addRealNum(char* realNum1, char* realNum2, char* result);
void subtractRealNum(char* realNum1, char* realNum2, char* result);
void multiplyRealNum(char* realNum1, char* realNum2, char* result);
void divideRealNum(char* realNum1, char* realNum2, char* result);

// TODO powerRealNum(char* realNum1, char* realNum2, char* result);
//////////////////////////////////////////////////////


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
void balanceNumOfDigits(char* realBigNum, char* realSmallNum)
{
	// Dealing with the integer part
	int bigLength = strlen(realBigNum), smallLength = strlen(realSmallNum);
	if(isRealNumber(realBigNum)) 
	{
		do 
		{
			bigLength--;
		}while(realBigNum[bigLength] != '.');
	}
	if(isRealNumber(realSmallNum))
	{
		do
		{
			smallLength--;
		}while(realSmallNum[smallLength] != '.');
	}
	
	if(bigLength < smallLength) 
	{
	balanceNumOfDigits(realSmallNum, realBigNum);
	return;
	}
	
	char tempNum[bigLength];
	int count, digitDifference = bigLength - smallLength;
	
	// Initialize the temporary result by adding digitDifference 0 to the left
	for(count = 0; count < digitDifference; count++) tempNum[count] = '0';
	bigLength = strlen(realSmallNum) + digitDifference;
	for(count = digitDifference; count < bigLength; count++) tempNum[count] = realSmallNum[count - digitDifference];
	tempNum[count] = '\0';
	strcpy(realSmallNum, tempNum);

	// Dealing with the floating points
	if(isRealNumber(realBigNum) || isRealNumber(realSmallNum)) 
	{
		bigLength = strlen(realBigNum), smallLength = strlen(realSmallNum);
		if(!isRealNumber(realBigNum)) realBigNum[bigLength] = '.';
		if(!isRealNumber(realSmallNum)) realSmallNum[smallLength] = '.';
	}
	
	if(isRealNumber(realBigNum) && isRealNumber(realSmallNum))
	{
		bigLength = strlen(realBigNum), smallLength = strlen(realSmallNum);
		while(bigLength > smallLength)	
		{
			realSmallNum[smallLength] = '0';
			smallLength++; 
		}
		while(bigLength < smallLength)
		{
			realBigNum[bigLength] = '0';
			bigLength++;
		}
		realBigNum[bigLength] = '\0';
		realSmallNum[smallLength] = '\0';
	}
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
	return 0;
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

////////////////////////////////////////////////////// Math Operations //////////////////////////////////////////////////////
//Calculate realNum1 - realNum2
void subtractRealNum(char* realNum1, char* realNum2, char* result)
{
	if(strlen(realNum2) == 0) 
	{
		strcpy(result, realNum1);
		return;
	}
}
//Calculate the sum of 2 positive real numbers
void addRealNum(char* realNum1, char* realNum2, char* result)
{
	eliminateRightZero(realNum1);
	eliminateLeftZero(realNum1);	
	eliminateRightZero(realNum2);
	eliminateLeftZero(realNum2);
	
	if(realNum1[0] == '-' && realNum2[0] == '-')
	{
		shiftLeft(realNum1);
		shiftLeft(realNum2);
		addRealNum(realNum1, realNum2, result);
		subtractRealNum(result, "", result);
	}
	if(strlen(realNum1) == 0) 
	{
		strcpy(result, realNum2);
		return;
	}
	balanceNumOfDigits(realNum1, realNum2);
	int numLength = strlen(realNum1) - 1; 					 // Not calculate '\0' + '\0'			
	int tempNum = 0, carry = 0, resultDotStorage = 0;
	
	char* tempResult = (char* ) calloc(strlen(realNum1) + 1, sizeof(char));
	
//	printf("\n%s\n%s\n\n", realNum1, realNum2);
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
			resultDotStorage = numLength;
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
}


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
