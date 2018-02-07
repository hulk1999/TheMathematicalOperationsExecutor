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

	// case + -
	// divide strIn into 2 parts: left and right of the operator, then do the math
	// i.g. calExpression("2*3+4-3") = addRealNum(calExpression("2*3"), calExpression("4-3"));
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
			calExpression(strIn1, strOut1); if(strIn1[0] == '\0') strcpy(strOut1, "0");
			calExpression(strIn2, strOut2); // strOut1 and strOut2 are numbers
			
			// check for MATH ERROR or SYNTAX ERROR
			if ((strOut1[0] == 'M') || (strOut2[0] == 'M')){
				strcpy(strOut, "MATH ERROR!");
				return;
			}
			if ((strOut1[0] == 'S') || (strOut2[0] == 'S')){
				strcpy(strOut, "SYNTAX ERROR!");
				return;
			}

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
			
			// check for MATH ERROR or SYNTAX ERROR
			if ((strOut1[0] == 'M') || (strOut2[0] == 'M')){
				strcpy(strOut, "MATH ERROR!");
				return;
			}
			if ((strOut1[0] == 'S') || (strOut2[0] == 'S')){
				strcpy(strOut, "SYNTAX ERROR!");
				return;
			}
			
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
			
			// check for MATH ERROR or SYNTAX ERROR
			if ((strOut1[0] == 'M') || (strOut2[0] == 'M')){
				strcpy(strOut, "MATH ERROR!");
				return;
			}
			if ((strOut1[0] == 'S') || (strOut2[0] == 'S')){
				strcpy(strOut, "SYNTAX ERROR!");
				return;
			}
			
			// calculate strIn
			powerRealNum(strOut1, strOut2, strOut);
			
			// exit
			return;
		}
	}
	
	// case !
	if (strIn[length - 1] == '!'){
		
		// make temporary string
		char str[MAX_LENGTH], strOut1[MAX_LENGTH];
		makeStrStartEnd(strIn, str, 0, length - 2);
		
		// calculate the number to calculate factorial
		calExpression(str, strOut1);
		
		// check for MATH ERROR or SYNTAX ERROR
			if (strOut1[0] == 'M'){
				strcpy(strOut, "MATH ERROR!");
				return;
			}
			if (strOut1[0] == 'S'){
				strcpy(strOut, "SYNTAX ERROR!");
				return;
			}
			
		// calculate strIn
		getFactorial(strOut1, strOut);
		
		// exit
		return;
	}
	
	// case sqrt()
	if (strIn[0] == 4294967291){
		
		// make temporary string
		char str[MAX_LENGTH], strOut1[MAX_LENGTH], strOut2[MAX_LENGTH];
		makeStrStartEnd(strIn, str, 1, length - 1);
		
		// calculate the calculate to calculate square root
		calExpression(str, strOut1);
		strcpy(strOut2, "0.5");
		
		// check for MATH ERROR or SYNTAX ERROR
			if (strOut1[0] == 'M'){
				strcpy(strOut, "MATH ERROR!");
				return;
			}
			if (strOut1[0] == 'S'){
				strcpy(strOut, "SYNTAX ERROR!");
				return;
			}
			
		// calculate strIn
		powerRealNum(strOut1, strOut2, strOut);
		
		// exit
		return;
	}
	
	//goToXY(1, 28); printf("%u", strIn[0]);
	
	// case "( )" such as "(3+4/6)":
	// delete brackets, return "3+4/6"
	if ((strIn[0] == '(') && (strIn[length - 1] == ')')){
		
		for (i = 0; i <= length - 1; i++){
			if (strIn[i] == '(') countBracket++;
			if (strIn[i] == ')') countBracket--;
			if (countBracket == 0) break; // all open brackets have their matches
		}
		
		// delete brackets
		if (i == length - 1){
			
			// make temporary string
			char str[MAX_LENGTH];
			makeStrStartEnd(strIn, str, 1, length - 2);
			
			// proceed calculating
			calExpression(str, strOut);
			
			// exit
			return;
		}
	}
	
	// case number
	makeStrStartEnd(strIn, strOut, 0, length - 1);
}
