#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int cmpint(const void *a, const void *b)
{
    const int *pa = a;
    const int *pb = b;

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
    size_t c;   // capacità allocata
    int *dati;  // puntatore ai dati
    size_t n;   // numero elementi
};
void vector_costruttore(struct vector *this)
{
    this->c = 1;
    this->dati = malloc(this->c*sizeof(int));
    if (this->dati == NULL) exit(1); // Solo per prova
    this->n = 0;
};
void vector_distruttore(struct vector *this) {
    free(this->dati);
}
void vector_push_back(struct vector *this, int val) {
    if (this->n == this->c) {
        this->c = this->c*2;

        int *tmp = realloc(this->dati, this->c*sizeof(int));
        if (tmp == NULL) exit(1);

        this->dati = tmp;

    }
    this->dati[this->n] = val;
    ++this->n;
}
void vector_sort(struct vector *this) {
    qsort(this->dati, this->n, sizeof(int), *cmpint);
}
size_t vector_size(const struct vector * const this){
    return this->n;
}
int vector_at(const struct vector * const this, const size_t pos) {
    // Se la condizione non si verifica, in modalità debug si inchioda
    // in release non viene considerato
    assert(pos < this->n);
    return this->dati[pos];
}
struct vector *new_vector(void){
    struct vector *x = malloc(sizeof(struct vector));
    vector_costruttore(x);
    return x;
}
void delete_vector(struct vector * this) {
    vector_distruttore(this);
    free(this);
}

int main(int argc, char** argv) {

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

    struct vector *v = new_vector();

    int tmp;
    while (fscanf(fi, "%d", &tmp) == 1) {
        vector_push_back(v, tmp);
    }

    fclose(fi);

    fo = fopen(argv[2], "w"); 

    if (fo == NULL) {
        printf("Error while opening the output file\n");
        return 3; 
    }
    vector_sort(v);

    for (size_t j = 0; j < vector_size(v); j++) {
        fprintf(fo, "%d\n", vector_at(v, j));
    }

    fclose(fo);

    delete_vector(v);

    return 0;
}