#include "EventHandler.hpp"

EventHandler::EventHandler(EditorView& editorView, TextCursor& textCursor)
    : _view(editorView), _cursor(textCursor) {}

void EventHandler::handleEvents(sf::RenderWindow& window, sf::Event& event) {}

void EventHandler::handleMouseEvents(sf::RenderWindow& window, sf::Event& event) {
    // Mouse scroll event
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            if (event.mouseWheelScroll.delta > 0) {
                _view.scrollUp();
                std::cout << "scroll up" << std::endl;
            } else {
                _view.scrollDown();
                std::cout << "scroll down" << std::endl;
            }
        } else {
            if (event.mouseWheelScroll.delta > 0) {
                _view.scrollLeft();
            } else {
                _view.scrollRight();
            }
        }
    }

    // TODO mouse press
}
