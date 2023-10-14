#pragma once
#include "../Events/editorEvents.hpp"
#include "../textDocument/doc.hpp"
#include <SFML/Graphics.hpp>

class EditorView
{
public:
  EditorView(sf::RenderWindow& window, EditorEvents& events, TextDoc& doc);
  void drawWindow(sf::RenderWindow& window);

  void scrollUp();
  void scrollDown();
  void scrollLeft();
  void scrollRight();
  void scrollTo(float x, float y);

  // getters
  int getWindowWidth();
  int getWindowLength();

  sf::View getCameraView();

  // setters
  void setCamera(int width, int height);
  void setFontSize(int size);

private:
  sf::RenderWindow& _window;
  TextDoc& _doc;
  EditorEvents& _events;
  sf::View _camera;

  void _drawStrings(TextDoc& doc);
  void _drawCursor(sf::RenderWindow& window);

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
};
