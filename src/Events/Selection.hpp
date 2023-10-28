#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "../textDocument/doc.hpp"
class TextDoc;
class Selection {
  public:
    Selection(sf::RenderWindow &window, TextDoc &doc, int fontSize, int charWidth);
    void createSelection(int startLine, int startCharIndex, int endLine, int endCharIndex);
    void removeSelection();

    sf::RectangleShape getSelectedShape() const;
    std::vector<sf::RectangleShape> getSelections() const;
    bool isSelection() const;
    std::string getSelectionData() const;
    std::pair<int, int> getStartCharLine() const;
    std::pair<int, int> getEndCharLine() const;

  private:
    std::vector<sf::RectangleShape> _selections;
    sf::RenderWindow &_window;
    TextDoc &_doc;

    int _startLine;
    int _startCharIndex;
    int _endLine;
    int _endCharIndex;

    int _charWidth;
    int _fontSize;
    bool _isSelectionExist;

    std::string _selectionData;
    sf::RectangleShape _selShape;
    void saveDataToSelectionBuffer(int startLine, int startCharIndex, int endLine,
                                   int endCharIndex);
};