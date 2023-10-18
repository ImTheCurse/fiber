#pragma once

#include "../Events/Selection.hpp"
#include "../Graphics/editorView.hpp"
#include "../TextCursor/TextCursor.hpp"

class EditorView;

class EventHandler {
  public:
    EventHandler(EditorView& editorView, TextCursor& textCursor, Selection& select);

    void handleEvents(sf::RenderWindow& window, sf::Event& event);
    void handleMouseEvents(sf::RenderWindow& window, sf::Event& event);

  private:
    EditorView& _view;
    TextCursor& _cursor;
    Selection& _select;

    std::pair<int, int> mapPixelsToLineChar(int x, int y);
    // void handleKeyPressedEvents(EditorView& view, sf::Event& event);
    // void handleKeyReleasedEvents(sf::Event& event);
    // void handleTextEnteredEvent(sf::Event& event);

    bool _isMousePressed;
    bool _shiftPressed;
    sf::String _stringCopied;
};