#include "mv.h"
#include <iostream>
#include "ribalta.h"

int main() {

    using namespace std;

    vector<int> v = {1, 2, 5, 7, 45};

    Ribalta(v);

    for (const auto &x:v) {
        cout << x << endl;
    }
    
    return 0;
}