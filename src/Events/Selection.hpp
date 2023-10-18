#include <SFML/Graphics.hpp>
#include <string>

#include "../textDocument/doc.hpp"

class Selection {
  public:
    Selection(sf::RenderWindow &window, TextDoc &doc, int fontSize, int charWidth);
    void createSelection(int startLine, int startCharIndex, int endLine, int endCharIndex);
    void updateSelection(int startLine, int startCharIndex, int endLine, int endCharIndex);
    void removeSelection();

  private:
    sf::RenderWindow &_window;
    TextDoc &_doc;

    int _startLine;
    int _startCharIndex;
    int _endLine;
    int _endCharIndex;

    int _charWidth;
    int _fontSize;

    std::string _selectionData;
    bool _isSelectionExist;

    void saveSelectionData();
    int findLineAndCharIndex();
};