#include "doc.hpp"

#include <string.h>

#include <cctype>
#include <fstream>
#include <iostream>
#include <vector>

TextDoc::TextDoc(const std::string &filename) : _filename(filename) {
    std::ifstream file;

    file.open(filename, std::ios::in);
    if (!file) {
        std::cerr << "Can't open file" << std::endl;
        return;
    }
    std::cout << "File opend successfuly!" << std::endl;

    if (file.is_open()) {
        char myChar;
        while (file) {
            myChar = file.get();
            _buffer += myChar;
        }
    }

    file.close();
}

bool TextDoc::saveFile() {
    std::ofstream fileToWrite;

    fileToWrite.open(_filename);
    if (!fileToWrite) {
        std::cerr << "Error opening file" << std::endl;
        return false;
    }

    // writing to file
    // TODO debug why there is an output of strange symbol at the end.
    fileToWrite << _buffer;

    fileToWrite.close();
    _isChanged = false;
    return true;
}

bool TextDoc::hasFileChanged() const { return _isChanged; }

std::string TextDoc::getLine(int lineNum) const {
    if (lineNum <= 0) {
        std::cerr << "Line number invalid." << std::endl;
        return "";
    }

    std::string newString;
    for (auto itr : _buffer) {
        if (lineNum == 1) {
            newString += itr;
        }
        if (itr == '\n') {
            lineNum--;
        }

        if (lineNum == 0) {
            break;
        }
    }

    return newString;
}

char TextDoc::getCharAt(int lineNum, int charIndex) const {
    if (charIndex > getLine(lineNum).size() - 1) {
        std::cerr << "Invalid character index." << std::endl;
        return ' ';
    }

    return getLine(lineNum)[charIndex];
}

int TextDoc::getCharInLineAmount(int lineNum) const {
    std::string str = getLine(lineNum);
    int count = 0;

    for (int i = 0; i < str.size(); i++) {
        if (std::isspace(str[i]))
            continue;

        count++;
    }
    return count;
}

int TextDoc::getLineCount() const {
    int count = 1;
    for (auto itr : _buffer) {
        if (itr == '\n')
            count++;
    }
    return count;
}

void TextDoc::addTextToLine(int lineNum, int charIndex, std::string text) {
    int idx = getCharIndex(lineNum, charIndex);

    _buffer.insert(idx, text);
    _isChanged = true;
}

size_t TextDoc::getCharIndex(int lineNum, int charIndex) {
    size_t idx = 0;
    idx += getNthOccurrenceIdx(lineNum - 1);
    idx += charIndex;

    return idx;
}

void TextDoc::deleteTextFromLine(int lineNum, int charIndex, int lengthToDelete) {
    int idx = getCharIndex(lineNum, charIndex);

    _buffer.erase(idx, lengthToDelete);
    _isChanged = true;
}

size_t TextDoc::getNthOccurrenceIdx(int lineCount) {
    size_t idx = 0;
    while (lineCount > 0 && idx < _buffer.length()) {
        if (_buffer.at(idx) == '\n') {
            lineCount--;
        }
        idx++;
    }
    return idx;
}
