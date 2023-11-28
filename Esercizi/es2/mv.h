#ifndef __MV_H__
#define __MV_H__

#include <vector>

template <typename T>
double Mean(const std::vector<T> &v) {

    if (v.empty()) return 0.0;

    double mean = 0.0;
    for (const auto &it : v) {
        mean += static_cast<double>(it);
    }

    return mean/v.size();
}

template <typename T>
double Variance(const std::vector<T> &v){

    if (v.empty()) return 0.0;

    double mean = Mean(v), var = 0.0;

    for (const auto &it : v) {
        var +=  (static_cast<double>(it) - mean)*(static_cast<double>(it) - mean);
    }

    return  var/v.size();
}
#endif