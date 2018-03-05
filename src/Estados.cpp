#include "Estados.h"

Estados::Estados(string nombre)
{
    cantCaminos = 0;
    this->nombre = nombre;
}

Estados::~Estados()
{
    //dtor
}

Arista * Estados::obtenerCamino(int num)
{
    return caminos.at(num);
}

void Estados::agregarCamino(Arista * a)
{
    caminos.push_back(a);
    cantCaminos++;
}
