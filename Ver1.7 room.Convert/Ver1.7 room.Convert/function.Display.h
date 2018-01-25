// move cusor to column x row y
void goToXY(int x, int y){
	HANDLE handle;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordinate = {x, y};
	SetConsoleCursorPosition(handle, coordinate);
}

// change text color
void textColor(int color){
	HANDLE handle;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);
}

// change font size
void fontSize(int x, int y){
	CONSOLE_FONT_INFOEX info = {0};
	info.cbSize = sizeof(info);
	info.dwFontSize.X = x;
	info.dwFontSize.Y = y;
	info.FontWeight = FW_NORMAL;
	wcscpy(info.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
}

// set console screen size
void setConsoleSize(int width, int height){
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

// wait for time/1000 seconds
void wait(clock_t time){
	clock_t goal;
	goal = time + clock();
	while(goal > clock()) {}
}
