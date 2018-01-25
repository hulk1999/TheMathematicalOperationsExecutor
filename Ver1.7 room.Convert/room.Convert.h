// create interface for room.Convert
void createInterfaceConvert(int firstColor){
	
	// print title
	textColor(firstColor);
	system("cls");
	goToXY(0, 0); printf("Press Esc to back");
	goToXY(24, 2); printf("                   __                                       __");
	goToXY(24, 3); printf("  ___  __ ____ _  / /  ___ ____  _______  ___ _  _____ ____/ /____ ____");
	goToXY(24, 4); printf(" / _ \\/ // /  ' \\/ _ \\/ -_) __/ / __/ _ \\/ _ \\ |/ / -_) __/ __/ -_) __/");
	goToXY(24, 5); printf("/_//_/\\_,_/_/_/_/_.__/\\__/_/    \\__/\\___/_//_/___/\\__/_/  \\__/\\__/_/");
	goToXY(119, 29);
}

// room.Convert main
void roomConvert(int firstColor, int secondColor){
	
	// create interface
	createInterfaceConvert(firstColor);
	
	// check for esc
	char ch;
	do{
		ch = getch();
		
		// esc
		if (ch == 27) return;
	} while(1);
}
