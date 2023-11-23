#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <utility>

namespace march{

/**
 * Con typename si indica che T é un tipo di dato (es. int, double, ecc). Equivalente a dire <class T>.
 */
template <typename T>
/**
 * Contiene gli elementi per gestire i dati, ma con malloc() i dati 
 * sono sull'heap (memoria allocata dinamicamente)
 */
struct vector {
    size_t c;  // capacità allocata
    T *dati;   // puntatore ai dati (puntatore a un dato di tipo T)
    size_t n;  // numero elementi

    // Costruttore della classe

    // dopo i due punti posso chiamare altri costruttori: in questo caso chiamo quello definito sotto
    vector() : vector(0) {}

    vector(size_t size)
    {
        c = size + 1;
        // Per interpretare un puntatore come un altro
        //dati = reinterpret_cast<int*> (malloc(c * sizeof(int)));

        // dati = new  int; -> per allocare int 
        // delete dati -> per deallocare
        
        dati = new T[c]; // alloco c elementi di tipo T uno a fianco all'altro in memoria: non si controllo più se non é NULL, perché
        // nel caso viene tirata un'eccezione

        n = size;
    };

    // Costruttore di copia
    vector(const vector& other) : vector(other.n){
        for (size_t i = 0; i < n; i++){
            dati[i] = other.dati[i];
        }
    }

    //vector(const vector& other) = delete; -> così non viene generato in automatico il default

    // Costruttore di move  : non alza eccezioni
    vector(vector &&other) noexcept { //rvalue reference
        c = other.c;
        n = other.n;
        dati = other.dati;
        other.dati = nullptr;
    }
    // Distruttore della classe
    ~vector()
    {
        delete[] dati;
    }
    /**
     * Si passa a reference perché T potrebbe essere una classe. Passandolo come copia 
     * si crea un overhead inutile e poco efficiente. Meglio per reference.
     * Lo standard in c++ é passare i parametri come const reference.
     */
    void push_back(const T& val)
    {
        if (n == c)
        {
            c = c * 2;

            // La realloc non richiama il costruttore -> con le classi non va bene
            // int *tmp = reinterpret_cast<int*> (realloc(dati,c * sizeof(int)));

            // La parola chiave auto serve per dire al compilatore di capire automaticamente il tipo:
            // nei template aggiunge un sacco di flessibilità

            // Poco efficiente perché chiamo sempre il costruttore: si risolve con il placement new, ovvero ci sono 
            // due meccanismi separati: uno per allocare la memoria e uno per chiamare il costruttore quando serve.
            auto tmp = new T[c];
            // Ci copiamo i vecchi dati
            for (size_t i = 0; i < n; i++){
                tmp[i] = dati[i];
            }

            // Libero la vecchia memoria
            delete[] dati;

            dati = tmp;
            // Non mi serve più -> lo faccio puntare a NULL
            tmp = nullptr;
        }
        dati[n] = val;
        ++n;
    }

    size_t size() const
    {
        return n;
    }
    // Ritorna un int -> dobbiamo far tornare una reference costante (deve comportarsi come [])
    const T& at(const size_t pos) const
    {
        // Se la condizione non si verifica, in modalità debug si inchioda
        // in release non viene considerato
        assert(pos < n);
        return dati[pos];
    }

    // Ritorna un int -> dobbiamo far tornare una reference costante (deve comportarsi come [])
    T& at(const size_t pos) 
    {
        // Se la condizione non si verifica, in modalità debug si inchioda
        // in release non viene considerato
        assert(pos < n);
        return dati[pos];
    }
    
    // Overload delle funzioni: basta che i parametri differiscano. 
    // In questo caso differisce il tipo di puntatore ala struttura: 
    // Nel primo caso é int, nel secondo caso é const int
    // La prima viene chiamata se il vettore é modificabile, la seconda 
    // se non lo é.
    T& operator [](const size_t pos)
    {

        return dati[pos];
    }

    const T& operator [](const size_t pos) const
    {
        // Se la condizione non si verifica, in modalità debug si inchioda
        // in release non viene considerato
        return dati[pos];
    }

    /**
     * Visto che se passo il vettore per copia, io sto già creando una copia del vettore
     * che voglio assegnare, mi basta scambiare *this con questo. 
     * All'uscita della funzione, cioé alla fine dello scope, viene comunque liberata la 
     * memoria di other, quindi abbiamo già tutto. 
     * Questo si chiama copy and swap idiom -> ci evita di riscrivere tutto ciò che é presente
     * nel costruttore di copia.
     * Other in questo caso viene realizzato tramite il costruttore di move, perché é temporaneo
     * Questo si chiama copy/move and swap idiom.
     */
    vector& operator=(vector other) {
        swap(*this, other);
        return *this;
    }
    //void operator=(const vector& other) = delete; -> stessa cosa del copy contructor

    // Per la funzione di SWAP sarebbe corretto creare un metodo per gestire direttamente gli attributi e 
    // allo stesso tempo sarebbe corretto avere una funzione esterna per farlo (ma non accederi direttamente agli attributi, overhead!)
    // -> soluzione: funzioni amiche
    friend void swap(vector<T>& a, vector<T>& b) {
        // Scambio le capacità utilizzando la funzione dalla libreria standard
        // La parola chiave using significa prendi quella funzione e portala nel namespace che sto usando
        // adesso
        using std::swap;
        // Anche in questo caso c'é ADL. c ed n sono dei size_t, quindi appartengono alla std che ho importato con using.
        swap(a.c, b.c);
        swap(a.n, b.n);
        swap(a.dati, b.dati);
    }
};

}

/**
 * vettore in cui parametro T é int
*/
auto leggiDaFile(const char* filePath) {

    FILE *fi;
    
    fi = fopen(filePath, "r"); 

    march::vector <double> v;

    if (fi == NULL) {
        printf("Error while opening the input file\n");
        return v;
    }
    
    while  (1) {
        double tmp;

        if (fscanf(fi, "%lf", &tmp) != 1) break;
        
        v.push_back(tmp);
    }

    fclose(fi);

    return v;
}

int main(int argc, char** argv) {

    // Nel c++ c'è l'ADL (Argument Dependent Lookup) -> ricerca dipendente degli argomenti
    // Se specifico il namespace per la classe vector, allora per la funzione swap viene cercato anche
    // all'interno del namespace degli argomenti.
    march::vector<char> c1(3), c2(2);

    c1[0] = 0;
    c2[0] = 'x';
    swap(c1, c2);

    // Controllo che gli argomenti passati siano due
    if (argc < 2) {
        printf("Missing arguments!\n");
        return 1;
    }

    FILE *fo;

    // vector v(); // Most vexing parsing -> pensa sia una funzione v che restituisce un vector 

    march::vector<double> v =  leggiDaFile(argv[1]);

    fo = fopen(argv[2], "w"); 

    if (fo == NULL) {
        printf("Error while opening the output file\n");
        return 3; 
    }
    //v.sort();

    // fprintf non é una funzione di c++, quindi non c'é modo per dire alla funzione che 
    // v sia un vettore di T.
    for (size_t j = 0; j < v.size(); j++) {
        fprintf(fo, "%f\n", v[j]);
    }

    fclose(fo);

    return 0;
}

