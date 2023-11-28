#include "translate.h"
#include <iostream>
void Translate(std::string& s, const std::string& from_lst, const std::string& to_lst) {

    if (from_lst.size() != to_lst.size()) return;
    size_t size = s.size();
    for (int i = 0; i < size; i++) {
        size_t idx = from_lst.find(s[i]);
        if (idx == std::string::npos) continue;
        else s[i] = to_lst[idx];
    }
}