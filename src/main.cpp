#include <iostream>
#include "../../src/textDocument/doc.hpp"
#include <SFML/Graphics.hpp>

int main()
{
    TextDoc doc("test.txt");
    doc.deleteTextFromLine(1,0,12);
    doc.saveFile();
    


}