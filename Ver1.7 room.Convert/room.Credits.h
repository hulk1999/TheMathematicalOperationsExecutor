//-----------------------------------------------declaration------------------------------------------------------------------//

// functions for creating interface
void createInterfaceCredits(int firstColor);

// room.Credits main
void roomCredits(int firstColor, int secondColor);

//----------------------------------------------------------------------------------------------------------------------------//

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
	
	// print contents
	goToXY(28, 11); printf("This project is dedicated to F-CODE, our mentors - our friends");
	goToXY(34, 16); printf("HUNG HUNG HANG");
	goToXY(70, 16); printf("CHI MINH GAT");
	
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
