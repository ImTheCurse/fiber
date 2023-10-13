#include "editorView.hpp"

EditorView::EditorView(const sf::RenderWindow &window,EditorEvents &events):

_camera(sf::FloatRect(-50,0,window.getSize().x,window.getSize().y)),_deltaScroll(20), _deltaZoomIn(0.8f), _deltaZoomOut(1.2f),_events(events)
{
    _font.loadFromFile("../../fonts/JetBrainsMono-Regular.ttf");
    setFontSize(18);
    
}

void EditorView::drawWindow(sf::RenderWindow &window){
}

void EditorView::scrollUp(){
}

void EditorView::scrollDown(){
}

void EditorView::scrollLeft(){
}

void EditorView::scrollRight(){
}

void EditorView::scrollTo(float x, float y){
}

int EditorView::getWindowWidth(){
    return 0;
}

int EditorView::getWindowLength(){
    return 0;
}

sf::View EditorView::getCameraView(){
    return sf::View();
}

void EditorView::setCamera(int width, int height){
}

void EditorView::setFontSize(int size){
    _fontSize = size;
}
