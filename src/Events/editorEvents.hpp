#pragma once

#include <SFML/Graphics.hpp>
#include "../textDocument/doc.hpp"


class EditorEvents{
    public:
    EditorEvents(TextDoc &doc) : _doc(doc){};//TODO add cursor and selection to constructor

    private:

    TextDoc &_doc;
    //Cursor _cursor;
    //Selection _sel;


};