#pragma once
#include "../../src/textDocument/doc.hpp"
#include <iostream>
#include <vector>

class TextCursor
{
public:
  TextCursor(TextDoc& doc, int initial_x = 0, int initial_y = 0);
  ~TextCursor(){};
  // setters
  void moveOneUp();
  void moveOneDown();
  void moveOneLeft();
  void moveOneRight();

  void moveUpEndLine();

  void setCursorPos(int line, int charIndex);
  void moveToNextLineStart();

  // getters
  int getCurrentLine();
  int getCurrentCharIdx();

private:
  TextDoc& _doc;
  int _line;
  int _charIdx;

  std::pair<int, int> _currentPos;
  std::vector<int> numOfCharInLines;

  void updatePos(int line, int charIndex);
  void updateNumOfCharInLines();
};