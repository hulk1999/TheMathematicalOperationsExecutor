// create interface for room.Credits
void createInterfaceCredits(int firstColor){
	
	// print title
	textColor(firstColor);
	system("cls");
	goToXY(0, 0); printf("Press Esc to back");
	goToXY(45, 2); printf("                 ___ __");
	goToXY(45, 3); printf(" ___________ ___/ (_) /____");
	goToXY(45, 4); printf("/ __/ __/ -_) _  / / __(_-<");
	goToXY(45, 5); printf("\\__/_/  \\__/\\___/_/\\__/___/");
	goToXY(119, 29);
}

// room.Credits main
void roomCredits(int firstColor, int secondColor){
	
	// create interface
	createInterfaceCredits(firstColor);
	
	// check for esc
	char ch;
	do{
		ch = getch();
		
		// esc
		if (ch == 27) return;
	} while(1);
}
