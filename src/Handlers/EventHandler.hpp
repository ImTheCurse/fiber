#pragma once

#include "../Events/Selection.hpp"
#include "../Graphics/editorView.hpp"
#include "../TextCursor/TextCursor.hpp"

class EditorView;

class EventHandler {
  public:
    EventHandler(EditorView& editorView, TextCursor& textCursor, Selection& select);

    void handleEvents(sf::RenderWindow& window, sf::Event& event);
    void handleKeyPressedEvents(sf::Event event);
    Selection& getSelection() const;

  private:
    EditorView& _view;
    TextCursor& _cursor;
    Selection& _select;

    std::string _buffer;

    sf::Vector2f _currentWorldCord;
    std::pair<int, int> _currentCharLine;

    std::pair<int, int> mapPixelsToLineChar(int x, int y);
    void handleMouseEvents(sf::RenderWindow& window, sf::Event& event);
    void handleTextEnteredEvent(sf::Event& event);
    void pasteContent();
    bool isCursorPosValid(int line);
    // void handleKeyReleasedEvents(sf::Event& event);

    sf::Event::EventType _lastEvent;
    bool wasFileSaved = false;
    bool _isMousePressed;
    bool _shiftPressed;
    int _lastKeyPressed;
    char _lastKey;
    bool _wasLastKeyReleased;
    sf::String _stringCopied;
};