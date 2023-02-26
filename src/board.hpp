#include <stdlib.h>
#include <ncurses.h>

enum class Piece {
  None, Normal
};

class Board {
 private:
     int _width;
     int _height;
     Piece* _board;
     char* _board_as_string;

     int _cursor_x;
     int _cursor_y;
 public:
     Board(int width, int height);
     ~Board();

 public:
     void draw_board();
     void debug();
     void set_piece(int x, int y, Piece p);
     void step_board_state();

     int get_width();
     int get_height();
};

Board::Board(int width, int height) {
  _width = width;
  _height = height;

  int size = _width * _height;

  _board = (Piece*)malloc(size * sizeof(Piece));
  for (int i = 0; i < size; i++)
  {
    _board[i] = Piece::None;
  }

  // allocate _width more memory than board size to store each new line char
  _board_as_string = (char*)malloc(size * sizeof(Piece) + _width);
}

int Board::get_width() {
  return _width;
}

int Board::get_height() {
  return _height;
}

void Board::draw_board() {
  for (int y = 0; y < _height; y++)
  {
    for (int x = 0; x < _width; x++)
    {
      Piece p = _board[y*_width+x];
      switch (p)
      {
        case Piece::None:
          _board_as_string[y * (_width+1) + x] = '.';
          break;
        case Piece::Normal:
          _board_as_string[y * (_width+1) + x] = 'o';
      }
    }
    // If we are at the end of a row, insert a new line
    _board_as_string[y * (_width+1) + _width] = '\n';
  }

  printw("%s", _board_as_string);

  attron(COLOR_PAIR(1));
  move(0,0);
  mvaddch(_cursor_y, _cursor_x, _board_as_string[(_cursor_y * _width + 1) + _cursor_x]);
  attroff(COLOR_PAIR(1));
}

void Board::set_piece(int x, int y, Piece p) {
  if (x < _width && x >= 0  && y < _height && y >= 0)
    _board[y * _width + x] = p;
}

void Board::step_board_state() {
  
}

Board::~Board() {
  free(_board);
  free(_board_as_string);
}
