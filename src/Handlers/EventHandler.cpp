#include "EventHandler.hpp"

EventHandler::EventHandler(EditorView& editorView, TextCursor& textCursor, Selection& select)
    : _view(editorView), _cursor(textCursor), _select(select) {}

void EventHandler::handleEvents(sf::RenderWindow& window, sf::Event& event) {}

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
                mapPixelsToLineChar(currentCord.x, currentCord.y, 4);

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

        // TODO - values inserted to created selection are wrong - lastCharLine
        std::pair<int, int> lastCharLine = mapPixelsToLineChar(lastCord.x, lastCord.y, 0);

        _select.createSelection(_currentCharLine.second, _currentCharLine.first,
                                lastCharLine.second, lastCharLine.first);
    }
}

Selection& EventHandler::getSelection() const { return _select; }

std::pair<int, int> EventHandler::mapPixelsToLineChar(int x, int y, int initial_offset_x) {
    std::pair<int, int> lineChar;
    lineChar.first = x / _view.getCharWidth() - initial_offset_x;  // character
    lineChar.second = y / _view.getFontSize() + 1;                 // line

    return lineChar;
}
