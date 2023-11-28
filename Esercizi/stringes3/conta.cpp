#include "conta.h"

int Conta(const std::string& str) {
    int words = 0;
    bool word = false;

    for (const char c: str) {
        if (c == ' ') word = false;
        else if (!word){
            words++;
            word = true;
        }
    }

    return words;
}