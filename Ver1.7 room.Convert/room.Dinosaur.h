// make random number in range [1, max]
int random(int max){
	return 1 + rand() % (max - 1);
}

// create interface for room.Dinosaur
void createInterfaceDinosaur(int firstColor){
	
	// print title
	textColor(firstColor);
	system("cls");
	goToXY(0, 0); printf("Press Esc to back");
	goToXY(22, 2); printf("                      _                ___");
	goToXY(22, 3); printf("  ______ _____  ___  (_)__  ___ _  ___/ (_)__  ___  ___ ___ ___ ______");
	goToXY(22, 4); printf(" / __/ // / _ \\/ _ \\/ / _ \\/ _ `/ / _  / / _ \\/ _ \\(_-</ _ `/ // / __/");
	goToXY(22, 5); printf("/_/  \\_,_/_//_/_//_/_/_//_/\\_, /  \\_,_/_/_//_/\\___/___/\\_,_/\\_,_/_/");
	goToXY(22, 6); printf("                          /___/");
	goToXY(119, 29);
}

void printGameOver(){
	goToXY(55, 10); printf("GAME OVER");
	goToXY(119, 29);
}

// make next element for ground
void makeGround(char ground[3][121]){
	int t = random(15);
	switch (t){
		case 1: ground[1][119] = '.'; ground[2][119] = ' '; break;
		case 2: ground[1][119] = '-'; ground[2][119] = ' '; break;
		case 3: ground[1][119] = 248; ground[2][119] = ' '; break;
		case 4: ground[1][119] = '`'; ground[2][119] = ' '; break;
		case 5: ground[2][119] = '.'; ground[1][119] = ' '; break;
		case 6: ground[2][119] = '-'; ground[1][119] = ' '; break;
		case 7: ground[2][119] = '`'; ground[1][119] = ' '; break;
		default: ground[1][119] = ' '; ground[2][119] = ' '; break;
	}
}

// set random seed; make ground
void initialize(char ground[3][121]){
	srand(time(NULL));
	
	int i, t;
	for (i = 0; i <= 120; i++){
		t = random(15);
		ground[0][i] = '_';
		switch (t){
			case 1: ground[1][i] = '.'; ground[2][i] = ' '; break;
			case 2: ground[1][i] = '-'; ground[2][i] = ' '; break;
			case 3: ground[1][i] = 248; ground[2][i] = ' '; break;
			case 4: ground[1][i] = '`'; ground[2][i] = ' '; break;
			case 5: ground[2][i] = '.'; ground[1][i] = ' '; break;
			case 6: ground[2][i] = '-'; ground[1][i] = ' '; break;
			case 7: ground[2][i] = '`'; ground[1][i] = ' '; break;
			default: ground[1][i] = ' '; ground[2][i] = ' '; break;
		}
	}
	ground[0][120] = '\0';
	ground[1][120] = '\0';
	ground[2][120] = '\0';
}

void printGround(char ground[3][121], int y0){
	goToXY(0, y0);
	puts(&ground[0][0]);
	puts(&ground[1][0]);
	puts(&ground[2][0]);
}

void printObstacle(int type, int x, int y0, int color){
	textColor(color);
	switch (type){
		case 1: // 1 large (height = 5)
			goToXY(x - 1, y0 - 4) ; printf(" %c%c", 186, 186);
			goToXY(x - 1, y0 - 3) ; printf("%c%c%c", 186, 186, 186);
			goToXY(x - 1, y0 - 2) ; printf("%c%c%c", 186, 204, 188);
			goToXY(x - 1, y0 - 1); printf("%c%c", 200, 185);
			goToXY(x, y0); printf("%c", 186);
			break;
		case 2: // 3 smalls (height = 2)
			goToXY(x - 1, y0 - 1); printf("%c%c%c%c%c%c%c%c%c", 200, 206, 188, 200, 206, 188, 200, 206, 188);
			goToXY(x, y0); printf("%c__%c__%c", 186, 186, 186);
			break;
		case 3: // 2 mediums (height = 3)
			goToXY(x - 1, y0 - 2) ; printf("%c%c%c%c%c%c", 186, 186, 186, 186, 186, 186);
			goToXY(x - 1, y0 - 1); printf("%c%c%c%c%c%c", 200, 206, 188, 200, 206, 188);
			goToXY(x, y0); printf("%c__%c", 186, 186);
			break;
		case 4: // small - large
			goToXY(x - 1, y0 - 4) ; printf("    %c%c", 186, 186);
			goToXY(x - 1, y0 - 3) ; printf("   %c%c%c", 186, 186, 186);
			goToXY(x - 1, y0 - 2) ; printf("   %c%c%c", 186, 204, 188);
			goToXY(x - 1, y0 - 1); printf("%c%c%c%c%c", 200, 206, 188, 200, 185);
			goToXY(x, y0); printf("%c__%c", 186, 186);
			break;
		case 5: // large - large - medium
			goToXY(x - 1, y0 - 4) ; printf(" %c%c %c%c", 186, 186, 186, 186);
			goToXY(x - 1, y0 - 3) ; printf("%c%c%c%c%c%c", 186, 186, 186, 186, 186, 186);
			goToXY(x - 1, y0 - 2) ; printf("%c%c%c%c%c%c%c%c%c", 186, 204, 188, 186, 204, 188, 186, 186, 186);
			goToXY(x - 1, y0 - 1); printf("%c%c %c%c %c%c%c", 200, 185, 200, 185, 200, 206, 188);
			goToXY(x, y0); printf("%c__%c__%c", 186, 186, 186);
			break;
		case 6: // small - large - large - medium
			goToXY(x - 1, y0 - 4) ; printf("    %c%c %c%c", 186, 186, 186, 186);
			goToXY(x - 1, y0 - 3) ; printf("   %c%c%c%c%c%c", 186, 186, 186, 186, 186, 186);
			goToXY(x - 1, y0 - 2) ; printf("   %c%c%c%c%c%c%c%c%c", 186, 204, 188, 186, 204, 188, 186, 186, 186);
			goToXY(x - 1, y0 - 1); printf("%c%c%c%c%c %c%c %c%c%c", 200, 206, 188, 200, 185, 200, 185, 200, 206, 188);
			goToXY(x, y0); printf("%c__%c__%c__%c", 186, 186, 186, 186);
			break;
		case 7: // large - large - medium - large
			goToXY(x - 1, y0 - 4) ; printf(" %c%c %c%c    %c%c", 186, 186, 186, 186, 186, 186);
			goToXY(x - 1, y0 - 3) ; printf("%c%c%c%c%c%c%c%c %c%c%c", 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186);
			goToXY(x - 1, y0 - 2) ; printf("%c%c%c%c%c%c%c%c%c%c%c%c", 186, 204, 188, 186, 204, 188, 186, 186, 186, 186, 204, 188);
			goToXY(x - 1, y0 - 1); printf("%c%c %c%c %c%c%c%c%c ", 200, 185, 200, 185, 200, 206, 188, 200, 185);
			goToXY(x, y0); printf("%c__%c__%c__%c", 186, 186, 186, 186);
			break;
		default: break;
	}
}

void deleteObstacle(int type, int x, int y0){
	switch (type){
		case 1: // 1 large (height = 5)
			goToXY(x + 1, y0 - 4) ; printf(" ");
			goToXY(x + 1, y0 - 3) ; printf(" ");
			goToXY(x + 1, y0 - 2) ; printf(" ");
			goToXY(x, y0 - 1); printf(" ");
			goToXY(x, y0); printf(" ");
			break;
		case 2: // 3 smalls (height = 2)
			goToXY(x + 7, y0 - 1); printf(" ");
			goToXY(x + 6, y0); printf(" ");
			break;
		case 3: // 2 mediums (height = 3)
			goToXY(x + 4, y0 - 2) ; printf(" ");
			goToXY(x + 4, y0 - 1); printf(" ");
			goToXY(x + 3, y0); printf(" ");
			break;
		case 4: // small - large
			goToXY(x + 4, y0 - 4) ; printf(" ");
			goToXY(x + 4, y0 - 3) ; printf(" ");
			goToXY(x + 4, y0 - 2) ; printf(" ");
			goToXY(x + 3, y0 - 1); printf(" ");
			goToXY(x + 3, y0); printf(" ");
			break;
		case 5: // large - large - medium
			goToXY(x + 4, y0 - 4) ; printf(" ");
			goToXY(x + 4, y0 - 3) ; printf(" ");
			goToXY(x + 7, y0 - 2) ; printf(" ");
			goToXY(x + 7, y0 - 1); printf(" ");
			goToXY(x + 6, y0); printf(" ");
			break;
		case 6: // small - large - large - medium
			goToXY(x + 7, y0 - 4) ; printf(" ");
			goToXY(x + 7, y0 - 3) ; printf(" ");
			goToXY(x + 10, y0 - 2) ; printf(" ");
			goToXY(x + 10, y0 - 1); printf(" ");
			goToXY(x + 9, y0); printf(" ");
			break;
		case 7: // large - large - medium - large
			goToXY(x + 10, y0 - 4) ; printf(" ");
			goToXY(x + 10, y0 - 3) ; printf(" ");
			goToXY(x + 10, y0 - 2) ; printf(" ");
			goToXY(x + 9, y0 - 1); printf(" ");
			goToXY(x + 9, y0); printf(" ");
			break;
		default: break;
	}
}

void printDinosaur(int height, int leg, int y0){
	goToXY(25, y0 - 5 - height); printf("          e-e");
	goToXY(25, y0 - 4 - height); printf("        /(\\_/)");
	goToXY(25, y0 - 3 - height); printf(".___.--' /`-'");
	goToXY(25, y0 - 2 - height); printf(" `-._. )/`");
	goToXY(25, y0 - 1 - height); printf("    //");
	goToXY(29, y0 - height);
	if ((height > 0) || (leg == 3)){
		printf("^^");
		return;
	}
	if (leg == 1) printf("^_");
	if (leg == 2) printf("_^");
}

void deleteDinosaur(int jump, int height, int y0){
	if (jump){
		if (jump < 25){
			goToXY(38, y0 - 4 - height); printf(" ");
			goToXY(35, y0 - 3 - height); printf("   ");
			goToXY(32, y0 - 2 - height); printf("   ");
			goToXY(29, y0 - height); printf("  ");
		}
		else{
			goToXY(35, y0 - 5 - height); printf("   ");
			goToXY(38, y0 - 4 - height); printf(" ");
		}
	}
}

int checkCollision(int height, int obstacle, int obstaclePos, int y0){
	
	int i, j, xy[100][21];
	
	for (i = 1; i <= 99; i++)
		for (j = 1; j <= 20; j++)
			xy[i][j] = 0;
	
	xy[38][y0 - 4 - height] = 1;
	xy[25][y0 - 3 - height] = 1;
	xy[35][y0 - 3 - height] = 1;
	xy[36][y0 - 3 - height] = 1;
	xy[37][y0 - 3 - height] = 1;
	xy[26][y0 - 2 - height] = 1;
	xy[27][y0 - 2 - height] = 1;
	xy[28][y0 - 2 - height] = 1;
	xy[31][y0 - 2 - height] = 1;
	xy[32][y0 - 2 - height] = 1;
	xy[33][y0 - 2 - height] = 1;
	xy[34][y0 - 2 - height] = 1;
	xy[29][y0 - 1 - height] = 1;
	xy[30][y0 - 1 - height] = 1;
	xy[29][y0 - height] = 1;
	xy[30][y0 - height] = 1;
		
	switch (obstacle){
		case 1: // 1 large
			if (xy[obstaclePos][y0 - 4]) return 1;
			if (xy[obstaclePos + 1][y0 - 4]) return 1;
			if (xy[obstaclePos - 1][y0 - 3]) return 1;
			if (xy[obstaclePos - 1][y0 - 2]) return 1;
			if (xy[obstaclePos - 1][y0 - 1]) return 1;
			break;
		case 2: // 3 smalls
			if (xy[obstaclePos - 1][y0 - 1]) return 1;
			if (xy[obstaclePos][y0 - 1]) return 1;
			if (xy[obstaclePos + 1][y0 - 1]) return 1;
			if (xy[obstaclePos + 2][y0 - 1]) return 1;
			if (xy[obstaclePos + 3][y0 - 1]) return 1;
			if (xy[obstaclePos + 4][y0 - 1]) return 1;
			if (xy[obstaclePos + 5][y0 - 1]) return 1;
			if (xy[obstaclePos + 6][y0 - 1]) return 1;
			if (xy[obstaclePos + 7][y0 - 1]) return 1;
			break;
		case 3: // 2 mediums
			if (xy[obstaclePos - 1][y0 - 2]) return 1;
			if (xy[obstaclePos][y0 - 2]) return 1;
			if (xy[obstaclePos + 1][y0 - 2]) return 1;
			if (xy[obstaclePos + 2][y0 - 2]) return 1;
			if (xy[obstaclePos + 3][y0 - 2]) return 1;
			if (xy[obstaclePos + 4][y0 - 2]) return 1;
			if (xy[obstaclePos - 1][y0 - 1]) return 1;
			break;
		case 4: // small - large
			if (xy[obstaclePos + 3][y0 - 4]) return 1;
			if (xy[obstaclePos + 4][y0 - 4]) return 1;
			if (xy[obstaclePos + 2][y0 - 3]) return 1;
			if (xy[obstaclePos + 2][y0 - 2]) return 1;
			if (xy[obstaclePos - 1][y0 - 1]) return 1;
			if (xy[obstaclePos][y0 - 1]) return 1;
			if (xy[obstaclePos + 1][y0 - 1]) return 1;
			break;
		case 5: // large - large - medium
			if (xy[obstaclePos][y0 - 4]) return 1;
			if (xy[obstaclePos + 1][y0 - 4]) return 1;
			if (xy[obstaclePos + 3][y0 - 4]) return 1;
			if (xy[obstaclePos + 4][y0 - 4]) return 1;
			if (xy[obstaclePos - 1][y0 - 3]) return 1;
			if (xy[obstaclePos - 1][y0 - 2]) return 1;
			if (xy[obstaclePos + 5][y0 - 2]) return 1;
			if (xy[obstaclePos + 6][y0 - 2]) return 1;
			if (xy[obstaclePos + 7][y0 - 2]) return 1;
			if (xy[obstaclePos - 1][y0 - 1]) return 1;
			break;
		case 6: // small - large - large - medium
			if (xy[obstaclePos + 3][y0 - 4]) return 1;
			if (xy[obstaclePos + 4][y0 - 4]) return 1;
			if (xy[obstaclePos + 6][y0 - 4]) return 1;
			if (xy[obstaclePos + 7][y0 - 4]) return 1;
			if (xy[obstaclePos + 2][y0 - 3]) return 1;
			if (xy[obstaclePos + 2][y0 - 2]) return 1;
			if (xy[obstaclePos + 8][y0 - 2]) return 1;
			if (xy[obstaclePos + 9][y0 - 2]) return 1;
			if (xy[obstaclePos + 10][y0 - 2]) return 1;
			if (xy[obstaclePos - 1][y0 - 1]) return 1;
			if (xy[obstaclePos][y0 - 1]) return 1;
			if (xy[obstaclePos + 1][y0 - 1]) return 1;
			break;
		case 7: // large - large - medium - large
			if (xy[obstaclePos][y0 - 4]) return 1;
			if (xy[obstaclePos + 1][y0 - 4]) return 1;
			if (xy[obstaclePos + 3][y0 - 4]) return 1;
			if (xy[obstaclePos + 4][y0 - 4]) return 1;
			if (xy[obstaclePos + 9][y0 - 4]) return 1;
			if (xy[obstaclePos + 10][y0 - 4]) return 1;
			if (xy[obstaclePos - 1][y0 - 3]) return 1;
			if (xy[obstaclePos - 1][y0 - 2]) return 1;
			if (xy[obstaclePos - 1][y0 - 1]) return 1;
			break;
		default: break;
	}
	
	return 0;
}

// room.Dinosaur main
void roomDinosaur(int firstColor, int secondColor){
	
	// declare vars
	int y0 = 20;
	int frameCount, frameTime, highscore = 0;
	int height, jump;
	int obstaclePos, obstacle;
	int i, t;
	char ground[3][121], ch;
	initialize(ground);
	
	// create interface
	createInterfaceDinosaur(firstColor);
	printGround(ground, y0);
	printDinosaur(0, 3, y0);
	goToXY(119, 29);
	
	// GAME
	while (1){
		
		gameStart:
		
		// initialize
		frameCount = 0; frameTime = 10;
		jump = 0;
		obstacle = 0;
		
		// press enter to start
		do{
			ch = getch();
			if (ch == 27) return; // esc
		}
		while (ch != 13);
		
		// print stuffs
		system("cls");
		goToXY(0, 0); printf("Press Esc to back");
		goToXY(94, 1); printf("Highs: %d", highscore);
		goToXY(94, 2); printf("Score:");
	
		// game
		while (1){
			
			// delete
			deleteObstacle(obstacle, obstaclePos, y0);
			deleteDinosaur(jump, height, y0);
			textColor(firstColor);
			
			// make ground
			makeGround(ground);
			for (i = 0; i <= 118; i++){
				ground[1][i] = ground[1][i + 1];
				ground[2][i] = ground[2][i + 1];
			}
			
			// make obstacle
			if (obstacle == 0){
				t = random(15);
				if (t <= 7){
					obstacle = t;
					obstaclePos = 108;
				}
			}
			else obstaclePos--;
			if (obstaclePos == 1){
				printObstacle(obstacle, 1, y0, 0);
				obstacle = 0;
				textColor(firstColor);
			}
			
			// dinosaur jump
			height = (50 - jump) * jump / 60; // it's physic mate. it's physiccccc			
			if ((jump < 50) && (jump != 0)) jump++;
			else jump = 0;
			
			// print
			printGround(ground, y0);
			printObstacle(obstacle, obstaclePos, y0, firstColor);
			printDinosaur(height, 1 + frameCount % 2, y0);
			goToXY(101, 2); printf("%d", frameCount);
			goToXY(119, 29);
			
			// check collision
			if (obstaclePos <= 39)
				if (checkCollision(height, obstacle, obstaclePos, y0)){
					goToXY(35, y0 - 5 - height); printf("x-x");
					printGameOver();
					if (highscore < frameCount) highscore = frameCount;
					goto gameStart;
				}
			
			// if keypressed
			if (kbhit()){
				ch = getch();
				
				// esc
				if (ch == 27) return;
				
				// spacebar
				if ((ch == ' ') && (jump == 0)) jump = 1;
			}
			
			// wait
			wait(frameTime);
			frameCount++;
			if ((frameCount % 600 == 0) && (frameTime > 2)) frameTime--;
		}
	}
}
