#include "conta.h"
#include <iostream>


int main() {

    using namespace std;

    string input = "  Questa e' una stringa lunga 45 caratteri.  ";

    cout << Conta(input) << endl;

    string input2 = "1 2 3 a b c";

    cout << Conta(input2) << endl;

    string input3 = "! @?$ ciao,prova";

    cout << Conta(input3) << endl;

    string input4 = " ";

    cout << Conta(input4) << endl;


    return 0;
}