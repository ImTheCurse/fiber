#include "TextCursor.hpp"

#include <string>
TextCursor::TextCursor(TextDoc& doc, int initial_x, int initial_y) : _doc(doc) {
    _currentPos.first = initial_x;
    _currentPos.second = initial_y;
    _line = 1;
    _charIdx = 0;
}

void TextCursor::updatePos(int line, int charIndex) {
    _line = line;
    _charIdx = charIndex;
}

void TextCursor::updateNumOfCharInLines() {
    std::string currLine;
    // this is done so we start from index 1 - same as line count.
    numOfCharInLines.push_back(-1);

    for (int i = 1; i <= _doc.getLineCount(); i++) {
        currLine = _doc.getLine(i);
        numOfCharInLines.push_back(currLine.length());
    }
}

void TextCursor::moveOneDown() {
    if (_line < _doc.getLineCount())
        updatePos(_line + 1, _charIdx);
}

void TextCursor::moveOneUp() {
    if (_line > 1)
        updatePos(_line - 1, _charIdx);
}

void TextCursor::moveOneRight() {
    if (_charIdx < numOfCharInLines[_line] - 1)  // TODO make sure that you are staying within
                                                 // vector bounds(currently seems fine but
                                                 // haven't tested it yet.)
        updatePos(_line, _charIdx + 1);
}

void TextCursor::moveOneLeft() {
    if (_charIdx > 0)
        updatePos(_line, _charIdx - 1);
}

void TextCursor::moveUpEndLine() {
    if (_line > 1)
        updatePos(_line - 1, numOfCharInLines[_line - 1] - 1);
}

void TextCursor::setCursorPos(int line, int charIndex) { updatePos(line, charIndex); }

void TextCursor::moveToNextLineStart() {
    if (_line < _doc.getLineCount())
        updatePos(_line + 1, 0);
}

int TextCursor::getCurrentLine() { return _line; }

int TextCursor::getCurrentCharIdx() { return _charIdx; }
std::pair<int, int> TextCursor::getCurrentPos() {
    _currentPos.first = _charIdx;
    _currentPos.second = _line;
    return _currentPos;
}