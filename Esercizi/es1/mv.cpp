#include "mv.h"


double Mean(const std::vector<int> &v) {
    using std::iterator;

    if (v.empty()) return 0.0;

    double mean = 0.0;

    for (auto it : v) {
        mean += it;
    }

    return mean/v.size();
}


double Variance(const std::vector<int> &v){

    if (v.empty()) return 0.0;

    double mean = Mean(v), var = 0.0;
    for (auto it : v) {
        var +=  (it - mean)*(it - mean);
    }

    return var/v.size();
}