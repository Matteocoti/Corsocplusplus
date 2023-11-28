#include <vector>
#include <algorithm>
#include <fstream>
// Per standard output invece che su file
#include <iostream> 

// Nella libreria iterator c'é la classe che adatta uno stream in modo da poterlo gestire come 
// se fosse una classe di elementi
#include <iterator>

int main(int argc, char** argv) {

    using std::vector;

    // Controllo che gli argomenti passati siano due
    if (argc < 2) {
        printf("Missing arguments!\n");
        return 1;
    }

    std::vector<int> a = {1, 2, 3, 4, 5};
    
    // Così chiamo il costruttore di copia
    //std::vector<int> b = a;

    // auto it_start = a.begin();
    // //auto it_stop = it_start + 3; // Con gli iteratori posso dire di avanzare di tre
    // auto it_stop = it_start;
    // advance(it_stop, 3); // Stessa cosa
    // std::vector<int> b(it_start, it_stop); // Anche in questo caso l'elemento puntato da it_stop é escluso

    std::ifstream is(argv[1]);

    if (!is)
        return 1;

    // Permette di estrarre dati con >> (legge in formato testo)
    // std::istream_iterator<double> it_start(is);
    // std::istream_iterator<double> it_stop; // Se non gli passiamo lo stream é la fine del file (in stato EOF)
    // std::vector<double> v(it_start, it_stop);

    // Se non mettiamo le graffe, Most Vexing Espression -> viene interpretata come puntatore a funzione senza parametri
    std::vector<double> v{std::istream_iterator<double>(is), std::istream_iterator<double>()};

    // Questo é superfluo, visto che vector ha un costruttore con gli iteratori, allora posso usare direttamente quello
    // for (auto it = it_start; it != it_stop; ++it) {
    //     v.push_back(*it);
    // }


    // Estrai dei byte e li converte (leggi i dati binari ) std::istreambuf_iterator

    FILE* fo;
    
    // vector v(); // Most vexing parsing -> pensa sia una funzione v che restituisce un vector 

    // auto v =  leggiDaFile(argv[1]);

    sort(v.begin(), v.end());

    std::ofstream os(argv[2]);

    if (!os) 
        return -1;

    // Il secondo elemento é un delimitatore, ovvero cosa vogliamo tra un numero e l'altro
    // Gli stream sono indipendenti dalle stringhe
    std::copy(begin(v), end(v), std::ostream_iterator<double>(os, "\n"));



    // Stessa funzione ma sto indirizzando la scrittura su due output differenti 
    //scrivi_vettore(os, v);
    //scrivi_vettore(std::cout, v);

    return 0;
}

