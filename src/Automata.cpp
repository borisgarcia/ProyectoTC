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
    /*for(int x = 0;x<eNFAtoDFA.size();x++)
    {
        cout<<eNFAtoDFA.at(x)->nombre<<endl;
    }*/
    return 0;
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

void Automata::resolverDFA1(string palabra)
{
    Estados * actual = inicial;
    if(resolverDFA1_2(actual,inicial->caminos,0,palabra,0))
        cout<<"Palabra: "<<palabra<<" no aceptada"<<endl;
    else
        cout<<"Palabra: "<<palabra<<" es aceptada"<<endl;
}

int Automata::resolverDFA1_2(Estados * e,vector<Arista*> a,int contArista,string pal,int contPal)
{
    if(contPal == pal.size())
    {
        if(e->aceptacion)
            return 0;
        else
            return 1;
    }
    for(contArista = 0;contArista<a.size();contArista++)
    {
        int y = -1;
        Arista * arist = a.at(contArista);
        string test = arist->elemento;
        if(test.at(0) == pal.at(contPal))
        {
            y = resolverDFA1_2(obtenerEstado(arist->numEstado),obtenerEstado(arist->numEstado)->caminos,0,pal,contPal+1);
            if(y == 3)
                continue;
            else if(y == 1)
                continue;
            else if(y == 0)
                return y;
        }
    }
    return 3;
}



int Gramatica::_check(NoTerminal *noTerminal, vector<string> vs, string cadena, int cont)
{
    if(cont==cadena.size())
    {
        if(noTerminal->terminal)
        {
            cout<<"Palabra Aceptada"<<endl;
            return 0;
        }
        else
            return 1;
    }
    else
    {
        cout<<"______________"<<endl;
        cout<<"ElsePrincipal - Contador: "<<cont<<endl;
        cout<<"Actual: "<<noTerminal->nombre<<endl;
        for(int x = 0;x<vs.size();x++)
        {
            bool flag = false;
            int b = -1;
            string temp = vs.at(x);
            for(int y = 0;y<temp.size();y++)
            {
                if(isupper(temp.at(y)))
                {
                    stringstream ss;
                    string s;
                    ss << temp.at(y);
                    ss >> s;
                    noTerminal = obtenerNT(s);
                    cout<<"isUpper - "<<s<<endl;
                    b = _check(noTerminal,noTerminal->producciones,cadena,cont);
                    if(b == 1)
                        continue;
                    if(b == 2)
                        continue;
                    else if(b == 0)
                        return b;
                }
                else
                {
                    if(temp.at(y)==cadena.at(cont))
                    {
                        if(temp.size()==1 || (temp.size()-1) == y)
                        {
                            cout<<"LowerSolo - "<<temp.at(y)<<endl;
                            stringstream tt;
                            string t;
                            tt << temp.at(y);
                            tt >> t;
                            noTerminal = obtenerT(t);
                            b = _check(noTerminal,noTerminal->producciones,cadena,++cont);
                            if(b == 1)
                                continue;
                            if(b == 2)
                                continue;
                            else if(b == 0)
                                return b;
                        }
                        else
                        {
                            cout<<"Lower - "<<temp.at(y)<<endl;
                            cont++;
                        }

                    }
                    else
                    {
                        cout<<"NEL"<<endl;
                        break;
                    }

                }

            }
        }
    }
    return 2;

}