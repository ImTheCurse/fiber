#include "EventHandler.hpp"
#define MARGIN_X_OFFSET 40
EventHandler::EventHandler(EditorView& editorView, TextCursor& textCursor, Selection& select)
    : _view(editorView), _cursor(textCursor), _select(select) {}

void EventHandler::handleEvents(sf::RenderWindow& window, sf::Event& event) {
    // handling constant keyPress "events"(not events, because events holds only a sinle value at a
    // time)
    handleKeyPressedEvents();

    // handling mouse events
    if (event.type == sf::Event::MouseButtonPressed ||
        event.type == sf::Event::MouseWheelScrolled ||
        event.type == sf::Event::MouseButtonReleased) {
        handleMouseEvents(window, event);
    }
}

void EventHandler::handleMouseEvents(sf::RenderWindow& window, sf::Event& event) {
    // Mouse scroll event
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            if (event.mouseWheelScroll.delta > 0) {
                _view.scrollUp();

            } else {
                _view.scrollDown();
            }
        } else {
            if (event.mouseWheelScroll.delta > 0) {
                _view.scrollLeft();
            } else {
                _view.scrollRight();
            }
        }
    }
    // mouse press or mouse select
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            // remove selection done at the start because if the button was pressed once, it won't
            // select text.
            _select.removeSelection();
            _isMousePressed = true;
            sf::Vector2i currentViewCord;

            // cordinates are relative to current view.
            sf::Vector2f currentCord;

            currentViewCord.x = event.mouseButton.x;
            currentViewCord.y = event.mouseButton.y;

            currentCord = window.mapPixelToCoords(currentViewCord);

            // order in pair: first is character, second is line
            std::pair<int, int> currentCharLine =
                mapPixelsToLineChar(currentCord.x, currentCord.y);

            _currentCharLine = currentCharLine;

            _cursor.setCursorPos(currentCharLine.second, currentCharLine.first);
            _view.drawTextCursor(_cursor);

            /////////////////////////////////////////////////////////////////////////////
        }
    }

    sf::Vector2f lastCord = _currentWorldCord;
    sf::Vector2i tempCord;

    if (event.type == sf::Event::MouseButtonReleased) {
        tempCord = sf::Mouse::getPosition(window);
        lastCord = window.mapPixelToCoords(tempCord);

        std::pair<int, int> lastCharLine = mapPixelsToLineChar(lastCord.x, lastCord.y);

        _select.createSelection(_currentCharLine.second, _currentCharLine.first,
                                lastCharLine.second, lastCharLine.first);
    }
}

void EventHandler::handleKeyPressedEvents() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
        // moving from selection buffer to EventBuffer.
        _buffer.clear();
        _buffer = _select.getSelectionData();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
        std::pair<int, int> cursorPos = _cursor.getCurrentPos();
        if (cursorPos.first <= _view.getDoc().getLine(cursorPos.second).length()) {
            _view.getDoc().addTextToLine(cursorPos.second, cursorPos.first, _buffer);
        }
    }
}

Selection& EventHandler::getSelection() const { return _select; }

std::pair<int, int> EventHandler::mapPixelsToLineChar(int x, int y) {
    sf::Text text;
    sf::Font font;
    font.loadFromFile("../../fonts/JetBrainsMono-Regular.ttf");
    text.setFont(font);
    text.setCharacterSize(_view.getFontSize());

    std::pair<int, int> lineChar;
    lineChar.second = y / _view.getFontSize() + 1;  // line

    int i = _view.getDoc().getLine(lineChar.second).length();
    text.setString(_view.getDoc().getLine(lineChar.second));
    while (text.findCharacterPos(i - 1).x > x - MARGIN_X_OFFSET) {
        i--;
    }

    lineChar.first = i;  // character

    return lineChar;
}
