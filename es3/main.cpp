#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int cmpint(const void *a, const void *b)
{
    const int *pa = reinterpret_cast<const int *>(a);
    const int *pb = reinterpret_cast<const int *>(b);

    // Se si fa (*pa - *pb) per numeri grandi, il risultato può andare
    // in overflow, quindi restituire il risultato sbagliato
    if (*pa < *pb) return -1;
    else if (*pa == *pb) return 0;
    else return 1;

    // Versione figa 
    //return (*pa > * pb) - (*pa < *pb);
}

/**
 * Contiene gli elementi per gestire i dati, ma con malloc() i dati 
 * sono sull'heap (memoria allocata dinamicamente)
 */
struct vector {
    size_t c;  // capacità allocata
    int *dati; // puntatore ai dati
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
        
        dati = new int[c]; // alloco c int uno a fianco all'altro in memoria: non si controllo più se non é NULL, perché
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

    void push_back(int val)
    {
        if (n == c)
        {
            c = c * 2;

            // La realloc non richiama il costruttore -> con le classi non va bene
            // int *tmp = reinterpret_cast<int*> (realloc(dati,c * sizeof(int)));

            int *tmp = new int[c];
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
    int at(const size_t pos) const
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
    int& operator [](const size_t pos)
    {

        return dati[pos];
    }

    const int& operator [](const size_t pos) const
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
            dati = new int[c];
        } 
        n = other.n;
        for (size_t i = 0; i < n; i++){
            dati[i] = other.dati[i];
        }
        return *this;
    }
    //void operator=(const vector& other) = delete; -> stessa cosa del copy contructor
};



vector leggiDaFile(const char* filePath) {

    FILE *fi;
    
    fi = fopen(filePath, "r"); 

    if (fi == NULL) {
        printf("Error while opening the input file\n");
        return vector();
    }
    vector v;
    while  (1) {
        int tmp;

        if (fscanf(fi, "%d", &tmp) != 1) break;
        
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

    vector v =  leggiDaFile(argv[1]);

    fo = fopen(argv[2], "w"); 

    if (fo == NULL) {
        printf("Error while opening the output file\n");
        return 3; 
    }
    v.sort();

    for (size_t j = 0; j < v.size(); j++) {
        fprintf(fo, "%d\n", v[j]);
    }

    fclose(fo);

    v[1] = 6;
    vector y = v;

    return 0;
}