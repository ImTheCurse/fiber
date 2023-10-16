#include "editorView.hpp"
#include "../TextCursor/TextCursor.hpp"
#include <iostream>

EditorView::EditorView(sf::RenderWindow& window,
                       EditorEvents& events,
                       TextDoc& doc)
  :

  _camera(sf::FloatRect(-50, 0, window.getSize().x, window.getSize().y))
  , _deltaScroll(20)
  , _deltaZoomIn(0.8f)
  , _deltaZoomOut(1.2f)
  , _events(events)
  , _doc(doc)
  , _window(window)
{
  _font.loadFromFile("../../fonts/JetBrainsMono-Regular.ttf");
  setFontSize(18);
  _marginOffset_x = 40;
  _colorMargin = sf::Color(32, 44, 68);
  _charColor = sf::Color::White;

  _windowLength = _window.getSize().x;
  _windowWidth = _window.getSize().y;
}

void
EditorView::drawWindow(sf::RenderWindow& window)
{
  // drawing the text itself.
  _drawStrings(_doc);

  // creating the line counter text on the sidebar
  for (int lineNum = 1; lineNum < _doc.getLineCount() + 1; lineNum++) {
    int lineHeight = 1;
    int blockHeight = lineHeight * _fontSize;

    sf::Text lineNumberText;
    lineNumberText.setFillColor(sf::Color::White);
    lineNumberText.setFont(_font);
    lineNumberText.setString(std::to_string(lineNum));
    lineNumberText.setCharacterSize(_fontSize - 1);
    lineNumberText.setPosition(0, blockHeight * (lineNum - 1));

    // creating rectangle behind text to constast.
    sf::RectangleShape marginRect(sf::Vector2f(_marginOffset_x, blockHeight));
    marginRect.setFillColor(_colorMargin);
    marginRect.setPosition(_marginOffset_x - 40, blockHeight * (lineNum - 1));

    // draw rectangle and text
    _window.draw(marginRect);
    _window.draw(lineNumberText);
  }
}

void
EditorView::scrollUp()
{
  float height = _window.getView().getSize().y;
  auto currentCamPos = _camera.getCenter();

  // if i'm not in the first half of the view
  // greater than and -delta because the y val go up when we go down
  if (currentCamPos.y > height / 2) {
    _camera.move(0, -_deltaScroll);
  }
}

void
EditorView::scrollDown()
{
  float height = _window.getView().getSize().y;
  auto currentCamPos = _camera.getCenter();
  float bottomLimit = std::max(_bottomPixelLimit, height);

  if (currentCamPos.y < (height / 2) - bottomLimit + 20) {
    _camera.move(0, _deltaScroll);
  }
}

void
EditorView::scrollLeft()
{
  float width = _window.getView().getSize().x;
  auto currentCamPos = _camera.getCenter();

  if (currentCamPos.x - width / 2 > -_marginOffset_x) {
    _camera.move(-_deltaScroll, 0);
  }
}

void
EditorView::scrollRight()
{
  float width = _window.getView().getSize().x;
  float rightLimit = std::max(_rightPixelLimit, width);
  auto camPos = _camera.getCenter();
  // Numero magico 20 como un plus
  if (camPos.x + width / 2 < rightLimit + 20) {
    _camera.move(_deltaScroll, 0);
  }
}

void
EditorView::scrollTo(float x, float y)
{
  if (x < _rightPixelLimit && y < _bottomPixelLimit) {
    _camera.move(x, y);
  }
}

int
EditorView::getWindowWidth()
{
  return _windowWidth;
}

int
EditorView::getWindowLength()
{
  return _windowLength;
}

sf::View
EditorView::getCameraView()
{
  return _camera;
}

void
EditorView::setCamera(int width, int height)
{
  _camera = sf::View(sf::FloatRect(-50, 0, width, height));
}

void
EditorView::setFontSize(int size)
{
  _fontSize = size;
  _lineHeight = _fontSize;

  // This a trick to find char width, only works because we are using monospace
  // font(we get the char width of a wide character)

  sf::Text tmpText;
  tmpText.setFont(_font);
  tmpText.setCharacterSize(_fontSize);
  tmpText.setString("_");
  float textwidth = tmpText.getLocalBounds().width;
  _charWidth = textwidth;
}

void
EditorView::_drawStrings(TextDoc& doc)
{
  sf::Text newString;
  sf::Color color;
  sf::Vector2f cord;

  int numOfLines = doc.getLineCount();
  // initial text start offset.
  cord.x = 100;
  cord.y = 0;

  for (int i = 0; i < numOfLines; i++) {
    newString.setString(doc.getLine(i + 1));
    newString.setFillColor(color.White);
    newString.setOutlineColor(color.White);
    newString.setPosition(cord);
    newString.setFont(_font);
    newString.setCharacterSize(_fontSize);
    cord.y += _fontSize;

    if (_window.isOpen()) {
      _window.draw(newString);
    } else {
      throw "Window is closed, unable to output text.";
    }
  }
}

void
EditorView::_drawTextCursor(sf::RenderWindow& window, TextCursor textCursor)
{
  int curr_x_pos = textCursor.getCurrentPos().first * _charWidth;
  //(textCursor.getCurrentPos().second * _fontSize) is the offset for spacing
  // between lines.
  int curr_y_pos = textCursor.getCurrentPos().second * _lineHeight +
                   (textCursor.getCurrentPos().second * _fontSize);
  int cursorDrawWidth = 2;

  sf::Vector2f rec(cursorDrawWidth, _lineHeight);
  sf::RectangleShape cursorShape(rec);
  cursorShape.setPosition(curr_x_pos, curr_y_pos);
  cursorShape.setFillColor(sf::Color::White);
  window.draw(cursorShape);
}
