#include <SFML/Graphics.hpp>
#include <iostream>

#include "../../src/Events/Selection.hpp"
#include "../../src/Events/editorEvents.hpp"
#include "../../src/Graphics/editorView.hpp"
#include "../../src/textDocument/doc.hpp"

#define FRAME_RATE_LIMIT 60

int main() {
    TextDoc doc("test.txt");
    TextCursor textCursor(doc);
    sf::Color backgroundColor = sf::Color(21, 29, 45);
    sf::RenderWindow window(sf::VideoMode(800, 600), "Fiber");
    window.setVerticalSyncEnabled(true);

    EditorEvents event(doc, textCursor);
    EditorView editorView(window, event, doc);
    Selection select(window, doc, editorView.getFontSize(), editorView.getCharWidth());
    EventHandler handler(editorView, textCursor, select);
    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last
        // iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (event.type == sf::Event::Resized) {
            editorView.setCamera(event.size.width, event.size.height);
        }

        // clear the window with black color
        window.clear(backgroundColor);
        handler.handleMouseEvents(window, event);
        editorView.drawTextCursor(textCursor);
        editorView.drawWindow(window);
        // end the current frame
        window.display();
    }

    return 0;
}