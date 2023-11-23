#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <utility>
#include <vector>
#include <list>

/**
 * Tre categorie di cose dentro la libreria: 
 * - container -> classi che rappresentano delle strutture dati (esempio vector, list, set)
 * - iteratori -> meccanismi standardizzati per ciclare su i contenitori
 * - algoritmi -> basati sugli iteratori su dei contenitori (molto efficienti)
*/

/**
 * Vettori vs liste vs set:
 * - liste più comode solo in alcuni casi e hanno senso solo se gli algoritmi gestiscono tutta la lista
 * - il vettore molto più veloce (se devo accedere al 50esimo elemento, so già dove trovarlo, mentre nelle liste no)
 * - set é più veloce per cercare un elemento all'interno perché gestisce gli elementi tramite un labero binario. Quindi faccio 
 * meno confronti (é fatto apposta).
 * 
*/

/**
 * vettore in cui parametro T é int
 * 
 * Questa dichiarazione é compatibile da c++17. Per le versioni prima si utilizza questa:
 * 
 * auto leggiDaFile(const char* filePath) -> march::vector<double>
 */
auto leggiDaFile(const char* filePath) {

    FILE *fi;
    
    fi = fopen(filePath, "r"); 

    std::vector <double> v;

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

auto leggiList(const char* filePath) {

    FILE *fi;
    
    fi = fopen(filePath, "r"); 

    std::list <double> v;

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

    using std::vector;
    using std::list;
    // Nel c++ c'è l'ADL (Argument Dependent Lookup) -> ricerca dipendente degli argomenti
    // Se specifico il namespace per la classe vector, allora per la funzione swap viene cercato anche
    // all'interno del namespace degli argomenti.
    vector<char> c1(3), c2(2);

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

    vector<double> v =  leggiDaFile(argv[1]);

    list <double> l = leggiList(argv[1]);

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

    // Se v fosse una lista, il funzionamento sarebbe lo stesso a meno del tipo dell'iteratore
    auto it_stop = v.end();
    for (auto it = v.begin(); it != it_stop; ++it) {
        double x = *it;
        fprintf(fo, "%f\n", x);
    }

    // Per la lista non cambia nulla
    auto it_stop_l = l.end();
    for (auto it = l.begin(); it != it_stop_l; ++it) {
        double x = *it;
        fprintf(fo, "%f\n", x);
    }

    fclose(fo);

    return 0;
}

