#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */


// TODO 
// Fix this case 0.000 + 0

const int MAX_LENGTH = 500;

int convertCharToInt(char inputChar)
{
	return (int)inputChar - 48;
}
char convertIntToChar(int inputNum)
{
	return (char)(inputNum + 48);
}

// Returns the position of '.'
int isRealNumber(char* inputNum)
{
	int count;
	for(count = 0; count < strlen(inputNum); count++) 
	{
		if(inputNum[count] == '.') return count;
	}
	return 0;
}
//////////////////////////////////////////////
// Change 1.000000000 to 1
void eliminateRightZero(char* inputRealNum)
{
	int numLength = strlen(inputRealNum);
	while(inputRealNum[numLength] != '.' && numLength > 0)
	{
		if(inputRealNum[numLength] == '0' || inputRealNum[numLength] == '.' || inputRealNum[numLength] == '\0') inputRealNum[numLength] = '\0';
		else numLength = 0;
		numLength--;
	}
}
/////////////////////////////////////////////
// Change 00001 to 1
void eliminateLeftZero(char* inputRealNum)
{
	int numOfZero = 0, count, numLength, dotStorage;
	numLength = strlen(inputRealNum);
	dotStorage = isRealNumber(inputRealNum);
	while(numOfZero < dotStorage && inputRealNum[numOfZero] == '0' && numOfZero < numLength) numOfZero++;
	for(count = 0; count < numLength; count++) inputRealNum[count] = inputRealNum[numOfZero + count];
}
void balanceNumOfDigits(char* realBigNum, char* realSmallNum)
{
//	printf("\n%s\n%s\n\n", realBigNum, realSmallNum);
	
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

//Calculate the sum of 2 positive real numbers
void addRealNum(char* intNum1, char* intNum2, char* result)
{
//	eliminateLeftZero(intNum1);
//	eliminateRightZero(intNum1);
//	eliminateLeftZero(intNum2);
//	eliminateRightZero(intNum2);
	if(strlen(intNum1) == 0) 
	{
		strcpy(result, intNum2);
		return;
	}
	balanceNumOfDigits(intNum1, intNum2);
	int numLength = strlen(intNum1) - 1, tempNum = 0, carry = 0, resultDotStorage = MAX_LENGTH;
	char* tempResult = (char* ) calloc(strlen(intNum1) + 1, sizeof(char));
	
//	printf("\n%s\n%s\n\n", intNum1, intNum2);
	// Caculate Sum
	while(numLength >= 0)
	{
		if(intNum1[numLength] != '.' && intNum2[numLength] != '.')
		{
			tempNum = convertCharToInt(intNum1[numLength]) + convertCharToInt(intNum2[numLength]) + carry;
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


