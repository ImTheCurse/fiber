#include "util.hpp"

int calculateEndLine(int startLine, std::string str) {
    int count = startLine;
    for (auto itr : str) {
        if (itr == '\n')
            count++;
    }
    return count;
}

int calculateEndChar(int startLine, int startChar, std::string str) {
    int charCount = startChar;
    for (auto itr : str) {
        if (itr == '\n') {
            charCount = 0;
            continue;
        }
        charCount++;
    }
    return charCount;
}
