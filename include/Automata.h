#ifndef AUTOMATA_H
#define AUTOMATA_H
#include "Estados.h"

class Automata
{
    public:
        Automata();
        virtual ~Automata();

        void AgregarEAceptacion(Estados * e);
        void crearDFA();
        void crearNFA();
        void imprimirDFA();
        void defAlfabeto();
        void agregarEstados();
        void definirInicial(Estados * e);

        int NFAtoDFA();

        void  resolverDFA1(string palabra);
        bool resolverDFA(string palabra);
        int  resolverDFA1_2(Estados * e,vector<Arista*> a,int contArista,string pal,int contPal);
        Estados * obtenerEstado(int num);

        vector<Estados*> aceptacion;
        vector<Estados*> estados;

        vector<Estados*> eNFAtoDFA;
        vector<Estados*> eNFAtoDFA_R;

        vector<string> alfabeto;

        int cantAceptacion;
        int cantEstados;
        int cantAlfabeto;
        Estados * inicial;

    protected:

    private:
};

#endif // AUTOMATA_H
