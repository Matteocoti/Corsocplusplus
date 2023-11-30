#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <unordered_set> 
#include <map>

class rational
{
    int num_, den_;

public:
    // Funzione collegata alla classe -> ma non appartenente alla classe. Vengono dette funzioni di classe.
    static int gcd(int m, int n)
    {

        while (n != 0)
        {
            int tmp = m % n;
            m = n;
            n = tmp;
        }

        return m;
    }

    rational(int num = 0, int den = 1)
    {
        assert(den != 0);
        if (den < 0)
        {
            num = -num;
            den = -den;
        }

        int MCD = gcd(num, den);

        this->num_ = num / MCD;
        this->den_ = den / MCD;
    }

    rational& operator+=(const rational &b) 
    {
        // Porto a e b allo stesso denominatore
        // Calcolo il minimo comune multiplo (prodotto dei numeri diviso MCD)
        int mcm = this->den_ / gcd(this->den_, b.den_) * b.den_;
        // Porto a al denominatore mcm
        // Porto b al denominatore mcm
        // Sommo i numeratori
        int s = this->num_ * mcm / this->den_ + b.num_ * mcm / b.den_;
        // Riduco ai minimi termini
        // divido numeratore e denominatore per il loro MCD
        int mcd = gcd(abs(s), mcm);

        this->num_ = s / mcd;
        this->den_ = mcm / mcd;
        return *this;
    }
    // friends defined inside class body are inline and are hidden from non-ADL lookup
    // passing lhs by value helps optimize chained a+b+c
    // otherwise, both parameters may be const references
    friend rational operator+(rational lhs, const rational& rhs) 
    {
        lhs += rhs; // reuse compound assignment
        return lhs; // return the result by value (uses move constructor)
    }

    friend bool operator==(const rational &lhs, const rational &rhs) 
    {
        return lhs.num_ == rhs.num_ && lhs.den_ == rhs.den_;
    }

    // La prassi é definire gli operatori di confronto come funzioni free-standing non come 
    // metodi.
    friend bool operator<(const rational &lhs, const rational &rhs)
    {
        int mcm = lhs.den_ / gcd(lhs.den_, rhs.den_) * rhs.den_;

        return (lhs.num_ * (mcm / lhs.den_)) < (rhs.num_ * (mcm / rhs.den_));
    }

    friend inline bool operator> (const rational& lhs, const rational& rhs) { return rhs < lhs; }
    friend inline bool operator<=(const rational& lhs, const rational& rhs) { return !(lhs > rhs); }
    friend inline bool operator>=(const rational& lhs, const rational& rhs) { return !(lhs < rhs); }
    friend inline bool operator!=(const rational& lhs, const rational& rhs) { return !(lhs == rhs); }
    friend std::ostream &operator<<(std::ostream &os, const rational &r);
    friend std::istream& operator>>(std::istream &is, rational& r);

    size_t GetHash() const {
        std::hash<int>hash_obj;
        auto num_hash = hash_obj(num_);
        auto den_hash = hash_obj(den_);
        return num_hash + den_hash;
    };

    // struct hash{
    //     size_t operator()(const rational& r) const {
    //         std::hash<int>hash_obj;
    //         auto num_hash = hash_obj(r.num_);
    //         auto den_hash = hash_obj(r.den_);
    //         return num_hash + den_hash;
    //     }
    // };

};
// In C gli operatori sono metodi del primo oggetto, ma se non sono presenti, possono essere una funzione esterna.
// In questo caso, se volessimo scrivere su uno stream un tipo razionale dobbiamo scrivere una funzione esterna
std::ostream &operator<<(std::ostream &os, const rational &r)
{
    if (r.den_ == 1) os << r.num_;
    else os << r.num_ << "/" << r.den_;
    return os;
}

std::istream& operator>>(std::istream &is, rational& r) 
{
    char tmp;
    int num, den;
    if (!(is >> num)) return is;

    // is >> tmp;
    
    // if (tmp != '/') {
    //     is.setstate(std::ios_base::iostate::_S_failbit);
    //     return is;
    // }
    if (is.eof()) {
        r = rational(num);
        return is;
    }

    is >> tmp;

    if (is.eof()) {
        is.clear();

        r = rational(num);
        return is; 
    }

    // Controllo se é presente uno spazio vuoto
    if ((tmp != '/')){
        is.unget();

        r = rational(num);
        return is;
    }
    
    if (!(is >> den)) return is;

    r = rational(num, den);
    return is;
}

namespace std {
    template<>
    struct hash<rational> {
        size_t operator() (const rational& r) const {
            return r.GetHash();
        }
    };
}

int main()
{

    using namespace std;

    rational d = 5;
    rational q = -3;
    rational x = d + q;

    // 7 viene riconosciuto come un rational con 7 come numeratore (viene chiamato il costruttore rational(7))
    rational z = x + 7;

    vector<rational> v ={ 1, rational(1,2), rational(-3,4)};
    sort(begin(v), end(v));

    // Greater é un function object -> una classe che esegue il compito di una funzione
    sort(begin(v), end(v), greater<rational>());


    std::ifstream is("rationals.txt");

    if (!is)
        return 1;

    std::vector<rational> f;
    rational r;
    while (is >> r) f.push_back(r);

    // é un albero binario con le chiavi come foglie, quindi la complessità della ricerca é
    // logaritmo in base 2 di n (al massimo)
    //std::map<rational, int> rational_count;

    std::unordered_map<rational, int> rational_count;

    std::sort(begin(f), end(f));
    size_t count = 0;
    rational x_old = f[0];
    // copy(begin(s), end(s), ostream_iterator<rational>(std::cout, ","));
    for (const auto& number: f) {
        // if (rational_count.find(number) == rational_count.end()){
        //     rational_count[number] = 1;
        // } else {
        //     rational_count[number]++;
        // }
        // La parte di sopra ho due volte la ricerca, perché l'operatore [] é una ricerca che non 
        // da errori. Inoltre, crea anche. Mentre con il metodo at() ho la gestione degli errori e non crea.

        // Altra soluzione
        // auto it = rational_count.find(number);
        // if (it == rational_count.end()) {
        //     rational_count.insert(*it,1);
        // }
        // else (*it).second++;

        // Se la chiave non é presente, viene costruita con il secondo valore di default della mappa, quindi in 
        // questo caso 0
        rational_count[number]++;
    }

    for (const auto x: rational_count) {
        std::cout << "Il valore " << x.first << " compare " << x.second << " volte" << endl;
    }
    return 0;
}