#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>




/**
 * Con typename si indica che T é un tipo di dato (es. int, double, ecc)
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

            T *tmp = new T[c];
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

    // Operatore di assegnamento
    vector& operator=(vector&& other) {
        delete[] dati; 
        c = other.c;
        n = other.n;
        dati = other.dati;
        other.dati = NULL;
        return *this;
    }

    vector& operator=(const vector& other) {
        // Check del self-assignment
        // if (this == &other) {
        //     return;
        // }
        if (other.n > c) {
            delete[] dati; 
            c = other.n + 1;
            dati = new T[c];
        } 
        n = other.n;
        for (size_t i = 0; i < n; i++){
            dati[i] = other.dati[i];
        }
        return *this;
    }
    //void operator=(const vector& other) = delete; -> stessa cosa del copy contructor
};


/**
 * vettore in cui parametro T é int
*/
vector<double> leggiDaFile(const char* filePath) {

    FILE *fi;
    
    fi = fopen(filePath, "r"); 

    vector <double> v;

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

    // Controllo che gli argomenti passati siano due
    if (argc < 2) {
        printf("Missing arguments!\n");
        return 1;
    }

    FILE *fo;

    // vector v(); // Most vexing parsing -> pensa sia una funzione v che restituisce un vector 

    vector<double> v =  leggiDaFile(argv[1]);

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