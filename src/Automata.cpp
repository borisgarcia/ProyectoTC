#include "Automata.h"

Automata::Automata()
{
    cantAceptacion = 0;
    cantEstados = 0;
}

Automata::~Automata()
{
    //dtor
}


void Automata::agregarEstados()
{
    cout<<"Ingrese la Cantidad Estados: ";
    cin>>cantEstados;
    cout<<""<<endl;
    string nombre;

    for(int x = 0;x<cantEstados;x++)
    {
        nombre = "Q"+to_string(x);
        Estados * e = new Estados(nombre);
        this->estados.push_back(e);
    }
}

Estados * Automata::obtenerEstado(int num)
{
    return estados.at(num);
}

void Automata::AgregarEAceptacion(Estados * e)
{
    aceptacion.push_back(e);
}

void Automata::defAlfabeto()
{
    cout<<"Ingrese la Cantidad de Elementos del Alfabeto: ";
    cin>>cantAlfabeto;
    cout<<""<<endl;
    cout<<"Ingrese los Caracteres"<<endl;
    string elemento;
    for(int x = 0;x<cantAlfabeto;x++)
    {
        cin>>elemento;
        alfabeto.push_back(elemento);
    }
}

void Automata::definirInicial(Estados * e)
{
    inicial = e;
}

int Automata::NFAtoDFA()
{
    int contT[cantAlfabeto];
    int numE[cantAlfabeto];
    string name[cantAlfabeto];

    bool flag = false;
    int val;

    vector<string> names;

    for(int x = 0; x<cantEstados;x++)
    {
        flag = false;
        for(int y = 0;y<cantAlfabeto;y++)
        {
            contT[y] = 0;
            name[y] ="";
        }

        for(int y = 0;y<cantAlfabeto;y++)
        {
            for(int z = 0;z<obtenerEstado(x)->cantCaminos;z++)
            {
                if(obtenerEstado(x)->obtenerCamino(z)->elemento == alfabeto.at(y))
                {
                    name[y] = name[y] + "Q"+to_string(obtenerEstado(x)->obtenerCamino(z)->numEstado);
                    numE[y] = x;
                    contT[y]++;
                }
            }
        }

        //Verifica que tenga mas de 2 transiciones
        for(int y = 0;y<cantAlfabeto;y++)
        {
            if(contT[y] > 1)
                flag = true;
        }

        //Verifica que el estado ya no existe, si existe lo quita
        for(int y = 0;y<names.size();y++)
        {
            if(names.at(y)==name[y])
            {
                name[y]="";
            }
        }

        if(flag)
        {
            Estados * estado_A = new Estados(obtenerEstado(x)->nombre);
            eNFAtoDFA.push_back(estado_A);
            for(int y = 0;y<cantAlfabeto;y++)
            {
                Arista * tempA = new Arista(numE[y],alfabeto.at(y));
                estado_A->agregarCamino(tempA);

                if(names.size()==0)
                {
                    Estados * estado_B = new Estados(name[y]);
                    names.push_back(name[y]);
                    eNFAtoDFA.push_back(estado_B);
                }
                else if(names.size()>0)
                {
                    for(int j = 0;j<names.size();j++)
                    {
                        if(name[j]!=names.at(j))
                        {
                            Estados * estado_B = new Estados(name[y]);
                            names.push_back(name[y]);
                            eNFAtoDFA.push_back(estado_B);
                        }
                    }

                }
            }
        }
    }

    //Solo imprime para verificar
    for(int x = 0;x<eNFAtoDFA.size();x++)
    {
        cout<<eNFAtoDFA.at(x)->nombre<<endl;
    }
    return 0;
}

int Automata::NFAtoDFA_R()
{

}

void Automata::crearNFA()
{
    int cantT;
    bool flag = true;
    defAlfabeto();
    agregarEstados();
    for(int x = 0;x<cantEstados;x++)
    {
        for(int y = 0;y<cantAlfabeto;y++)
        {
            cout<<"Ingrese la cantidad de Transiciones de " + alfabeto[y] +" en el estado "+obtenerEstado(x)->nombre+": ";
            cin>>cantT;
            while(cantT!=0)
            {
                flag = true;
                int num;

                while(flag)
                {
                    cout<<"Ingrese el estado para la transicion desde " +obtenerEstado(x)->nombre + " con "+ alfabeto[y] + ": ";
                    cout<<"Q";
                    cin>>num;
                    if(num < cantEstados)
                    {
                        Arista * a = new Arista(num,alfabeto.at(y));
                        obtenerEstado(x)->agregarCamino(a);
                        flag = false;
                    }
                    else
                    {
                        cout<<"Estado no Existe"<<endl;
                    }
                }
                cantT--;
            }
        }
    }
    cout<<"Definir Estado Inicial"<<endl;
    cout<<"Ingrese el Estado Inicial: Q";

    int in;
    cin>>in;
    definirInicial(obtenerEstado(in));

    cout<<"Ingrese la cantidad de Estados de Aceptacion que desea definir: ";
    cin>>cantAceptacion;
    int eAceptacion;
    for(int x = 0;x<cantAceptacion;x++)
    {
        cout<<"Ingrese el numero de Estado :Q";
        cin>>eAceptacion;
        aceptacion.push_back(obtenerEstado(eAceptacion));
        obtenerEstado(eAceptacion)->aceptacion = true;
    }
}

void Automata::crearDFA()
{
    defAlfabeto();
    agregarEstados();
    bool flag = true;
    for(int x = 0;x<cantEstados;x++)
    {
        for(int y = 0;y<cantAlfabeto;y++)
        {
            flag = true;
            int num;

            while(flag)
            {
                cout<<"Ingrese el estado para la transicion desde " +obtenerEstado(x)->nombre + " con "+ alfabeto[y] + ": ";
                cout<<"Q";
                cin>>num;
                if(num < cantEstados)
                {
                    Arista * a = new Arista(num,alfabeto.at(y));
                    obtenerEstado(x)->agregarCamino(a);
                    flag = false;
                }
                else
                {
                    cout<<"Estado no Existe"<<endl;
                }
            }
        }
    }
    cout<<"Definir Estado Inicial"<<endl;
    cout<<"Ingrese el Estado Inicial: Q";

    int in;
    cin>>in;
    definirInicial(obtenerEstado(in));

    cout<<"Ingrese la cantidad de Estados de Aceptacion que desea definir: ";
    cin>>cantAceptacion;
    int eAceptacion;
    for(int x = 0;x<cantAceptacion;x++)
    {
        cout<<"Ingrese el numero de Estado :Q";
        cin>>eAceptacion;
        aceptacion.push_back(obtenerEstado(eAceptacion));
        obtenerEstado(eAceptacion)->aceptacion = true;
    }
}

void Automata::imprimirDFA()
{
    for(int x = 0;x<cantEstados;x++)
    {
        cout<<obtenerEstado(x)->nombre + " tiene transiciones hacia: ";
            for(int z = 0;z<obtenerEstado(x)->cantCaminos;z++)
            {
                cout<<"Q";
                cout<<obtenerEstado(x)->obtenerCamino(z)->numEstado;
                cout<<" con ";
                cout<<obtenerEstado(x)->obtenerCamino(z)->elemento;
                if(z != (obtenerEstado(x)->cantCaminos - 1))
                    cout<<" | ";
            }

        cout<<""<<endl;
    }
}



bool Automata::resolverDFA(string palabra)
{
    int cont = 0;
    Estados * actual = inicial;

    for(int x =0;x<palabra.size();x++)
    {
        for(int y = 0;y<cantAlfabeto;y++)
        {

            string x1 = actual->obtenerCamino(y)->elemento;

            if(x1.at(0) == palabra.at(x))
            {
                actual = obtenerEstado(actual->obtenerCamino(y)->numEstado);
            }
        }
    }
    int s = aceptacion.size();
    for (int x = 0;x<s;x++)
    {
        if(aceptacion.at(x)->nombre == actual->nombre)
        {
            cout<<"La Palabra: -"<<palabra<<"- es aceptada - Estado Actual " + actual->nombre<<endl;
            return true;
        }
    }
    cout<<"La Palabra: -"<<palabra<<"- no es aceptada"<<endl;
    return false;

}

bool Automata::resolverDFA1(string palabra)
{
    Estados * actual = inicial;
    return resolverDFA1_2(actual,palabra,0);
}

bool Automata::resolverDFA1_2(Estados * e,string pal,int cont)
{
    if(cont < pal.size())
    {
        for(int y = 0;y<cantAlfabeto;y++)
        {
            string x = e->obtenerCamino(y)->elemento;
            if(x.at(0) == pal.at(cont))
            {
                e = obtenerEstado(e->obtenerCamino(y)->numEstado);
                return resolverDFA1_2(e,pal,cont+1);
            }
        }
    }
    else if (e->aceptacion && cont == (pal.size()))
    {
        cout<<"Aceptada";
        return true;
    }

    else if (!e->aceptacion && cont == (pal.size()))
        return false;


}
