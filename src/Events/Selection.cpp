#include "Selection.hpp"

Selection::Selection(sf::RenderWindow &window, TextDoc &doc, int fontSize, int charWidth)
    : _window(window), _doc(doc) {
    _isSelectionExist = false;
    _charWidth = charWidth;
    _fontSize = fontSize;
}

void Selection::createSelection(int startLine, int startCharIndex, int endLine, int endCharIndex) {
    if (startLine < 1 || startCharIndex < 0 || endLine > _doc.getLineCount() ||
        endCharIndex + 1 > _doc.getCharInLineAmount(endLine)) {
        return;
    }

    _startLine = startLine;
    _startCharIndex = startCharIndex;
    _endLine = endLine;
    _endCharIndex = endCharIndex;

    int y_offset = 0;
    float x_length = _charWidth * (endCharIndex - startCharIndex);
    float y_length = (endLine - startLine + 1) * _fontSize;
    sf::RectangleShape selectionShape(sf::Vector2f(x_length, y_length));

    selectionShape.setFillColor(sf::Color(175, 89, 194));
    selectionShape.setPosition(sf::Vector2f(startCharIndex * _charWidth, startLine * _fontSize));

    _window.draw(selectionShape);
}