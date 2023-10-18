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
            sf::Vector2i currentCord;
            currentCord.x = event.mouseButton.x;
            currentCord.y = event.mouseButton.y;

            // order in pair: first is character, second is line
            std::pair<int, int> currentCharLine =
                mapPixelsToLineChar(currentCord.x, currentCord.y);
            _cursor.setCursorPos(currentCharLine.second, currentCharLine.first);
            _view.drawTextCursor(_cursor);

            sf::Vector2i lastCord = currentCord;
            // TODO - button is always pressed in while loop ///////////////////////////////
            while (_isMousePressed) {
                std::cout << "event is: " << event.type << std::endl;
                if (event.type == sf::Event::MouseButtonReleased) {
                    _isMousePressed = false;
                }
                lastCord = sf::Mouse::getPosition();
            }
            ///////////////////////////////////////////////////////////////////////////////
            std::pair<int, int> lastCharLine = mapPixelsToLineChar(lastCord.x, lastCord.y);

            if (lastCord != currentCord) {
                _select.createSelection(currentCharLine.second, currentCharLine.first,
                                        lastCharLine.second, lastCharLine.first);
            }
            _cursor.setCursorPos(lastCharLine.second, lastCharLine.first);
            _view.drawTextCursor(_cursor);
        }
    }
}

std::pair<int, int> EventHandler::mapPixelsToLineChar(int x, int y) {
    std::pair<int, int> lineChar;
    lineChar.first = x / _view.getCharWidth();  // character
    lineChar.second = y / _view.getFontSize();  // line

    return lineChar;
}
