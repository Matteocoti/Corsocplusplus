#include <vector>



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