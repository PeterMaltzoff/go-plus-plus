#include <stdlib.h>
#include <ncurses.h>

enum class PieceType {
  None, White, Black 
};

struct Piece {
  
};

class Board {
 private:
     int _width;
     int _height;
     PieceType* _board;
     char* _board_as_string;

     int _cursor_x;
     int _cursor_y;
 public:
     Board(int width, int height);
     ~Board();

 public:
     void draw_board();
     void debug();
     void set_piece(int x, int y, PieceType p);
     void step_board_state();

     int get_width();
     int get_height();
};

Board::Board(int width, int height) {
  _width = width;
  _height = height;

  int size = _width * _height;

  _board = (PieceType*)malloc(size * sizeof(PieceType));
  for (int i = 0; i < size; i++)
  {
    _board[i] = PieceType::None;
  }

  // allocate +1 for each row to store each new line char
  _board_as_string = (char*)malloc(size * sizeof(PieceType) + _height);
}

Board::~Board() {
  free(_board);
  free(_board_as_string);
}

int Board::get_width() {
  return _width;
}

int Board::get_height() {
  return _height;
}

void Board::draw_board() {
  for (int y = 0; y < _height; y++) {
    for (int x = 0; x < _width; x++) {
      PieceType p = _board[y*_width+x];
      switch (p) {
        case PieceType::None:
          _board_as_string[y * (_width+1) + x] = '.';
          break;
        case PieceType::White:
          _board_as_string[y * (_width+1) + x] = 'o';
          break;
        case PieceType::Black:
          _board_as_string[y * (_width+1) + x] = 'x';
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

void Board::set_piece(int x, int y, PieceType p) {
  if (x < _width && x >= 0  && y < _height && y >= 0)
    _board[y * _width + x] = p;
}

// RULES RULE!!! 8D

// Rule 1. The rule of liberty (god bless). Every stone remaining on the board after a turn must have at least one open point, or be part of a group that has at least one open point.
//
// In order to implement this I need a way to know if a piece is part of a group.
// It is pretty easy to calculate, I just need a place to store the group indexes.

// Rule 2. The ko rule. The stones on the board must never repeat a previous position of stones. Moves which do so are forbidden.
