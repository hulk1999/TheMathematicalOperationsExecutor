#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

const int MAX_LENGTH = 500;

// Make the length of 2 numbers equal by adding 0 to the left of the small number
int convertCharToInt(char inputChar)
{
	return (int)inputChar - 48;
}
char convertIntToChar(int inputNum)
{
	return (char)(inputNum + 48);
}
void balanceNumOfDigits(char* intBigNum, char* intSmallNum)
{
	//printf("%s\n%s", intBigNum, intSmallNum);
	int bigLength = strlen(intBigNum), smallLength = strlen(intSmallNum);
	if(bigLength < smallLength) 
	{
	balanceNumOfDigits(intSmallNum, intBigNum);
	return;
	}
	char tempNum[bigLength];
	
	int count, digitDifference = bigLength - smallLength;
	for(count = 0; count < digitDifference; count++) tempNum[count] = '0';
	for(count = digitDifference; count < bigLength; count++) tempNum[count] = intSmallNum[count - digitDifference];
	for(count = 0; count < bigLength; count++) intSmallNum[count] = tempNum[count]; 
	intSmallNum[count] = '\0';
}

void addIntegerNum(char* intNum1, char* intNum2, char* result)
{
	balanceNumOfDigits(intNum1, intNum2);
	int numLength = strlen(intNum1) - 1, tempNum = 0, carry = 0;
	while(numLength >= 0)
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
		result[numLength] = convertIntToChar(tempNum);
		numLength--;
	}
}
int main(int argc, char *argv[]) {
	char inputNum1[MAX_LENGTH], inputNum2[MAX_LENGTH], result[MAX_LENGTH];
	
	scanf("%s %s", &inputNum1, &inputNum2);
	addIntegerNum(inputNum1, inputNum2, result);
	printf("Num1: %s\nNum2: %s\nResult: %s", inputNum1, inputNum2, result);
	return 0;
}
