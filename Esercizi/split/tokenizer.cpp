#include "tokenizer.h"


std::vector<std::string> tokenizer(const std::string& str, const std::string& delimiter) {

    std::vector<std::string> tokens;
    size_t curr_pos = 0;

    while(1) {
        size_t start = str.find_first_not_of(delimiter, curr_pos);
        
        if (start == std::string::npos ) break;

        size_t end = str.find_first_of(delimiter, start);
        tokens.push_back(str.substr(start, end - start));

        curr_pos = end;
    }  
    

    return tokens;
}

  
Tokenizer::Tokenizer(const std::string& str, const std::string& delimiter) {

    this->string = str;
    this->delimiter = delimiter;
    this->index = 0;
}

bool Tokenizer::HasNext() {

    size_t nextIdx = this->string.find_first_not_of(this->delimiter, this->index);

    return (nextIdx != std::string::npos);
}
    
std::string Tokenizer::Next() {
    
    size_t nextIdx = this->string.find_first_not_of(this->delimiter, this->index);
        
    if (nextIdx == std::string::npos) return std::string();

    this->index = this->string.find_first_of(this->delimiter, nextIdx);

    return this->string.substr(nextIdx, this->index - nextIdx);
}