/*
    Pardo Rodriguez Daniel            210635942
    Vazquez Valadez Angel Isaac       220288655
    Materia: Estructuras de Datos II
    Tutorea: Lara Lopez Graciela
    Clave: I5888
    Seccion: D12
*/

#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>

using namespace std;
#define COUNT 10
string ARCHIVO_ARBOL = "Arbol.txt";

class Arbol
{
public:
    int nrr;
    int llave;
    Arbol *hijoIzquierdo;
    Arbol *hijoDerecho;

    Arbol()
    {
        this->hijoIzquierdo = nullptr;
        this->hijoDerecho = nullptr;
    }

    int generarLlave() {
        string temp;
        int valor;
        valor = rand() % (999-0)+1;

        if (valor < 10) {
            temp.append("00" + to_string(valor));
        } else if (valor >= 10 && valor < 100) {
            temp.append("0" + to_string(valor));
        }

        return valor;
    }

    void insertar(Arbol **aux, int llave, int nrr)
    {
        if (*aux == nullptr)
        {
            (*aux) = new Arbol;
            (*aux)->llave = llave;
            (*aux)->nrr = nrr;
            (*aux)->hijoDerecho = nullptr;
            (*aux)->hijoIzquierdo = nullptr;
        }
        else
        {
            if (llave < (*aux)->llave)
            {
                insertar(((&(*aux)->hijoIzquierdo)), llave, nrr);
            }
            else
            {
                insertar(((&(*aux)->hijoDerecho)), llave, nrr);
            }
        }
    }

    void inorder(Arbol **aux)
    {
        if (*aux != nullptr)
        {
            inorder(((&(*aux)->hijoIzquierdo)));
            if ((*aux)->llave < 10000)
            {
                cout << (*aux)->llave << "||";
            }
            inorder(((&(*aux)->hijoDerecho)));
        }
    }

    void preorder(Arbol **aux)
    {
        if (*aux != nullptr)
        {
            if ((*aux)->llave < 10000)
            {
                cout << (*aux)->llave << "||";
            }
            preorder(((&(*aux)->hijoIzquierdo)));
            preorder(((&(*aux)->hijoDerecho)));
        }
    }

    void postorder(Arbol **aux)
    {
        if (*aux != nullptr)
        {
            postorder(((&(*aux)->hijoIzquierdo)));
            postorder(((&(*aux)->hijoDerecho)));
            if ((*aux)->llave < 10000)
            {
                cout << (*aux)->llave << "||";
            }
        }
    }

    void elimina(Arbol **subarbol, int llave)
    {

        if (*subarbol == nullptr)
        {
            return;
        }
        if ((*subarbol)->llave == llave)
        {
            if ((*subarbol)->hijoIzquierdo == nullptr && (*subarbol)->hijoDerecho == nullptr)
            {
                delete *subarbol;
                *subarbol = nullptr;
                return;
            }

            if ((*subarbol)->hijoIzquierdo == nullptr && (*subarbol)->hijoDerecho != nullptr)
            {
                (*subarbol)->llave = (*subarbol)->hijoDerecho->llave;
                delete (*subarbol)->hijoDerecho;
                (*subarbol)->hijoDerecho = nullptr;
                return;
            }

            if ((*subarbol)->hijoIzquierdo != nullptr && (*subarbol)->hijoDerecho == nullptr)
            {
                (*subarbol)->llave = (*subarbol)->hijoIzquierdo->llave;
                delete (*subarbol)->hijoIzquierdo;
                (*subarbol)->hijoIzquierdo = nullptr;
                return;
            }

            if ((*subarbol)->hijoIzquierdo != nullptr && (*subarbol)->hijoDerecho != nullptr)
            {
                Arbol *aux = nullptr;
                aux = new Arbol;
                aux = (*subarbol);

                Arbol *auxz = nullptr;
                auxz = new Arbol;
                auxz = (*subarbol)->hijoDerecho;
                cout << auxz->llave;

                Arbol *auxi = nullptr;
                auxi = new Arbol;
                auxi = (*subarbol)->hijoDerecho;

                Arbol *auxe = nullptr;
                auxe = new Arbol;

                while (auxz->hijoIzquierdo != nullptr)
                {

                    auxz = auxz->hijoIzquierdo;
                }
                cout << auxz->llave;
                //Solo una vuelta
                if ((*subarbol)->hijoDerecho == auxz)
                {
                    auxe = (*subarbol)->hijoDerecho;

                    (*subarbol)->hijoDerecho = (*subarbol)->hijoDerecho->hijoDerecho;
                }
                else
                {

                    while (auxi->hijoIzquierdo != auxz)
                    {
                        if (auxi->hijoIzquierdo->hijoIzquierdo->llave == llave)
                            break;
                        auxi = auxi->hijoIzquierdo;
                    }
                }

                if ((*subarbol)->hijoDerecho != auxz)
                {
                    auxi->hijoIzquierdo = nullptr;
                }

                aux->llave = auxz->llave;
                return;
            }
        }
        else
        {
            if ((*subarbol)->llave > llave)
            {
                elimina(((&(*subarbol)->hijoIzquierdo)), llave);
            }
            else
            {
                elimina(((&(*subarbol)->hijoDerecho)), llave);
            }
        }
    }

    void buscar(Arbol *&aux, int llave)
    {
        if (aux == nullptr)
        {
            return;
        }

        buscar(aux->hijoIzquierdo, llave);

        buscar(aux->hijoDerecho, llave);

        if (aux->llave == llave)
        {
            cout << "El dato:" << llave << "| Fue encontrado" << endl;
            return;
        }
        else
        {
            cout << "El dato no fue encontrado" << endl;
        }
    }

    void anula(Arbol *&aux)
    {
        if (aux == nullptr)
            return;

        anula(aux->hijoIzquierdo);
        anula(aux->hijoDerecho);
        delete aux;
        aux = nullptr;
    }
};

void padding(char ch, int n)
{
    int i;
    for (i = 0; i < n; i++)
        putchar(ch);
}
void structure(Arbol *root, int level)
{
    int i;
    if (root == NULL)
    {
        padding('\t', level);
        puts("~");
    }
    else
    {
        structure(root->hijoDerecho, level + 1);
        padding('\t', level);
        printf("%d|%d\n", root->nrr, root->llave);
        structure(root->hijoIzquierdo, level + 1);
    }
}

void escribirArbol(Arbol *root) {
    ofstream escribir;
    string llaveTemp;
    string nrrTemp;
    string hd;
    string hi;
    escribir.open(ARCHIVO_ARBOL, ios::app);

    if (root != nullptr) {

        if (root->hijoIzquierdo != nullptr)
        {
            if (root->hijoIzquierdo->nrr < 10)
            {
                hi.append("  ");
            }
            else if (root->hijoIzquierdo->nrr >= 10 && root->hijoIzquierdo->nrr < 100)
            {
                hi.append(" ");
            }
            hi.append(to_string(root->hijoIzquierdo->nrr));
        }
        else
        {
            hi = " -1";
        }

        if (root->hijoDerecho != nullptr) {
            if (root->hijoDerecho->nrr < 10) {
                hd.append("  ");
            } else if (root->hijoDerecho->nrr >= 10 && root->hijoDerecho->nrr < 100) {
                hd.append(" ");
            }
            hd.append(to_string(root->hijoDerecho->nrr));
        } else {
            hd = " -1";
        }

        if (root->llave < 10) {
            llaveTemp.append("00");
        } else if (root->llave >= 10 && root->llave < 100) {
            llaveTemp.append("0");
        }
        
        llaveTemp.append(to_string(root->llave));

        if (root->nrr < 10) {
            nrrTemp.append("  ");
        } else if (root->nrr >= 10 && root->nrr < 100) {
            nrrTemp.append(" ");
        }
        nrrTemp.append(to_string(root->nrr));

        escribir << nrrTemp << "|" << llaveTemp << "|" << hd << "|" << hi << "|" << endl;
        escribirArbol(root->hijoDerecho);
        escribirArbol(root->hijoIzquierdo);
    }

    escribir.close();
}

int main()
{
    int nrr = 0;
    int res = 0;
    int dato = 0;
    int resBusqueda = 0;
    ofstream escribir;
    Arbol *ancla;
    ancla = new Arbol;

    do
    {
        cin.get();
        system("clear");
        cout << "Arbol binario" << endl;
        cout << "1 > Insertar registro" << endl;
        // cout << "2 > Imprimir en preOrden" << endl;
        // cout << "3 > Imprimir en postOrden" << endl;
        cout << "4 > Imprimir en Orden" << endl;
        cout << "5 > Imprimir Arbol" << endl;
        // cout << "6 > Eliminar" << endl;
        // cout << "7 > Anular" << endl;
        cout << "8 > Mostrar registro" << endl;
        cout << "0 > Salir" << endl;
        cout << "Respuesta >";
        cin >> res;

        switch (res)
        {
        case 1:
            dato = ancla->generarLlave();
            cout << "Llave generada " << dato << endl;
            ancla->insertar(&ancla, dato, nrr);
            cout << "Dato ingresado correctamente" << endl;
            cin.get();

            remove("Arbol.txt");
            escribir.open(ARCHIVO_ARBOL, ios::app);
            escribir << "NRR|LLV| HD| HI|" << endl;
            escribir.close();
            escribirArbol(ancla);
            nrr++;
            break;
        case 2:
            ancla->preorder(&ancla);
            cin.get();

            break;
        case 3:
            ancla->postorder(&ancla);
            cin.get();

            break;
        case 4:
            ancla->inorder(&ancla);
            cin.get();

            break;
        case 5:
            cout << "nrr|llave" << endl << endl;
            structure(ancla, 0);
            cin.get();

            break;
        case 6:
            cout << "Ingresa el numero que quieres eliminar....";
            cin >> dato;
            ancla->elimina(&ancla, dato);
            cin.get();

            break;
        case 7:
            ancla->anula(ancla);
            cout << "Anulado correctamente";
            cin.get();

            break;
        case 8:
            cout << "Ingresa el numero que quieres buscar....";
            cin >> dato;
            ancla->buscar(ancla, dato);
            cin.get();

            break;
        }

    } while (res != 0);
    delete ancla;
    return 0;
}