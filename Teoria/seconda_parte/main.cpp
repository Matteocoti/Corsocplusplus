#include <iostream>
#include <cassert>
#include <vector>

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

    rational operator+(const rational &b) const
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

        return rational{s / mcd, mcm / mcd};
    }

    rational &operator+(const rational &b)
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

    bool operator==(const rational &b) const
    {
        return this->num_ == b.num_ && this->den_ == b.den_;
    }

    friend std::ostream &operator<<(std::ostream &os, const rational &r); 
};
// In C gli operatori sono metodi del primo oggetto, ma se non sono presenti, possono essere una funzione esterna.
// In questo caso, se volessimo scrivere su uno stream un tipo razionale dobbiamo scrivere una funzione esterna
std::ostream &operator<<(std::ostream &os, const rational &r)
{
    os << r.num_ << "/" << r.den_;
    return os;
}

int main()
{

    using namespace std;

    rational d = 5;
    rational q = -3;
    rational x = d + q;

    // 7 viene riconosciuto come un rational con 7 come numeratore (viene chiamato il costruttore rational(7))
    rational z = x + 7;
    std::cout << x << endl;

    std::vector<rational> v;
    v.push_back(d);

    if (x == rational{3, 10})
    {
        cout << "uguale\n";
    }
    else
    {
        cout << "diverso\n";
    }

    return 0;
}