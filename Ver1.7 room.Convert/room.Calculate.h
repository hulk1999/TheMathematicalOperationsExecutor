void printFirstLineTable(int num){
	int i;
	printf("%c", 218);
	for (i = 1; i < num; i++) printf("%c%c%c%c%c%c%c%c", 196, 196, 196, 196, 196, 196, 196, 194);
	printf("%c%c%c%c%c%c%c%c", 196, 196, 196, 196, 196, 196, 196, 191);
}

void printMiddleLineTable(int num){
	int i;
	printf("%c", 195);
	for (i = 1; i < num; i++) printf("%c%c%c%c%c%c%c%c", 196, 196, 196, 196, 196, 196, 196, 197);
	printf("%c%c%c%c%c%c%c%c", 196, 196, 196, 196, 196, 196, 196, 180);
}

void printLastLineTable(int num){
	int i;
	printf("%c", 192);
	for (i = 1; i < num; i++) printf("%c%c%c%c%c%c%c%c", 196, 196, 196, 196, 196, 196, 196, 193);
	printf("%c%c%c%c%c%c%c%c", 196, 196, 196, 196, 196, 196, 196, 217);
}

void printContentLineTable(int xStart, int xEnd, int y, char* str[8][6]){
	int i;
	printf("%c", 179);
	for (i = xStart; i <= xEnd; i++) printf("%s%c", str[i][y], 179);
}

// create interface for room.Calculate
void createInterfaceCalculate(int x0, int y0, char* str[8][6], int firstColor){
	
	// print title
	textColor(firstColor);
	system("cls");
	goToXY(0, 0); printf("Press Esc to back");
	goToXY(40, 2); printf("           __         __     __");
	goToXY(40, 3); printf(" _______ _/ /_____ __/ /__ _/ /____  ____");
	goToXY(40, 4); printf("/ __/ _ `/ / __/ // / / _ `/ __/ _ \\/ __/");
	goToXY(40, 5); printf("\\__/\\_,_/_/\\__/\\_,_/_/\\_,_/\\__/\\___/_/");
 	
 	// print screen section
 	int i;
 	goToXY(x0, y0 - 3); printf("%c", 218); for (i = 1; i <= 57; i++) printf("%c", 196); printf("%c", 191);
 	goToXY(x0, y0 - 2); printf("%c 1+2/3", 179); goToXY(x0 + 58, y0 - 2); printf("%c", 179); 
 	goToXY(x0, y0 - 1); printf("%c", 192); for (i = 1; i <= 57; i++) printf("%c", 196); printf("%c", 217);
 	
 	// print number section
	goToXY(x0, y0); printFirstLineTable(5);
	for (i = 1; i <= 2; i++){
		goToXY(x0, y0 + i*2 - 1); printContentLineTable(1, 5, i, str);
		goToXY(x0, y0 + i*2); printMiddleLineTable(5);
	}
	goToXY(x0, y0 + 4); printLastLineTable(5);
	
	// print advance operator section
	goToXY(x0, y0 + 5); printFirstLineTable(5);
	for (i = 3; i <= 5; i++){
		goToXY(x0, y0 + i*2); printContentLineTable(1, 5, i, str);
		goToXY(x0, y0 + i*2 + 1); printMiddleLineTable(5);
	}
	goToXY(x0, y0 + 11); printLastLineTable(5);
	
	// print equal sign section
	goToXY(x0 + 42, y0); printFirstLineTable(2);
	for (i = 1; i <= 2; i++){
		goToXY(x0 + 42, y0 + i*2 - 1); printContentLineTable(6, 7, i, str);
		goToXY(x0 + 42, y0 + i*2); printMiddleLineTable(2);
	}
	goToXY(x0 + 42, y0 + 4); printLastLineTable(2);

	// print basic operator section
	goToXY(x0 + 42, y0 + 5); printFirstLineTable(2);
	for (i = 3; i <= 5; i++){
		goToXY(x0 + 42, y0 + i*2); printContentLineTable(6, 7, i, str);
		goToXY(x0 + 42, y0 + i*2 + 1); printMiddleLineTable(2);
	}
	goToXY(x0 + 42, y0 + 11); printLastLineTable(2);
	
	goToXY(119, 29);
}

// highlight current part
void highlightCalculate(int x0, int y0, int x, int y, char* str[8][6], int secondColor){
	
	// highligh
	textColor(secondColor);
	int dx = 0, dy = 0;
	if (x > 5) dx = 2;
	if (y > 2) dy = 1;
	goToXY(x0 + (x - 1)*8 + 1 + dx, y0 + y*2 - 1 + dy);
	printf("%s", str[x][y]);
	
	// move the cusor to the bottom right corner
	goToXY(119, 29);
}

// unhighlight current part
void unhighlightCalculate(int x0, int y0, int x, int y, char* str[8][6], int firstColor){
	
	// unhighligh
	textColor(firstColor);
	int dx = 0, dy = 0;
	if (x > 5) dx = 2;
	if (y > 2) dy = 1;
	goToXY(x0 + (x - 1)*8 + 1 + dx, y0 + y*2 - 1 + dy);
	printf("%s", str[x][y]);
}

// room.Calculate main
void roomCalculate(int firstColor, int secondColor){
	
	// declare vars
	int x0 = 30, y0 = 12, column = 7, row = 5; 
	char strReal[35][50], tmp = '\0';
	char* str[8][6]; // store address of those strings
	
	// assign all the strings '\0'
	int i, j;
	for (i = 0; i <= column + 1; i++)
		for (j = 0; j <= row + 1; j++) str[i][j] = &tmp;
	
	// assign values to the strings	
	makeStr("   1   ", &strReal[1][0]); 
	makeStr("   2   ", &strReal[2][0]);
	makeStr("   3   ", &strReal[3][0]);
	makeStr("   4   ", &strReal[4][0]);
	makeStr("   5   ", &strReal[5][0]);
	makeStr("   6   ", &strReal[6][0]);
	makeStr("   7   ", &strReal[7][0]);
	makeStr("   8   ", &strReal[8][0]);
	makeStr("   9   ", &strReal[9][0]);
	makeStr("   0   ", &strReal[10][0]);
	makeStr("   ^   ", &strReal[11][0]);
	makeStr("   s   ", &strReal[12][0]); strReal[12][3] = 251; // sqrt
	makeStr("   <   ", &strReal[13][0]);
	makeStr("   >   ", &strReal[14][0]);  
	makeStr("   !   ", &strReal[15][0]);
	makeStr("  sin  ", &strReal[16][0]);
	makeStr("  cos  ", &strReal[17][0]);
	makeStr("  | |  ", &strReal[18][0]);
	makeStr("  log  ", &strReal[19][0]);
	makeStr("  ln   ", &strReal[20][0]);
	makeStr("  tan  ", &strReal[21][0]);
	makeStr("  cot  ", &strReal[22][0]);
	makeStr("   (   ", &strReal[23][0]);
	makeStr("   )   ", &strReal[24][0]);
	makeStr("   e   ", &strReal[25][0]);
	makeStr("   .   ", &strReal[26][0]);
	makeStr("   =   ", &strReal[27][0]);
	makeStr("   p   ", &strReal[28][0]); strReal[28][3] = 227; // pi
	makeStr("  ans  ", &strReal[29][0]);
	makeStr("  DEL  ", &strReal[30][0]);
	makeStr("  AC   ", &strReal[31][0]);
	makeStr("   x   ", &strReal[32][0]);
	makeStr("   /   ", &strReal[33][0]);
	makeStr("   +   ", &strReal[34][0]);
	makeStr("   -   ", &strReal[35][0]);
	
	// store addresses
	str[1][1] = &strReal[1][0];
	str[2][1] = &strReal[2][0];
	str[3][1] = &strReal[3][0];
	str[4][1] = &strReal[4][0];
	str[5][1] = &strReal[5][0];
	str[1][2] = &strReal[6][0];
	str[2][2] = &strReal[7][0];
	str[3][2] = &strReal[8][0];
	str[4][2] = &strReal[9][0];
	str[5][2] = &strReal[10][0];
	str[1][3] = &strReal[11][0];
	str[2][3] = &strReal[12][0];
	str[3][3] = &strReal[13][0];
	str[4][3] = &strReal[14][0];
	str[5][3] = &strReal[15][0];
	str[1][4] = &strReal[16][0];
	str[2][4] = &strReal[17][0];
	str[3][4] = &strReal[18][0];
	str[4][4] = &strReal[19][0];
	str[5][4] = &strReal[20][0];
	str[1][5] = &strReal[21][0];
	str[2][5] = &strReal[22][0];
	str[3][5] = &strReal[23][0];
	str[4][5] = &strReal[24][0];
	str[5][5] = &strReal[25][0];
	str[6][1] = &strReal[26][0];
	str[7][1] = &strReal[27][0];
	str[6][2] = &strReal[28][0];
	str[7][2] = &strReal[29][0];
	str[6][3] = &strReal[30][0];
	str[7][3] = &strReal[31][0];
	str[6][4] = &strReal[32][0];
	str[7][4] = &strReal[33][0];
	str[6][5] = &strReal[34][0];
	str[7][5] = &strReal[35][0];
	
	// create interface
	createInterfaceCalculate(x0, y0, str, firstColor);
	
	// using arrow keys to control
	highlightCalculate(x0, y0, 1, 1, str, secondColor);
	int x = 1, y = 1; // store coordinates
	// store calculator memory
	char screenLine[1000], ans[500] = "0";
	int screenLineLength = 0;
	char ch;
	do{
		ch = getch();
		
		// esc
		if (ch == 27) return;
		
		// arrow keys
		if (ch == 4294967264){
			unhighlightCalculate(x0, y0, x, y, str, firstColor);
			ch = getch();
			
			// arrow up
			if (ch == 72){
				y--;
				if (y == 0){
					//screenSection(screenLine, screenLineLength, ans, firstColor);
					y = 1;
				}
			}
			
			// arrow down
			if (ch == 80){
				y++;
				if (y == row + 1) y = row;
			}
			
			// arrow left
			if (ch == 75){
				x--;
				if (x == 0) x = 1;
			}
			
			// arrow right
			if (ch == 77){
				x++;
				if (x == column + 1) x = column;
			}
			
			highlightCalculate(x0, y0, x, y, str, secondColor);
		}
	} while(1);
}
