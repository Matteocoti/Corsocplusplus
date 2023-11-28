#include <iostream>

struct rational
{
    int num, den;

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

    rational operator + (const rational &b) const
    {
        // Porto a e b allo stesso denominatore
        // Calcolo il minimo comune multiplo (prodotto dei numeri diviso MCD)
        int mcm = this->den / gcd(this->den, b.den) * b.den;
        // Porto a al denominatore mcm
        // Porto b al denominatore mcm
        // Sommo i numeratori
        int s = this->num * mcm / this->den + b.num * mcm / b.den;
        // Riduco ai minimi termini
        // divido numeratore e denominatore per il loro MCD
        int mcd = gcd(abs(s), mcm);

        return rational{s / mcd, mcm / mcd};
    }

    rational& operator + (const rational &b) 
    {
        // Porto a e b allo stesso denominatore
        // Calcolo il minimo comune multiplo (prodotto dei numeri diviso MCD)
        int mcm = this->den / gcd(this->den, b.den) * b.den;
        // Porto a al denominatore mcm
        // Porto b al denominatore mcm
        // Sommo i numeratori
        int s = this->num * mcm / this->den + b.num * mcm / b.den;
        // Riduco ai minimi termini
        // divido numeratore e denominatore per il loro MCD
        int mcd = gcd(abs(s), mcm);

        this->num = s/mcd;
        this->den = mcm/mcd;
        return *this;
    }
};

int main()
{

    using namespace std;

    rational d = {1, 10};
    rational q = {2, 10};
    rational x = d + q;
    
    if (x == rational{3,10}) {
        cout << "uguale\n";
    }
    else {
        cout << "diverso\n";
    }

    return 0;
}