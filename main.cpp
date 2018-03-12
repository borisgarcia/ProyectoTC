#include <iostream>
using namespace std;
#include "Automata.h"

int main()
{


        Automata * test = new Automata();
        test->alfabeto.push_back("A");
        test->alfabeto.push_back("B");
        test->cantAceptacion = 1;
        test->cantAlfabeto = 2;
        test->cantEstados = 6;


        Estados * e0 = new Estados("Q0");
        Estados * e1 = new Estados("Q1");
        Estados * e2 = new Estados("Q2");
        Estados * e3 = new Estados("Q3");
        Estados * e4 = new Estados("Q4");
        Estados * e5 = new Estados("Q5");

        test->estados.push_back(e0);
        test->estados.push_back(e1);
        test->estados.push_back(e2);
        test->estados.push_back(e3);
        test->estados.push_back(e4);
        test->estados.push_back(e5);

        Arista * a0 = new Arista(1,"A");
        Arista * a1 = new Arista(2,"A");
        Arista * a2 = new Arista(4,"A");
        Arista * a3 = new Arista(3,"A");
        Arista * a6 = new Arista(0,"A");
        Arista * a4 = new Arista(0,"B");
        Arista * a5 = new Arista(0,"B");
        Arista * a7 = new Arista(5,"B");

        test->obtenerEstado(0)->agregarCamino(a0);
        test->obtenerEstado(0)->agregarCamino(a1);
        test->obtenerEstado(0)->agregarCamino(a2);
        test->obtenerEstado(2)->agregarCamino(a3);
        test->obtenerEstado(3)->agregarCamino(a4);
        test->obtenerEstado(1)->agregarCamino(a5);
        test->obtenerEstado(5)->agregarCamino(a6);
        test->obtenerEstado(4)->agregarCamino(a7);

        test->definirInicial(test->obtenerEstado(0));
        test->inicial->aceptacion = true;
        //test->obtenerEstado(1)->aceptacion = false;

    test->resolverDFA1("AAAAA");


    return 0;
}
