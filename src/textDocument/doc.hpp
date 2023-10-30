#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "../Events/Selection.hpp"
class Selection;
class TextDoc {
  public:
    TextDoc(const std::string &filename);
    ~TextDoc(){};
    bool saveFile();
    bool hasFileChanged() const;

    std::string getLine(int lineNum) const;
    char getCharAt(int lineIndex, int charIndex) const;
    int getLineCount() const;
    int getCharInLineAmount(int lineNum) const;
    size_t getCharIndex(int lineNum, int charIndex);
    // crud operations
    void addTextToLine(int lineNum, int charIndex, std::string text);
    void addTextToLine(int lineNum, int charIndex, char c);
    void deleteTextFromLine(int lineNum, int charIndex, int lengthToDelete);
    void deleteSelectionText(Selection &sel);

  private:
    std::string _buffer;  // using sf::string for ease of conversion between
                          // formats
    std::string _filename;
    bool _isChanged;
    size_t getNthOccurrenceIdx(int lineCount);
};