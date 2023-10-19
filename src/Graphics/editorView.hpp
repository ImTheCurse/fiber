#pragma once
#include <SFML/Graphics.hpp>

#include "../Events/editorEvents.hpp"
#include "../Handlers/EventHandler.hpp"
#include "../textDocument/doc.hpp"

class EditorView {
  public:
    EditorView(sf::RenderWindow& window, EditorEvents& events, TextDoc& doc);
    void drawWindow(sf::RenderWindow& window);

    void scrollUp();
    void scrollDown();
    void scrollLeft();
    void scrollRight();
    void scrollTo(float x, float y);

    // getters
    TextDoc& getDoc();
    int getWindowWidth();
    int getWindowLength();
    int getFontSize();
    int getCharWidth();
    sf::RenderWindow& getWindow() { return _window; }

    sf::View getCameraView();

    // setters
    void setCamera(int width, int height);
    void setFontSize(int size);
    void setViewToCamera();
    void drawTextCursor(TextCursor textCursor);

  private:
    sf::RenderWindow& _window;
    TextDoc& _doc;
    EditorEvents& _events;
    sf::View _camera;

    void _drawStrings(TextDoc& doc);

    sf::Font _font;
    int _fontSize;

    int _windowWidth;
    int _windowLength;

    float _deltaScroll;
    float _deltaZoomIn;
    float _deltaZoomOut;

    int _marginOffset_x;

    sf::Color _colorMargin;
    sf::Color _charColor;

    float _bottomPixelLimit;
    float _rightPixelLimit;

    int _lineHeight;  // is used to increase bottom and upper limit so scroll will
    int _charWidth;   // work.
};
