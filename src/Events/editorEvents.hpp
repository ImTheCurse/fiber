#pragma once

#include <SFML/Graphics.hpp>

#include "../TextCursor/TextCursor.hpp"
#include "../textDocument/doc.hpp"

class EditorEvents {
  public:
    EditorEvents(TextDoc& doc, TextCursor cursor)
        : _doc(doc), _cursor(cursor){};  // TODO add selection to constructor

    bool mouseWheelEvent(sf::Event);

  private:
    TextDoc& _doc;
    TextCursor _cursor;
    // Selection _sel;
};