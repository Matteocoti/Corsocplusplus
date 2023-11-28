#ifndef __MV_H__
#define __MV_H__

#include <vector>

template <typename T>
double Mean(const T &v) {

    if (v.empty()) return 0.0;

    double mean = 0.0;
    const auto it_stop = v.end();
    for (const auto &it =  v.begin(); it != it_stop; ++it) {
        mean += static_cast<double>(it);
    }

    return mean/v.size();
}

template <typename T>
double Variance(const T &v){

    if (v.empty()) return 0.0;

    double mean = Mean(v), var = 0.0;

    const auto it_stop = v.end();
    for (const auto &it =  v.begin(); it != it_stop; ++it) {
        var +=  (static_cast<double>(it) - mean)*(static_cast<double>(it) - mean);
    }

    return  var/v.size();
}
#endif