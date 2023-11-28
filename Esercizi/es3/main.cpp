#include "mv.h"
#include <iostream>
#include <list>
#include <set>

int main() {

    using namespace std;

    set<char> v = {1, 2, 5, 7, 45};

    double mean = Mean(v);

    cout << "Media: " << mean << endl;

    double var = Variance(v);
    
    cout << "Varianza: " << var << endl;
    
    return 0;
}