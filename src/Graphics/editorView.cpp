#include "editorView.hpp"

#include <iostream>

#include "../TextCursor/TextCursor.hpp"

EditorView::EditorView(sf::RenderWindow& window, EditorEvents& events, TextDoc& doc)
    :

      _camera(sf::FloatRect(-50, 0, window.getSize().x, window.getSize().y)),
      _deltaScroll(20),
      _deltaZoomIn(0.8f),
      _deltaZoomOut(1.2f),
      _events(events),
      _doc(doc),
      _window(window) {
    _font.loadFromFile("../../fonts/JetBrainsMono-Regular.ttf");
    setFontSize(18);
    _marginOffset_x = 40;
    _colorMargin = sf::Color(32, 44, 68);
    _charColor = sf::Color::White;

    _windowLength = _window.getSize().x;
    _windowWidth = _window.getSize().y;
}

void EditorView::drawWindow(sf::RenderWindow& window) {
    // drawing the text itself.
    _drawStrings(_doc);

    // creating the line counter text on the sidebar
    for (int lineNum = 1; lineNum < _doc.getLineCount() + 1; lineNum++) {
        int lineHeight = 1;
        int blockHeight = lineHeight * _fontSize;

        sf::Text lineNumberText;
        lineNumberText.setFillColor(sf::Color::White);
        lineNumberText.setFont(_font);
        lineNumberText.setString(std::to_string(lineNum));
        lineNumberText.setCharacterSize(_fontSize - 1);
        lineNumberText.setPosition(0, blockHeight * (lineNum - 1));

        // creating rectangle behind text to contrast.
        sf::RectangleShape marginRect(sf::Vector2f(_marginOffset_x, blockHeight));
        marginRect.setFillColor(_colorMargin);
        marginRect.setPosition(_marginOffset_x - 40, blockHeight * (lineNum - 1));

        // draw rectangle and text
        _window.draw(marginRect);
        _window.draw(lineNumberText);

        if (lineNum == _doc.getLineCount()) {
            _bottomPixelLimit = blockHeight * lineNum;
        }
    }
}

void EditorView::scrollUp() {
    if (_camera.getCenter().y > _window.getSize().y / 2) {
        _camera.move(0, -_deltaScroll / 2);
        setViewToCamera();
    }
}

void EditorView::scrollDown() {
    if (_camera.getCenter().y < _bottomPixelLimit) {
        _camera.move(0, _deltaScroll / 2);
        setViewToCamera();
    }
}
// TODO add control flow to scroll left and right.
void EditorView::scrollLeft() {
    _camera.move(-_deltaScroll / 2, 0);
    setViewToCamera();
}

void EditorView::scrollRight() {
    _camera.move(_deltaScroll / 2, 0);
    setViewToCamera();
}

void EditorView::scrollTo(float x, float y) {
    _camera.move(x, y);
    setViewToCamera();
}

int EditorView::getWindowWidth() { return _windowWidth; }

int EditorView::getWindowLength() { return _windowLength; }

sf::View EditorView::getCameraView() { return _camera; }

void EditorView::setCamera(int width, int height) {
    _camera = sf::View(sf::FloatRect(0, 0, width, height));
}

void EditorView::setFontSize(int size) {
    _fontSize = size;
    _lineHeight = _fontSize;

    // This a trick to find char width, only works because we are using monospace
    // font(we get the char width of a wide character)

    sf::Text tmpText;
    tmpText.setFont(_font);
    tmpText.setCharacterSize(_fontSize);
    tmpText.setString("_");
    float textwidth = tmpText.getLocalBounds().width;
    _charWidth = textwidth;
}

void EditorView::setViewToCamera() {
    _camera.setCenter(_camera.getCenter().x, _camera.getCenter().y);
    _window.setView(_camera);
}

void EditorView::_drawStrings(TextDoc& doc) {
    sf::Text newString;
    sf::Color color;
    sf::Vector2f cord;

    int numOfLines = doc.getLineCount();
    // initial text start offset.
    cord.x = _marginOffset_x;
    cord.y = 0;

    for (int i = 0; i < numOfLines; i++) {
        newString.setString(doc.getLine(i + 1));
        newString.setFillColor(color.White);
        newString.setOutlineColor(color.White);
        newString.setPosition(cord);
        newString.setFont(_font);
        newString.setCharacterSize(_fontSize);
        cord.y += _fontSize;

        if (_window.isOpen()) {
            _window.draw(newString);
        } else {
            throw "Window is closed, unable to output text.";
        }
    }
}

void EditorView::drawTextCursor(TextCursor textCursor) {
    sf::Text text;
    sf::Font font;
    font.loadFromFile("../../fonts/JetBrainsMono-Regular.ttf");
    text.setFont(font);
    text.setCharacterSize(_fontSize);
    text.setString(_doc.getLine(textCursor.getCurrentPos().second));

    int curr_x_pos = text.findCharacterPos(textCursor.getCurrentPos().first).x + _marginOffset_x;
    //(textCursor.getCurrentPos().second * _fontSize) is the offset for spacing
    // between lines.
    int curr_y_pos = textCursor.getCurrentPos().second * _lineHeight +
                     (textCursor.getCurrentPos().second * _fontSize);
    int cursorDrawWidth = 2;

    sf::Vector2f rec(cursorDrawWidth, _lineHeight);
    sf::RectangleShape cursorShape(rec);
    cursorShape.setPosition(curr_x_pos, (curr_y_pos / 2) - _fontSize);
    cursorShape.setFillColor(sf::Color::White);
    _window.draw(cursorShape);
}

int EditorView::getFontSize() { return _fontSize; }
int EditorView::getCharWidth() { return _charWidth; }

TextDoc& EditorView::getDoc() { return _doc; }