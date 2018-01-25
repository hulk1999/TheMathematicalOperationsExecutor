int firstColorSo, secondColorSo;

// create interface for room.Solve
void createInterfaceSolve(){
	
	// print title
	textColor(firstColorSo);
	system("cls");
	goToXY(0, 0); printf("Press Esc to back");
	goToXY(28, 2); printf("                     __  _                      __");
	goToXY(28, 3); printf(" ___ ___ ___ _____ _/ /_(_)__  ___    ___ ___  / /  _____ ____");
	goToXY(28, 4); printf("/ -_) _ `/ // / _ `/ __/ / _ \\/ _ \\  (_-</ _ \\/ / |/ / -_) __/");
	goToXY(28, 5); printf("\\__/\\_, /\\_,_/\\_,_/\\__/_/\\___/_//_/ /___/\\___/_/|___/\\__/_/");
	goToXY(28, 6); printf("	 /_/");
	goToXY(119, 29);
}

// room.Solve main
void roomSolve(int* pFirstColor, int* pSecondColor){
	
	// assign color
	firstColorSo = *pFirstColor;
	secondColorSo = *pSecondColor;
	
	// create interface
	createInterfaceSolve();
	
	// check for esc
	char ch;
	do{
		ch = getch();
		
		// esc
		if (ch == 27) return;
	} while(1);
}
