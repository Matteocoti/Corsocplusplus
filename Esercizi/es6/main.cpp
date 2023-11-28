#include "mv.h"
#include <iostream>
#include "ribalta.h"
#include <list>

int main() {

    using namespace std;

    vector<int> v_in = {4, 1, 1, 4, 7, 9, 7}, v_out;

    nodup(v_in, v_out);
    
    cout << "From vector to vector: " << endl;
    for (const auto &x:v_out) {
        cout << x << endl;
    }
    cout << "From vector to set: " << endl;

    for (const auto &x:nodup2(v_in)) {
        cout << x << endl;
    }
    return 0;
}