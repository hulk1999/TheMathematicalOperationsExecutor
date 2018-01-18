void createInterfaceCredits(){
	textColor(15);
	system("cls");
	goToXY(0, 0); printf("Press Esc to back");
	goToXY(45, 2); printf("                 ___ __");
	goToXY(45, 3); printf(" ___________ ___/ (_) /____");
	goToXY(45, 4); printf("/ __/ __/ -_) _  / / __(_-<");
	goToXY(45, 5); printf("\\__/_/  \\__/\\___/_/\\__/___/");
	goToXY(119, 29);
}

void roomCredits(){
	
	createInterfaceCredits();
	
	char ch;
	do{
		ch = getch();
		if (ch == 27) return; // esc
	} while(1);
}
