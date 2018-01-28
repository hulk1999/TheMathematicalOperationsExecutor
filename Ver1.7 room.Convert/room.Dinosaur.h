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

// room.Dinosaur main
void roomDinosaur(int firstColor, int secondColor){
	
	// create interface
	createInterfaceDinosaur(firstColor);
	
	// check for esc
	char ch;
	do{
		ch = getch();
		
		// esc
		if (ch == 27) return;
	} while(1);
}