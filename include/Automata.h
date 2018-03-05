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
        int NFAtoDFA_R();

        bool resolverDFA(char palabra[]);
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
