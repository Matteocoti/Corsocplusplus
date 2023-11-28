#include "mv.h"
#include <iostream>
#include "ribalta.h"
#include <list>

int main() {

    using namespace std;

    list<int> v = {1, 2, 5, 7, 45};

    Ribalta(v);

    for (const auto &x:v) {
        cout << x << endl;
    }
    
    return 0;
}