#include "editorView.hpp"
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
  setFontSize(12);
  _marginOffset_x = 40;
  _colorMargin = sf::Color(32, 44, 68);
  _charColor = sf::Color::White;
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
}

void
EditorView::scrollDown()
{
}

void
EditorView::scrollLeft()
{
}

void
EditorView::scrollRight()
{
}

void
EditorView::scrollTo(float x, float y)
{
}

int
EditorView::getWindowWidth()
{
  return 0;
}

int
EditorView::getWindowLength()
{
  return 0;
}

sf::View
EditorView::getCameraView()
{
  return sf::View();
}

void
EditorView::setCamera(int width, int height)
{
}

void
EditorView::setFontSize(int size)
{
  _fontSize = size;
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
    cord.y += 10; // TODO change "magic number" to formula so the text will
                  // offset corectly with scaling of font size.

    if (_window.isOpen()) {
      _window.draw(newString);
    } else {
      throw "Window is closed, unable to output text.";
    }
  }
}

void
EditorView::_drawCursor(sf::RenderWindow& window)
{
}
