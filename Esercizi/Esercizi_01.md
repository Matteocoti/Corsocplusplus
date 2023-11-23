# Esercizio 1

Nei file `mv.h` e `mv.cpp` definisci le seguenti funzioni: 

```c++
double Mean(const std::vector<int> &v);

double Variance(const std::vector<int> &v);
```

Le funzioni prendono in input un vettore di numeri interi e ritornarno rispettivamente la loro media e varianza.

# Esercizio 2

Implementare le funzioni `Mean` e `Variance` affinché possano calcolare media e variaza su vettori di numeri *di qualunque tipo*.

# Esercizio 3

Implementare le funzioni `Mean` e `Variance` affinché possano calcolare media e varianza su qualunque tipo di contenitore di numeri.

# Esercizio 4

Nei file `ribalta.h` definire la seguente funzione: 

```c++
template <typename T>
void Ribalta(std::vector<T> &v);
```

La funzione prende in input il vettore `v` e ne "ribalta" gli elementi.

Se il vettore di input fosse ad esempio `v = {1, 2, 3, 4}`, la funzione dovrebbe trasformarlo in `v = {4, 3, 2, 1}`.

# Esercizio 5

Implementare la funzione `Ribalta` affinché funzioni su diversi tipi di contenitori.

# Esercizio 6

Scrivere la funzione `nodup()` che prende in input un vettore di numeri, `v_in`, e ritorna un nuovo vettore, `v_out` contenente gli stessi numeri, ripetuti una sola volte. L'ordine degli elementi in `v_out` non è importante.

Dato l'input `v_in = {4, 1, 1, 4, 7, 9, 7}` la funzione potrebbe ritornare `v_out = {1, 4, 7, 9}` o anche `v_out = {9, 4, 7, 1}` o qualsiasi altra permutazione.

# Esercizio 7

Scrivere la funzione `nodup_ord()` che prende in input un vettore di numeri, `v_in`, e ritorna un nuovo vettore, `v_out` contenente gli stessi numeri, ripetuti una sola volte. L'ordine degli elementi di `v_in` deve essere preservato. Dato l'input `v_in = {4, 1, 1, 4, 7, 9, 7}`, la funzione deve ritornare `v_out = {4, 1, 7, 9}`.