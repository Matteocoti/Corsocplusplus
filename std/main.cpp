#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>

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

    std::ifstream is(filePath);

    std::vector <double> v;

    // Se lo stream viene rappresentato come un bool, il risultato é l'esito della costruzione dello
    // stream, ovvero il suo stato (corrisponde al metodo fail())
    if (!is) return v;

    double num;
    while  (is >> num) {
        v.push_back(num);
    }

    return v;
}


int main(int argc, char** argv) {

    using std::vector;

    // Controllo che gli argomenti passati siano due
    if (argc < 2) {
        printf("Missing arguments!\n");
        return 1;
    }

    FILE* fo;
    
    // vector v(); // Most vexing parsing -> pensa sia una funzione v che restituisce un vector 

    auto v =  leggiDaFile(argv[1]);

    std::ofstream os(argv[2]); 

    if (!os) return 3; 
    
    // Si può vedere il codice sorgente perché é una funzione a template, quindi non si può compilare prima
    sort(v.begin(), v.end());
    // Se v fosse una lista, il funzionamento sarebbe lo stesso a meno del tipo dell'iteratore
    auto it_stop = v.end();

    // Prendi v e chiama begin e hai l'iteratore, poi ad ogni ciclo chiami il next e lo fai fino ad end.
    // La forma si chiama Range Based For 
    // x é solo il nome che diamo per accedere il nome corrente di v
    for (const auto& x : v) {
        os << x << '\n';
    }
    
    return 0;
}

