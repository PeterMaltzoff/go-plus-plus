#include <ncurses.h>

int main()
{
  initscr();
  getch();
  refresh();
  endwin();
  return 0;
}


void drawBoard(int width, int height)
{
	for (int y=0; y<height; y++)
	{
		for (int x=0; x<width; x++)
		{
      printw("x");
		}
    printw("\n");
	}
}
