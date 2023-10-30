#include "EventHandler.hpp"

#include <SFML/Window/Clipboard.hpp>

#define MARGIN_X_OFFSET 40
EventHandler::EventHandler(EditorView& editorView, TextCursor& textCursor, Selection& select)
    : _view(editorView), _cursor(textCursor), _select(select) {}

void EventHandler::handleEvents(sf::RenderWindow& window, sf::Event& event) {
    // handling constant keyPress "events"(not events, because events holds only a sinle value at a
    // time)

    handleKeyPressedEvents(event);

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

void EventHandler::handleKeyPressedEvents(sf::Event event) {
    bool isCtrlPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
                         sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);

    if (isCtrlPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            // moving from selection buffer to EventBuffer.
            _buffer.clear();
            _buffer = _select.getSelectionData();
        }

        else if (event.key.code == sf::Keyboard::V) {
            pasteContent();
        }
    }

    if (_select.isSelection() && event.type == sf::Event::KeyReleased &&
        event.text.unicode == sf::Keyboard::Backspace) {
        _view.getDoc().deleteSelectionText(_select);
        _select.removeSelection();
    }

    else if (event.type == sf::Event::KeyReleased &&
             event.text.unicode == sf::Keyboard::Backspace &&
             _lastKeyPressed == 8 /*key of backspace when pressing it*/) {
        int currentLine = _cursor.getCurrentLine();
        int currentCharIdx = _cursor.getCurrentCharIdx();

        if (currentLine == 1 && currentCharIdx == 0)
            return;

        _view.getDoc().deleteTextFromLine(currentLine, currentCharIdx - 1, 1);

        if (currentCharIdx == 0) {
            currentLine--;
            currentCharIdx = _view.getDoc().getLine(currentLine).length();
        }
        _cursor.setCursorPos(currentLine, currentCharIdx - 1);
    }

    if (event.type == sf::Event::KeyReleased && event.text.unicode == sf::Keyboard::Space &&
        _lastKeyPressed == 32 /*key press when space is pressed*/) {
        if (_view.getDoc().getLine(_cursor.getCurrentLine()) == "\n") {
            return;
        }

        _view.getDoc().addTextToLine(_cursor.getCurrentLine(), _cursor.getCurrentCharIdx(), " ");
        _cursor.setCursorPos(_cursor.getCurrentLine(), _cursor.getCurrentCharIdx() + 1);
    }

    if (event.type == sf::Event::KeyPressed && event.text.unicode == sf::Keyboard::Up &&
        _wasLastKeyReleased) {
        _cursor.setCursorPos(_cursor.getCurrentLine() - 1, _cursor.getCurrentCharIdx());
    }

    if (event.type == sf::Event::KeyPressed && event.text.unicode == sf::Keyboard::Down &&
        _wasLastKeyReleased) {
        _cursor.setCursorPos(_cursor.getCurrentLine() + 1, _cursor.getCurrentCharIdx());
    }

    if (event.type == sf::Event::KeyPressed && event.text.unicode == sf::Keyboard::Right &&
        _wasLastKeyReleased) {
        _cursor.setCursorPos(_cursor.getCurrentLine(), _cursor.getCurrentCharIdx() + 1);
    }

    if (event.type == sf::Event::KeyPressed && event.text.unicode == sf::Keyboard::Left &&
        _wasLastKeyReleased) {
        _cursor.setCursorPos(_cursor.getCurrentLine(), _cursor.getCurrentCharIdx() - 1);
    }

    if (event.type == sf::Event::KeyReleased) {
        _wasLastKeyReleased = true;
    } else {
        _wasLastKeyReleased = false;
    }
    _lastKeyPressed = event.text.unicode;
}

void EventHandler::pasteContent() {
    std::pair<int, int> cursorPos = _cursor.getCurrentPos();
    if (cursorPos.first <= _view.getDoc().getLine(cursorPos.second).length()) {
        _view.getDoc().addTextToLine(cursorPos.second, cursorPos.first, _buffer);
        _buffer.clear();
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
