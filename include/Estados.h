#ifndef ESTADOS_H
#define ESTADOS_H
#include "Arista.h"

class Estados
{
    public:
        Estados(string nombre);
        virtual ~Estados();
        vector<Arista*> caminos;
        vector<Estados*> NFA;
        Arista * obtenerCamino(int num);
        void agregarCamino(Arista * a);
        string nombre;
        int cantCaminos;
        bool aceptacion;

    protected:

    private:
};

#endif // ESTADOS_H
