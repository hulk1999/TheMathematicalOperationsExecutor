// create interface for room.Settings
void createInterfaceSettings(int x0, int y0, int step, int row, char* str[6][5], int firstColor){
	
	// print title
	textColor(firstColor);
	system("cls");
	goToXY(0, 0); printf("Press Esc to back");
	goToXY(42, 2); printf("           __  __  _");
	goToXY(42, 3); printf("  ___ ___ / /_/ /_(_)__  ___ ____");
	goToXY(42, 4); printf(" (_-</ -_) __/ __/ / _ \\/ _ `(_-<");
	goToXY(42, 5); printf("/___/\\__/\\__/\\__/_/_//_/\\_, /___/");
	goToXY(42, 6); printf("                       /___/");
	goToXY(119, 29);
	
	// print menu
	int i;
	for (i = 1; i <= row; i++){
		goToXY(x0, y0 + (i - 1)*step);
		printf("%s", str[1][i]);
	}
}

// highlight current part
void highlightSettings(int x0, int y0, int step, int x, int y, char* str[6][5], int secondColor){
	
	// set appropriate color then print
	if ((x >= 2) && (y <= 2)) textColor(128 + 16*(x - 2 + 4*(y-1)));
	else textColor(secondColor);
	if (x == 1) goToXY(x0, y0 + (y - 1)*step);
	else goToXY(16 + x*16, y0 + (y - 1)*step);
	printf("%s", str[x][y]);
	
	// move the cusor to the bottom right corner
	goToXY(119, 29);
}

// unhighlight current part
void unhighlightSettings(int x0, int y0, int step, int x, int y, char* str[6][5], int firstColor){
	
	// set appropriate color then print
	if ((x >= 2) && (y <= 2)) textColor(4*(y - 1) + x + 6);
	else textColor(firstColor);
	if (x == 1) goToXY(x0, y0 + (y - 1)*step);
	else goToXY(16 + x*16, y0 + (y - 1)*step);
	printf("%s", str[x][y]);
}

// print color section
void printColor(int y0, int step, char* str[6][5]){
	int x, y;
	for (x = 2; x <= 5; x++)
		for (y = 1; y <= 2; y++){
			// set appropriate color
			textColor(4*(y - 1) + x + 6);
			goToXY(16 + x*16, y0 + (y - 1)*step);
			printf("%s", str[x][y]);
		}
}

// delete color section
void deleteColor(int y0, int step, char* str[6][5], int firstColor){
	textColor(0);
	int x, y;
	for (x = 2; x <= 5; x++)
		for (y = 1; y <= 2; y++){
			goToXY(16 + x*16, y0 + (y - 1)*step);
			printf("%s", str[x][y]);
		}
	textColor(firstColor);
}

// print size section
void printSize(int y0, int step, char* str[6][5]){
	int x, y = 3;
	for (x = 2; x <= 5; x++){
		goToXY(16 + x*16, y0 + (y - 1)*step);
		printf("%s", str[x][y]);
	}
}

// delete size section
void deleteSize(int y0, int step, char* str[6][5], int firstColor){
	textColor(0);
	int x, y = 3;
	for (x = 2; x <= 5; x++){
		goToXY(16 + x*16, y0 + (y - 1)*step);
		printf("%s", str[x][y]);
	}
	textColor(firstColor);
}

// print music section
void printMusic(int y0, int step, char* str[6][5]){
	int x = 2, y = 4;
	goToXY(16 + x*16, y0 + (y - 1)*step);
	printf("%s", str[x][y]);
}

// delete music section
void deleteMusic(int y0, int step, char* str[6][5], int firstColor){
	textColor(0);
	int x = 2, y = 4;
	goToXY(16 + x*16, y0 + (y - 1)*step);
	printf("%s", str[x][y]);
	textColor(firstColor);
}

// get optional size number
int inputSize(int* pX, int firstColor, int secondColor){
	
	// display
	int x = 96, y = 16;
	textColor(firstColor);
	goToXY(x, y + 1); printf("    input    ");
	textColor(secondColor);
	goToXY(x, y); printf("             ");
	goToXY(x + 5, y);
	
	// get input
	char ch;
	int numStr[3], count = 0, num;
	do{
		ch = getch();
		loopWithoutGetch:
		
		// esc
		if (ch == 27) return 0;
		
		// backspace
		if ((ch == 8) && (count > 0)){
			count--;
			goToXY(x + 6 + count, y); printf(" ");
			goToXY(x + 6 + count, y);
		}
		
		// numbers
		if ((ch >= '0') && (ch <= '9') && (count <= 1)){
			goToXY(x + 6 + count, y); printf("%c", ch);
			count++;
			numStr[count] = ch;
		}
		
		// enter
		if (ch == 13){
			if (count >= 1){
				num = numStr[count] - '0';
				if (count == 2) num += (numStr[1] - '0') * 10;
				if ((num == 0) || (num > 24)){
					textColor(firstColor);
					goToXY(x, y + 1);
					printf("    error!   ");
					goToXY(119, 29);
					ch = getch();
					goToXY(x, y + 1);
					printf("    input    ");
					goToXY(x + 6 + count, y);
					textColor(secondColor);
					goto loopWithoutGetch;
				}
				else{
					// set new size
					fontSize(num / 2, num);
					
					// save new color to memory file
					int tmp, score;
					FILE *memory = fopen("memory.txt", "r");
					fscanf(memory, "%d %d %d %d", &tmp, &tmp, &tmp, &score);
					fclose(memory);
					memory = fopen("memory.txt", "w");
					fprintf(memory, "%d\n%d\n%d\n%d", firstColor, secondColor, num, score);
					fclose(memory);
				}
			}
		}
		
		// arrow keys
		if (ch == 4294967264){
			ch = getch();
			
			// arrow left
			if (ch == 75){
				*pX -= 1;
				textColor(firstColor);
				goToXY(x, y + 1); printf("             ");
				return 1;
			}
		}
	} while (1);
}

// room.Settings main
void roomSettings(int* pFirstColor, int* pSecondColor){
	
	// assign color
	int firstColor = *pFirstColor;
	int secondColor = *pSecondColor;
	
	// declare vars
	int x0 = 22, y0 = 10, step = 3, row = 4, column = 5;
	char strReal[17][50], tmp = '\0';
	char* str[6][5]; // store address of those strings
	
	// assign all the strings '\0'
	int i, j;
	for (i = 0; i <= column + 1; i++)
		for (j = 0; j <= row + 1; j++) str[i][j] = &tmp;
	
	// assign values to the strings	
	strcpy(&strReal[1][0], "       COLOR      >"); 
	strcpy(&strReal[2][0], "    boring   ");
	strcpy(&strReal[3][0], "    shark    ");
	strcpy(&strReal[4][0], "    matrix   ");
	strcpy(&strReal[5][0], "     sky     ");
	strcpy(&strReal[6][0], "    devil    ");
	strcpy(&strReal[7][0], "  melancholy ");
	strcpy(&strReal[8][0], "  sunflower  ");
	strcpy(&strReal[9][0], "     pure    ");
	strcpy(&strReal[10][0], "       SIZE       >");
	strcpy(&strReal[11][0], "    small    ");
	strcpy(&strReal[12][0], "    medium   ");
	strcpy(&strReal[13][0], "    large    ");
	strcpy(&strReal[14][0], "    other    ");  
	strcpy(&strReal[15][0], "       MUSIC      >");
	strcpy(&strReal[16][0], "    Nah I'm just kidding :))    ");
	
	// store addresses
	str[1][1] = &strReal[1][0];
	str[2][1] = &strReal[2][0];
	str[3][1] = &strReal[3][0];
	str[4][1] = &strReal[4][0];
	str[5][1] = &strReal[5][0];
	str[2][2] = &strReal[6][0];
	str[3][2] = &strReal[7][0];
	str[4][2] = &strReal[8][0];
	str[5][2] = &strReal[9][0];
	str[1][3] = &strReal[10][0];
	str[2][3] = &strReal[11][0];
	str[3][3] = &strReal[12][0];
	str[4][3] = &strReal[13][0];
	str[5][3] = &strReal[14][0];
	str[1][4] = &strReal[15][0];
	str[2][4] = &strReal[16][0];
	
	// create interface
	createInterfaceSettings(x0, y0, step, row, str, firstColor);
	
	// using arrow keys to control
	highlightSettings(x0, y0, step, 1, 1, str, secondColor);
	int x = 1, y = 1; // store coordinates
	char ch;
	do{
		ch = getch();
		
		// esc
		if (ch == 27) return;
		
		// arrow keys
		if (ch == 4294967264){
			unhighlightSettings(x0, y0, step, x, y, str, firstColor);
			ch = getch();
			
			// arrow up
			if (ch == 72){
				y--;
					 if (y == 0) y = 1;
				else if ((y == 2) && (x == 1)) y = 1;
				else if ((y == 2) && (x != 1)) y = 3;
				else if ((y == 3) && (x != 1)) y = 4;
			}
			
			// arrow down
			if (ch == 80){
				y++;
					 if (y == row + 1) y = row;
				else if ((y == 2) && (x == 1)) y = 3;
				else if ((y == 3) && (x != 1)) y = 2;
				else if ((y == 4) && (x != 1)) y = 3;
			}
			
			// arrow left
			if (ch == 75){
				x--;
					 if (x == 0) x = 1;
				else if ((x == 1) && (y == 2)){
					x = 1;
					y = 1;
					deleteColor(y0, step, str, firstColor);
				}
				else if (x == 1) switch (y){
									case 1: deleteColor(y0, step, str, firstColor); break;
									case 3: deleteSize(y0, step, str, firstColor); break;
									case 4: deleteMusic(y0, step, str, firstColor); break;
									default: break;
								 }
			}
			
			// arrow right
			if (ch == 77){
				x++;
					 if (x == 6) x = 5;
				else if ((x == 3) && (y == 4)) x = 2;
				else if (x == 2) switch (y){
									case 1: printColor(y0, step, str); break;
									case 3: printSize(y0, step, str); break;
									case 4: printMusic(y0, step, str); break;
									default: break;
								 }
				if ((x == 5) && (y == 3)){
					if (inputSize(&x, firstColor, secondColor) == 0) return;
					unhighlightSettings(x0, y0, step, 5, 3, str, firstColor);
				}
			}
			
			highlightSettings(x0, y0, step, x, y, str, secondColor);
		}
		
		// enter
		if ((ch == 13) && (x >= 2)){
			
			// color section: change color
			if (y <= 2){
				
				// change color
				firstColor = 4*(y - 1) + x + 6; *pFirstColor = firstColor;
				secondColor = 128 + 16*(x - 2 + 4*(y-1)); *pSecondColor = secondColor;
				createInterfaceSettings(x0, y0, step, row, str, firstColor);
				highlightSettings(x0, y0, step, 1, 1, str, secondColor);
				x = 1; y = 1;
				
				// save new color to memory file
				int tmp, size, score;
				FILE *memory = fopen("memory.txt", "r");
				fscanf(memory, "%d %d %d %d", &tmp, &tmp, &size, &score);
				fclose(memory);
				memory = fopen("memory.txt", "w");
				fprintf(memory, "%d\n%d\n%d\n%d", firstColor, secondColor, size, score);
				fclose(memory);
			}
			
			// size section: change size
			if (y == 3){
				int tmp, size, score;
				switch (x){
					case 2: size = 12; break;
					case 3: size = 16; break;
					case 4: size = 22; break;
					default: break;
				}
				if ((x >= 2) && (x <= 4)){
					
					// set new size
					fontSize(size / 2, size);
					
					// save new color to memory file
					FILE *memory = fopen("memory.txt", "r");
					fscanf(memory, "%d %d %d %d", &tmp, &tmp, &tmp, &score);
					fclose(memory);
					memory = fopen("memory.txt", "w");
					fprintf(memory, "%d\n%d\n%d\n%d", firstColor, secondColor, size, score);
					fclose(memory);
				}
			}
		}
	} while (1);
}
