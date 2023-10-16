#include "EventHandler.hpp"

void EventHandler::handleEvents(EditorView& view, sf::RenderWindow& window, sf::Event& event) {}

void EventHandler::handleMouseEvents(EditorView& view, sf::RenderWindow& window,
                                     sf::Event& event) {
    // Mouse scroll event
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            if (event.mouseWheelScroll.delta > 0) {
                view.scrollUp();
            } else {
                view.scrollDown();
            }
        } else {
            if (event.mouseWheelScroll.delta > 0) {
                view.scrollLeft();
            } else {
                view.scrollRight();
            }
        }
    }

    // TODO mouse press
}
