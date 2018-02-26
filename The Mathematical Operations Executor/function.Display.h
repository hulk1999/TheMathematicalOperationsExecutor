//-----------------------------------------------declaration------------------------------------------------------------------//

// functions for displaying
void goToXY(int x, int y);
void textColor(int color);
void fontSize(int x, int y);
void wait(clock_t time);

//----------------------------------------------------------------------------------------------------------------------------//

// move cusor to column x row y
void goToXY(int x, int y){
	COORD coordinate = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

// change text color
void textColor(int color){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// change font size
void fontSize(int x, int y){
	CONSOLE_FONT_INFOEX info = {0};
	info.cbSize = sizeof(info);
	info.dwFontSize.X = x;
	info.dwFontSize.Y = y;
	info.FontWeight = FW_NORMAL;
	wcscpy(info.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &info);
}

// set console screen size
void setConsoleSize(int width, int height){
	RECT r;
	GetWindowRect(GetConsoleWindow(), &r);
	MoveWindow(GetConsoleWindow(), r.left, r.top, width, height, TRUE);
	
    COORD coordinates = {120, 30};
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

// wait for time/1000 seconds
void wait(clock_t time){
	clock_t goal;
	goal = time + clock();
	while(goal > clock()) {}
}
