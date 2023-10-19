#include "Selection.hpp"

#include <iostream>

Selection::Selection(sf::RenderWindow &window, TextDoc &doc, int fontSize, int charWidth)
    : _window(window), _doc(doc) {
    _isSelectionExist = false;
    _charWidth = charWidth;
    _fontSize = fontSize;
}

void Selection::createSelection(int startLine, int startCharIndex, int endLine, int endCharIndex) {
    // checking that selection is in the bounds of the text;

    // if (startLine < 1 || startCharIndex < 0 || endLine > _doc.getLineCount() ||
    //  endCharIndex + 1 > _doc.getCharInLineAmount(endLine)) {
    //  return;
    //}

    // TODO - draw it line by line.
    _isSelectionExist = true;
    _startLine = startLine;
    _startCharIndex = startCharIndex;
    _endLine = endLine;
    _endCharIndex = endCharIndex;

    int y_offset = 0;
    float x_length = _charWidth * (endCharIndex - startCharIndex);
    float y_length = (endLine - startLine + 1) * _fontSize;
    sf::RectangleShape selectionShape(sf::Vector2f(x_length, y_length));
    selectionShape.setFillColor(sf::Color(175, 89, 194));
    selectionShape.setPosition(
        sf::Vector2f(startCharIndex * _charWidth, (startLine * _fontSize) - _fontSize));
    _selShape = selectionShape;

    _window.draw(selectionShape);
}

void Selection::removeSelection() {
    sf::RectangleShape removedShape(sf::Vector2f(0, 0));
    _selShape = removedShape;
}

sf::RectangleShape Selection::getSelectedShape() const { return _selShape; }

bool Selection::isSelection() const { return _isSelectionExist; }