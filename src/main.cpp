#include <ncurses.h>
#include "board.hpp"

#define SELECTED_PAIR 1;

void init()
{
  initscr();
  cbreak();
  noecho(); 
  if (has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support color\n");
    exit(1);
  }

  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_GREEN);
}

void main_loop()
{
  Board board(8,8);
  char input = 0;
  int x = 0;
  int y = 0;
  while (input != 'q')
  {
    erase();
    if (input == ' ')
      board.set_piece(x,y,Piece::Normal);
    board.draw_board();
    move(y,x);
    switch (input) {
      case 'w':
        if (y > 0)
          move(--y, x);
        break;
      case 's':
        if (y < board.get_height()-1)
          move(++y, x);
        break;
      case 'a':
        if (x > 0)
          move(y, --x);
        break;
      case 'd':
        if (x < board.get_width()-1)
          move(y, ++x);
        break;
    }
    refresh();
    input = getch();
  }
}

int main()
{
  init();
  main_loop();
  endwin();

  return 0;
}
