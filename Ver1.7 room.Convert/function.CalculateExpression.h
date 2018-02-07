#define MAX_LENGTH 500

// make strOut = strIn[start] to strIn[end]
void makeStrStartEnd(char strIn[MAX_LENGTH], char strOut[MAX_LENGTH], int start, int end){
	int i;
	for (i = start; i <= end; i++) strOut[i - start] = strIn[i];
	strOut[end - start + 1] = '\0';
}

// delete spaces

// calculate expression
void calExpression(char strIn[MAX_LENGTH], char strOut[MAX_LENGTH]){
	
	// initialize
	int length = strlen(strIn);
	int countBracket = 0; // work as a stack, +1 for '(', -1 for ')'
	int i;
	
	// case "( )" such as "(3+4/6)" or "(3+2)*(4-9)":
	// fisrt case: delete brackets, return "3+4/6"
	// second case: ignore
	if ((strIn[0] == '(') && (strIn[length - 1] == ')')){
		
		for (i = 0; i <= length - 1; i++){
			if (strIn[i] == '(') countBracket++;
			if (strIn[i] == ')') countBracket--;
			if (countBracket == 0) break; // all open brackets have their matches
		}
		
		// first case
		if (i == length - 1){
			
			// make string
			char str[MAX_LENGTH];
			makeStrStartEnd(strIn, str, 1, length - 2);
			
			// recursion
			calExpression(str, strOut);
			return;
		}
	}

	// case + -
	// divide strIn into 2 parts: left and right of the operator, then do the math
	// i.g. calExpression("2*3+4-3") == addRealNum(calExpression("2*3"), calExpression("4-3"));
	for (i = 0; i <= length - 1; i++){
		
		// count bracket
		if (strIn[i] == '(') countBracket++;
		if (strIn[i] == ')') countBracket--;
		
		// check + -
		if (((strIn[i] == '+') || (strIn[i] == '-')) && (countBracket == 0)){
			
			// divide strIn to 2 parts: strIn1 and strIn2
			char strIn1[MAX_LENGTH], strIn2[MAX_LENGTH], strOut1[MAX_LENGTH], strOut2[MAX_LENGTH];
			makeStrStartEnd(strIn, strIn1, 0, i - 1);
			makeStrStartEnd(strIn, strIn2, i + 1, length - 1);
			
			// calculate strIn1 and strIn2
			calExpression(strIn1, strOut1);
			calExpression(strIn2, strOut2); // strOut1 and strOut2 are numbers

			// calculate strIn
			if (strIn[i] == '+') addRealNum(strOut1, strOut2, strOut);
			else subtractRealNum(strOut1, strOut2, strOut);
			
			// exit
			return;
		}
	}
	
	// case x /
	for (i = 0; i <= length - 1; i++){
		
		// count bracket
		if (strIn[i] == '(') countBracket++;
		if (strIn[i] == ')') countBracket--;
		
		// check x /
		if (((strIn[i] == 'x') || (strIn[i] == '/')) && (countBracket == 0)){
			
			// divide strIn into 2 parts: strIn1 and strIn2
			char strIn1[MAX_LENGTH], strIn2[MAX_LENGTH], strOut1[MAX_LENGTH], strOut2[MAX_LENGTH];
			makeStrStartEnd(strIn, strIn1, 0, i - 1);
			makeStrStartEnd(strIn, strIn2, i + 1, length - 1);
			
			// calculate strIn1 and strIn2
			calExpression(strIn1, strOut1);
			calExpression(strIn2, strOut2);
			
			// calculate strIn
			if (strIn[i] == 'x') multiplyRealNum(strOut1, strOut2, strOut);
			else divideRealNum(strOut1, strOut2, strOut);
			
			// exit
			return;
		}
	}
	
	// case ^
	for (i = 0; i <= length - 1; i++){
		
		// count bracket
		if (strIn[i] == '(') countBracket++;
		if (strIn[i] == ')') countBracket--;
		
		// check ^
		if ((strIn[i] == '^') && (countBracket == 0)){
			
			// divide strIn to 2 parts: strIn1 and strIn2
			char strIn1[MAX_LENGTH], strIn2[MAX_LENGTH], strOut1[MAX_LENGTH], strOut2[MAX_LENGTH];
			makeStrStartEnd(strIn, strIn1, 0, i - 1);
			makeStrStartEnd(strIn, strIn2, i + 1, length - 1);
			
			// calculate strIn1 and strIn2
			calExpression(strIn1, strOut1);
			calExpression(strIn2, strOut2);
			
			// calculate strIn
			powerRealNum(strOut1, strOut2, strOut);
			
			// exit
			return;
		}
	}
	
	// case number
	makeStrStartEnd(strIn, strOut, 0, length - 1);
}
