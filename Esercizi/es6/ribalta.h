#include <vector>
#include <algorithm>
#include <set>

template <typename T>
void Ribalta(T &v) {

    auto it_start = v.begin();
    auto it_stop = v.end();
    --it_stop;
   
    for (size_t count = 0; count < (v.size()/2); count++) {
        std::swap(*it_start, *it_stop);
        it_start++;
        --it_stop;
    }

    return;
}

template <typename T> 
void nodup(const std::vector<T>& a, std::vector<T>& b) {
    
    for (const auto &x : a) {
        if (std::find(b.begin(), b.end(), x) == b.end()) {
            b.push_back(x);
        }
    }

    return;
}


template <typename T> 
std::vector<T> nodup2(const std::vector<T> &a) {
    
    std::set b(a.begin(), a.end());

    return std::vector(b.begin(), b.end());
}

