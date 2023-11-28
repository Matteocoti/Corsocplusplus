#include "mv.h"

int main() {

    std::vector<double> v = {1, 2, 5, 7, 45};

    double mean = Mean<double>(v);

    double var = Variance<double>(v);

    return 0;
}