#include "Selection.hpp"

#include <iostream>
#define FONT_SIZE 18
#define MARGIN_OFFSET_X 40

Selection::Selection(sf::RenderWindow &window, TextDoc &doc, int fontSize, int charWidth)
    : _window(window), _doc(doc) {
    _isSelectionExist = false;
    _charWidth = charWidth;
    _fontSize = fontSize;
}

void Selection::createSelection(int startLine, int startCharIndex, int endLine, int endCharIndex) {
    _isSelectionExist = true;
    _startLine = startLine;
    _startCharIndex = startCharIndex;
    _endLine = endLine;
    _endCharIndex = endCharIndex;

    sf::Text text;
    sf::Font font;
    font.loadFromFile("../../fonts/JetBrainsMono-Regular.ttf");
    text.setFont(font);
    text.setCharacterSize(FONT_SIZE);

    for (int i = startLine; i <= endLine; i++) {
        text.setString(_doc.getLine(i));

        // x and y cordinates of a bounding box of a full line.
        int x_length = text.findCharacterPos(_doc.getLine(i).length() - 1).x;
        int y_length = _fontSize;

        // if only one line is selected
        if (startLine == endLine) {
            sf::RectangleShape selectionShape(sf::Vector2f(
                text.findCharacterPos(endCharIndex).x - text.findCharacterPos(startCharIndex).x,
                y_length));
            selectionShape.setFillColor(sf::Color(175, 89, 194));
            selectionShape.setPosition(
                sf::Vector2f(text.findCharacterPos(startCharIndex).x + MARGIN_OFFSET_X,
                             (startLine * _fontSize) - _fontSize));
            _window.draw(selectionShape);
            _selections.push_back(selectionShape);
            break;
        }
        // first line of a multiple line selection.
        if (i == startLine) {
            sf::RectangleShape selectionShape(
                sf::Vector2f(x_length - text.findCharacterPos(startCharIndex).x, y_length));
            selectionShape.setFillColor(sf::Color(175, 89, 194));
            selectionShape.setPosition(
                sf::Vector2f(text.findCharacterPos(startCharIndex).x + MARGIN_OFFSET_X,
                             (i * _fontSize) - _fontSize));
            _window.draw(selectionShape);
            _selections.push_back(selectionShape);
            continue;

            // if there is multiple lines and we aren't on the first line or last line.
        } else if (i != endLine) {
            sf::RectangleShape selectionShape(sf::Vector2f(x_length, y_length));
            selectionShape.setFillColor(sf::Color(175, 89, 194));
            selectionShape.setPosition(sf::Vector2f(MARGIN_OFFSET_X, (i * _fontSize) - _fontSize));
            _window.draw(selectionShape);
            _selections.push_back(selectionShape);

            // if we are on the final line and multiple lines are selected.
        } else {
            sf::RectangleShape selectionShape(
                sf::Vector2f(text.findCharacterPos(endCharIndex).x, y_length));
            selectionShape.setFillColor(sf::Color(175, 89, 194));
            selectionShape.setPosition(sf::Vector2f(MARGIN_OFFSET_X, (i * _fontSize) - _fontSize));
            _window.draw(selectionShape);
            _selections.push_back(selectionShape);
        }
    }
    saveDataToSelectionBuffer(startLine, startCharIndex, endLine, endCharIndex);
}

void Selection::removeSelection() { _selections.clear(); }

std::string Selection::getSelectionData() const { return _selectionData; }

std::pair<int, int> Selection::getStartCharLine() const {
    return std::make_pair(_startCharIndex, _startLine);
}

std::pair<int, int> Selection::getEndCharLine() const {
    return std::make_pair(_endCharIndex, _endLine);
}

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
            newString =
                _doc.getLine(i).substr(startCharIndex, _doc.getLine(i).length() - startCharIndex);

            // multiple line, not at end and not at start.
        } else if (i != endLine) {
            newString += _doc.getLine(i);

            // if we are on the final line and multiple lines are selected.
        } else {
            newString += _doc.getLine(i).substr(0, endCharIndex);
            _selectionData = newString;
        }
    }
}

sf::RectangleShape Selection::getSelectedShape() const { return _selShape; }

std::vector<sf::RectangleShape> Selection::getSelections() const { return _selections; }

bool Selection::isSelection() const { return _isSelectionExist; }