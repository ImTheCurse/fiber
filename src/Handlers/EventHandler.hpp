#pragma once
#include <list>

#include "../Events/Selection.hpp"
#include "../Graphics/editorView.hpp"
#include "../TextCursor/TextCursor.hpp"

class EditorView;

enum class ActionType { ADDED, REMOVED };

// if endLine and endChar could be -1, if an action is needed to be added back.
struct Action {
    ActionType actionType;
    int startLine;
    int startChar;
    int endLine;
    int endChar;
    std::string str;
};

// used as a class to store last actions, for ctrl-z functionality.
class ActionList {
  public:
    ActionList() {}
    void addToActionList(ActionType actionName, const int startLine, const int startChar,
                         const int endLine, const int endChar, std::string str);
    Action popLastAction();

  private:
    ActionType _actionType;
    std::list<Action> _lastActions;
};

class EventHandler : public ActionList {
  public:
    EventHandler(EditorView& editorView, TextCursor& textCursor, Selection& select);

    void handleEvents(sf::RenderWindow& window, sf::Event& event);
    void handleKeyPressedEvents(sf::Event event);
    Selection& getSelection() const;

  private:
    EditorView& _view;
    TextCursor& _cursor;
    Selection& _select;
    ActionList _actionList;

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