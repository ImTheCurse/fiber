#pragma once

#include "../TextCursor/TextCursor.hpp"
#include "../textDocument/doc.hpp"
#include <SFML/Graphics.hpp>

class EditorEvents
{
public:
  EditorEvents(TextDoc& doc, TextCursor cursor)
    : _doc(doc)
    , _cursor(cursor){}; // TODO add cursor and selection to constructor

private:
  TextDoc& _doc;
  TextCursor _cursor;
  // Selection _sel;
};