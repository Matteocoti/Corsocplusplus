#include <vector>
#include <string>


class Tokenizer{

private:
    std::string string, delimiter;
    size_t index;

public:
    Tokenizer(const std::string& str, const std::string& delimiter = " ");

    bool HasNext();
    
    std::string Next();
};

std::vector<std::string> tokenizer(const std::string& str, const std::string& delimiter = " ");