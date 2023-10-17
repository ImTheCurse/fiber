#pragma once

#include "../Graphics/editorView.hpp"
#include "../TextCursor/TextCursor.hpp"

class EditorView;

class EventHandler {
  public:
    EventHandler(EditorView& editorView, TextCursor& textCursor);

    void handleEvents(sf::RenderWindow& window, sf::Event& event);
    void handleMouseEvents(sf::RenderWindow& window, sf::Event& event);

  private:
    EditorView& _view;
    TextCursor& _cursor;

    // void handleKeyPressedEvents(EditorView& view, sf::Event& event);
    // void handleKeyReleasedEvents(sf::Event& event);
    // void handleTextEnteredEvent(sf::Event& event);

    bool mouseDown;
    bool shiftPressed;
    sf::String stringCopied;
};