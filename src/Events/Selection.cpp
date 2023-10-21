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

    _isSelectionExist = true;
    _startLine = startLine;
    _startCharIndex = startCharIndex;
    _endLine = endLine;
    _endCharIndex = endCharIndex;

    for (int i = startLine; i <= endLine; i++) {
        int x_length = _doc.getLine(i).length() * (_charWidth + 2.5);
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

        if (i == startLine) {
            sf::RectangleShape selectionShape(sf::Vector2f(
                (_doc.getLine(i).length() - startCharIndex) * (_charWidth + 2.5), y_length));
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

// TODO - create a fuction that will acuretly get each character size and convert it to pixel, and
// compare it to the position of the screen, also change parameters in saveDataSelectionToBuffer().
void Selection::saveDataToSelectionBuffer(int startLine, int startCharIndex, int endLine,
                                          int endCharIndex) {
    _selectionData.clear();
    std::string newString;
    for (int i = startLine; i <= endLine; i++) {
        // if only one line is selected
        if (startLine == endLine) {
            newString = _doc.getLine(i).substr(startCharIndex, (endCharIndex - startCharIndex));
            _selectionData = newString;
            break;
        }
        // first line of a multiple line selection.
        if (i == startLine) {
            newString = _doc.getLine(i);

            // multiple line, not at end and not at start.
        } else if (i != endLine) {
            newString += _doc.getLine(i);

            // if we are on the final line and multiple lines are selected.
        } else {
            newString += _doc.getLine(i).substr(0, endCharIndex);
            _selectionData = newString;
        }
    }
    std::cout << _selectionData << std::endl;
}

sf::RectangleShape Selection::getSelectedShape() const { return _selShape; }

std::vector<sf::RectangleShape> Selection::getSelections() const { return _selections; }

bool Selection::isSelection() const { return _isSelectionExist; }