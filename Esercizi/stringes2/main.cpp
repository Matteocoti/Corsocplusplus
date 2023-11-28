#include "translate.h"
#include <iostream>


int main() {

    using namespace std;

    string input = "ciao";

    Translate(input, "abdc", "wxzy");

    cout << input << endl;

    return 0;
}