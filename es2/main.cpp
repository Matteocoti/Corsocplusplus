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
        dati = reinterpret_cast<int*> (malloc(c * sizeof(int)));
        if (dati == NULL) exit(1); // Solo per prova
        n = 0;
    };

    // Costruttore di copia
    vector(const vector& other) : vector(other.n){
        memcpy(dati, other.dati, n*sizeof(int));
    }

    //vector(const vector& other) = delete; -> così non viene generato in automatico il default

    // Distruttore della classe
    ~vector()
    {
        free(dati);
    }

    void push_back(int val)
    {
        if (n == c)
        {
            c = c * 2;

            int *tmp = reinterpret_cast<int*> (realloc(dati,c * sizeof(int)));
            if (tmp == NULL)
                exit(1);

            dati = tmp;
        }
        dati[n] = val;
        ++n;
    }
    void sort()
    {
        qsort(dati, n, sizeof(int), *cmpint);
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
    void operator=(const vector& other) {
        // Check del self-assignment
        // if (this == &other) {
        //     return;
        // }
        if (other.n > c) {
            free(dati);
            c = other.n + 1;
            dati = reinterpret_cast<int*> (malloc(c * sizeof(int)));
            if (dati == NULL) exit(1);
        } 
        n = other.n;
        memcpy(dati, other.dati, n*sizeof(int));
    }

    //void operator=(const vector& other) = delete; -> stessa cosa del copy contructor
};


struct oggetto {
    int numero;
    vector v{3}; // Se si utilizzano le graffe in una definizione sono un modo per passare i parametri al costruttore

    oggetto() : v(3) {}
};

int main(int argc, char** argv) {

    oggetto a;
    a.numero = 5;
    a.v.push_back(32);
    a.v.push_back(-51);

    // Controllo che gli argomenti passati siano due
    if (argc < 2) {
        printf("Missing arguments!\n");
        return 1;
    }

    FILE *fi, *fo;

    fi = fopen(argv[1], "r"); 

    if (fi == NULL) {
        printf("Error while opening the input file\n");
        return 2;
    }

    // vector v(); // Most vexing parsing -> pensa sia una funzione v che restituisce un vector 

    vector v;

    int tmp;
    while (fscanf(fi, "%d", &tmp) == 1) {
        v.push_back(tmp);
    }

    fclose(fi);

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