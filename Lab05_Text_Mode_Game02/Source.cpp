#include<stdio.h>
#include<windows.h>
#include<conio.h>
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void draw_ship(int x, int y)
{
	setcolor(2, 4);
	gotoxy(x, y); 
	printf("<-0->");
}
void draw_bullet(int xb, int yb)
{
	setcolor(14 , 0);
	gotoxy(xb , yb);
	printf("|");
}
void erase_ship(int x, int y)
{
	gotoxy(x, y);
	setcolor(2, 0);
	printf("     ");
}
void erase_bullet(int xb, int yb)
{
	gotoxy(xb , yb);
	setcolor(2, 0);
	printf(" ");
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
int main()
{
	setcursor(0);
	int gun[5] = { 0 }, ax[5] = { 0 }, ay[5] = { 0 };
	int bullet = 0;
	char dir = 's';
	char ch = '.';
	int x = 38, y = 20;
	int xb = x, yb = y;
	draw_ship(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a')
				dir = 'l';
			if (ch == 'd')
				dir = 'r';
			if (ch == 's')
				dir = 'p';
			if (ch == ' ') {
				for (int i = 0; i < 5; i++) {
					if (gun[i] == 0) {
						gun[i] = 1;
						ax[i] = x + 2;
						ay[i] = y - 1;
						break;
					}
				}
			}
			fflush(stdin);
		}
		if (dir == 'l' && x > 0) { erase_ship(x, y); draw_ship(--x, y); }
		if (dir == 'r' && x < 75) { erase_ship(x, y); draw_ship(++x, y); }
		if (dir == 'p') { erase_ship(x, y);  draw_ship(x, y); }
		for (int i = 0; i < 5; i++) {
			if (gun[i] == 1 && ay[i] > 0) {
				erase_bullet(ax[i], ay[i]);  draw_bullet(ax[i], --ay[i]);
			}
			if (gun[i] == 1 && ay[i] == 0) {
				erase_bullet(ax[i], ay[i]);
				gun[i] = 0;
			}
		}
		Sleep(100);
	} while (ch != 'x');
	return 0;
}