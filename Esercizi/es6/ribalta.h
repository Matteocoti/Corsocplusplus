#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>

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



/**
 * Una funzione di hash é una funzione non invertibile. 
 * Nel caso delle hash map si ottiene una peculiarità, 
 * ovvero che due funzioni vicini nello stato 
 * di partenza sono lontani nell'output. 
 * Un unordered set é una hash map. Due valori possono generare 
 * lo stesso hash, questo porta ad avere una lista. 
 * Un valore produce sempre un hash deterministico. 
 * Il set mi dà un ordinamento numerico, mentre l'hash map tiene 
 * l'ordine dell'input. Il costo della ricerca é molto basso (O(1)).
 * 
*/
template <typename T> 
std::vector<T> nodupHash(const std::vector<T>& a) {
    
    std::unordered_set<T> b(a.begin(), a.end());

    return std::vector(b.begin(), b.end());
}



template <typename T> 
std::vector<T> nodup2(const std::vector<T> &a) {
    
    std::set b(a.begin(), a.end());

    return std::vector(b.begin(), b.end());
}

template <typename T> 
std::vector<T> nodupSort(std::vector<T> a) {

    size_t count = a.size();

    std::vector<T> b(count);
    
    std::sort(a.begin(), a.end());

    b[0] = a[0];

    for (int i = 1, j = 0; i < count; ++i) {
        if (a[i] != a[i-1]) {
            b[++j] = a[i];
        }
    }

    return b;
}


