#include <iostream>
using namespace std;
#include "Automata.h"
#include <fstream>
int main()
{
    Automata * test = new Automata();
    test->crearDFA();
    string filename = "enter.txt";
    string cadena;
    ifstream inFile(filename);
    while(inFile>>cadena){
       test->resolverDFA(cadena);
    }
    inFile.close();
    return 0;
}
