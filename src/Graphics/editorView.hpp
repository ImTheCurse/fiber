#pragma once
#include <SFML/Graphics.hpp>
#include "../textDocument/doc.hpp"
#include "../Events/editorEvents.hpp"


class EditorView {
    public:
    
    EditorView(const sf::RenderWindow &window,EditorEvents &events);
    void drawWindow(sf::RenderWindow &window);

    void scrollUp();
    void scrollDown();
    void scrollLeft();
    void scrollRight();
    void scrollTo(float x, float y);
    
    //getters
    int getWindowWidth();
    int getWindowLength();

    sf::View getCameraView();
    
    //setters
    void setCamera(int width, int height);
    void setFontSize(int size);
    

    private:
        EditorEvents &_events;
        sf::View _camera;
        void _drawStrings(TextDoc &doc);
        void _drawCursor(sf::RenderWindow &window);

        sf::Font _font;
        int _fontSize;

        int _windowWidth;
        int _windowLength;

        float _deltaScroll;
        float _deltaZoomIn;
        float _deltaZoomOut;




};
