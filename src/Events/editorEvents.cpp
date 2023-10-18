#include "editorEvents.hpp"

bool EditorEvents::mouseWheelEvent(sf::Event event) {
    if (sf::Event::MouseWheelScrolled == event.type) {
        return true;
    }
    return false;
}
