#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <set> 

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
    // Controllo se é presente uno spazio vuoto
    if ((tmp != '/') || is.eof()) {
        is.unget();
        r = rational(num);
        return is;
    }
    
    if (!(is >> den)) return is;

    r = rational(num, den);
    return is;
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

    copy(begin(v), end(v), ostream_iterator<rational>(std::cout, ","));

    std::ifstream is("rationals.txt");

    if (!is)
        return 1;

    std::vector<rational> f;

    while (1) {
        rational r;
        is >> r;
        if (!is) break;

        f.push_back(r);
        
    }
    std::cout << endl << endl;
    std::set<rational> s(begin(f), end(f));
    copy(begin(s), end(s), ostream_iterator<rational>(std::cout, ","));
    std::cout << endl;

    return 0;
}