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
	gotoxy(x, y); 
	printf("<--0-->");
}
void draw_ammo(int x, int y)
{
	gotoxy(x , --y);
	setcolor(14 , 0);
	printf("   A   ");
}
void erase_ship(int x, int y)
{
	gotoxy(x, y);
	printf("       ");
}
void erase_ammo(int x, int y)
{
	gotoxy(x , --y);
	printf("       ");
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
	char ch = '.';
	int x1 = 38, y1 = 20, x2 = 38, y2 = 20, i = 0, j = 0;
	setcolor(2, 4);
	draw_ship(x1, y1);
	setcolor(2, 0);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') {
				i = 1;
			}
			if (ch == 'd') {
				i = 2;
			}
			if (ch == 's') {
				i = 0;
			}
			if (ch == ' ') {
				j = 1;
			}
			fflush(stdin);
		}
		if (i == 1 && x1>1) {
			erase_ship(x1, y1);
			setcolor(2, 4);
			draw_ship(--x1, y1);
			setcolor(2, 0);
			Sleep(100);
		}
		if (i == 2 && x1<113) {
			erase_ship(x1, y1);
			setcolor(2, 4);
			draw_ship(++x1, y1);
			setcolor(2, 0);
			Sleep(100);
		}
		if (j == 0) {
			x2 = x1;
		}
		if (j == 1 && y2 > 1) {
			erase_ammo(x2, y2);
			draw_ammo(x2, --y2);
		}
		if (y2 == 1) {
			erase_ammo(x2, y2);
			j = 0; 
			y2 = y1;
		}
	} while (ch != 'x');
	return 0;
}