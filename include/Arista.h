#ifndef ARISTA_H
#define ARISTA_H
#include <vector>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

using namespace std;

class Arista
{
    public:
        Arista(int numEstado, string elemento);
        string elemento;
        int numEstado;
        virtual ~Arista();

    protected:

    private:
};

#endif // ARISTA_H
