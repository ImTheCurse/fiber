#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class TextDoc
{
public:
  TextDoc(const std::string& filename);
  ~TextDoc(){};
  bool saveFile();
  bool hasFileChanged() const;

  std::string getLine(int lineNum) const;
  char getCharAt(int lineIndex, int charIndex) const;
  int getLineCount() const;
  int getCharInLineAmount(int lineNum) const;
  int getCharIndex(int lineNum, int charIndex);
  // crud operations
  void addTextToLine(int lineNum, int charIndex, std::string text);
  void deleteTextFromLine(int lineNum, int charIndex, int lengthToDelete);

private:
  std::string _buffer; // using sf::string for ease of conversion between
                       // formats
  std::string _filename;
  bool _isChanged;
};