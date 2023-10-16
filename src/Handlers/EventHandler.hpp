#pragma once
#include <SFML/Graphics.hpp>

#include "../Graphics/editorView.hpp"
#include "../TextCursor/TextCursor.hpp"
#include "../TextDocument/doc.hpp"

class EventHandler {
  public:
    EventHandler(EditorView& editorView, TextCursor& textCursor, TextDoc& doc /*,Selection &sel*/);

    void handleEvents(EditorView& view, sf::RenderWindow& window, sf::Event& event);

  private:
    void handleMouseEvents(EditorView& view, sf::RenderWindow& window, sf::Event& event);
    // void handleKeyPressedEvents(EditorView& view, sf::Event& event);
    // void handleKeyReleasedEvents(sf::Event& event);
    // void handleTextEnteredEvent(sf::Event& event);

    bool mouseDown;
    bool shiftPressed;
    sf::String stringCopied;
};