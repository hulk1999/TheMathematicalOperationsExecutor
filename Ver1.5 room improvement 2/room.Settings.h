void createInterfaceSettings(){
	textColor(15);
	system("cls");
	goToXY(0, 0); printf("Press Esc to back");
	goToXY(45, 2); printf("	           __  __  _");
	goToXY(45, 3); printf("  ___ ___ / /_/ /_(_)__  ___ ____");
	goToXY(45, 4); printf(" (_-</ -_) __/ __/ / _ \\/ _ `(_-<");
	goToXY(45, 5); printf("/___/\\__/\\__/\\__/_/_//_/\\_, /___/");
	goToXY(45, 6); printf("                       /___/");
	goToXY(119, 29);
	getchar();
}

void roomSettings(){
	createInterfaceSettings();
}
