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

    int x_offset = 4;
    // float x_length = _charWidth * (endCharIndex - startCharIndex);
    // float y_length = (endLine - startLine + 1) * _fontSize;

    for (int i = startLine; i <= endLine; i++) {
        int x_length = _doc.getLine(i).length() * _charWidth;
        int y_length = _fontSize;

        // if only one line is selected
        if (startLine == endLine) {
            sf::RectangleShape selectionShape(
                sf::Vector2f((endCharIndex - startCharIndex) * _charWidth, y_length));
            selectionShape.setFillColor(sf::Color(175, 89, 194));
            selectionShape.setPosition(
                sf::Vector2f(startCharIndex * _charWidth, (startLine * _fontSize) - _fontSize));
            _window.draw(selectionShape);
            _selections.push_back(selectionShape);
            break;
        }

        // TODO - fix all multiple lines - going to the end, except last line
        //  if there is multiple lines and we are on the first line.
        if (i == startLine) {
            sf::RectangleShape selectionShape(
                sf::Vector2f((_doc.getLine(i).length() - startCharIndex) * _charWidth, y_length));
            selectionShape.setFillColor(sf::Color(175, 89, 194));
            selectionShape.setPosition(
                sf::Vector2f(startCharIndex * _charWidth, (i * _fontSize) - _fontSize));
            _window.draw(selectionShape);
            _selections.push_back(selectionShape);
            continue;

            // if there is multiple lines and we aren't on the first line or last line.
        } else if (i != endLine) {
            sf::RectangleShape selectionShape(sf::Vector2f(x_length, y_length));
            selectionShape.setFillColor(sf::Color(175, 89, 194));
            selectionShape.setPosition(sf::Vector2f(0, (i * _fontSize) - _fontSize));
            _window.draw(selectionShape);
            _selections.push_back(selectionShape);

            //////////////////////this is working as excpected////////////////////////////
            // if we are on the final line and multiple lines are selected.
        } else {
            sf::RectangleShape selectionShape(sf::Vector2f(endCharIndex * _charWidth, y_length));
            selectionShape.setFillColor(sf::Color(175, 89, 194));
            selectionShape.setPosition(sf::Vector2f(0, (i * _fontSize) - _fontSize));
            _window.draw(selectionShape);
            _selections.push_back(selectionShape);
        }
    }
}

void Selection::removeSelection() { _selections.clear(); }

sf::RectangleShape Selection::getSelectedShape() const { return _selShape; }

std::vector<sf::RectangleShape> Selection::getSelections() const { return _selections; }

bool Selection::isSelection() const { return _isSelectionExist; }