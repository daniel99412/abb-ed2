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
string ARCHIVO_ARBOL = "Arbol.txt"; // nombre del archivo indizado para generar el arbol

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
        srand(time(NULL));
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
        printf("[%d|%d]\n", root->nrr, root->llave);
        structure(root->hijoIzquierdo, level + 1);
    }
}

// Genera un archivo indizado en forma de árbol binario
void escribirArbol(Arbol *root) {
    ofstream escribir;
    string llaveTemp;
    string nrrTemp;
    string hd;
    string hi;

    // inicia el flujo de escritura
    escribir.open(ARCHIVO_ARBOL, ios::app);

    // Comprobamos que el arbol no este vacio
    if (root != nullptr) {

        /*
            Comprueba que exista un hijo izquierdo
            si existe toma el nrr y le agrega espacios para acomodar en la tabla
            si no existe apunta a -1
        */
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

        /*
            Comprueba que exista un hijo izquierdo
            si existe toma el nrr y le agrega espacios para acomodar en la tabla
            si no existe apunta a -1
        */
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

        /*
            modifica la llave para que sea de 3 digitos
        */
        if (root->llave < 10) {
            llaveTemp.append("00");
        } else if (root->llave >= 10 && root->llave < 100) {
            llaveTemp.append("0");
        }
        
        llaveTemp.append(to_string(root->llave));

        /*
            Agrega espacios al nrr para que se acomode en la tabla
        */
        if (root->nrr < 10) {
            nrrTemp.append("  ");
        } else if (root->nrr >= 10 && root->nrr < 100) {
            nrrTemp.append(" ");
        }
        nrrTemp.append(to_string(root->nrr));

        // Escribe la informacion del nodo
        escribir << nrrTemp << "|" << llaveTemp << "|" << hd << "|" << hi << "|" << endl;

        // Escribe la informacion del hijo derecho
        escribirArbol(root->hijoDerecho);

        // Escribe la informacion del hijo izquierdo
        escribirArbol(root->hijoIzquierdo);
    }

    // cierra el flujo de escritura
    escribir.close();
}

int main()
{
    int nrr = 0;
    int res = 0;
    int llave = 0;
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
        // cout << "4 > Imprimir en Orden" << endl;
        cout << "2 > Imprimir Arbol" << endl;
        // cout << "6 > Eliminar" << endl;
        // cout << "7 > Anular" << endl;
        cout << "3 > Mostrar registro" << endl;
        cout << "0 > Salir" << endl;
        cout << "Respuesta >";
        cin >> res;

        switch (res)
        {
        case 1:
            llave = ancla->generarLlave();
            cout << "Llave generada " << llave << endl;
            ancla->insertar(&ancla, llave, nrr);
            cout << "Dato ingresado correctamente" << endl;
            cin.get();

            // Elimina el archivo anterior
            remove("Arbol.txt");

            // Crea el archivo nuevo
            escribir.open(ARCHIVO_ARBOL, ios::app);

            // escribe los encabezados
            escribir << "NRR|LLV| HD| HI|" << endl;

            // cierra el flujo de escritura
            escribir.close();

            // escribe el archivo indizado en forma de arbol
            escribirArbol(ancla);

            // aumenta el nrr
            nrr++;
            break;
        case 2:
            cout << "[nrr|llave]" << endl << endl;
            structure(ancla, 0);
            cin.get();

            break;
        case 3:
            cout << "Ingresa el numero que quieres buscar....";
            cin >> llave;
            ancla->buscar(ancla, llave);
            cin.get();

            break;
        }

    } while (res != 0);
    delete ancla;
    return 0;
}