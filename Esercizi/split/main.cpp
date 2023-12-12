#include "tokenizer.h"
#include <iostream>

int main() {

    using namespace std;

    vector<string> split = tokenizer("Ciao  Mamma! ", " ");

    for (const auto &x:split) {
        cout << x << endl;
    }

    cout << endl << endl;

    Tokenizer tokenizer("Ciao Mamma!");

    while (tokenizer.HasNext()) {
        cout << tokenizer.Next() << endl;
    }

    return 0;
}