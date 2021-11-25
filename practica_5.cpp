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
#include <limits>

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

    int generarLlave()
    {
        string temp;
        int valor;
        srand(time(NULL));
        valor = rand() % (999 - 0) + 1;

        if (valor < 10)
        {
            temp.append("00" + to_string(valor));
        }
        else if (valor >= 10 && valor < 100)
        {
            temp.append("0" + to_string(valor));
        }

        return valor;
    }

    void insertar(Arbol **aux, int llave, int nrr)
    {
        if (*aux == nullptr) // si el apuntador es nulo creamos un nuevo nodo
        {
            (*aux) = new Arbol;
            (*aux)->llave = llave;
            (*aux)->nrr = nrr;
            (*aux)->hijoDerecho = nullptr;
            (*aux)->hijoIzquierdo = nullptr;
        }
        else // si no
        {
            if (llave < (*aux)->llave) // comparamos si la llave que recibimos es menor al nodo en el que nos encontramos
            {
                insertar(((&(*aux)->hijoIzquierdo)), llave, nrr); // si lo es llamamos una funcion recursiva que llama la funcion insertar y tomamos el hijo izquierdo
            }
            else
            {
                insertar(((&(*aux)->hijoDerecho)), llave, nrr); // si es mayor llamamos ala funcion recursiva tomando el de la derecha
            }
        }
    }

    void buscar(Arbol *&aux, int llave)
    {
        ifstream reg;
        string buffer;
        buffer.clear();
        reg.open("Productos_Media.txt"); // se abre el archivo en modo de lectura

        if (aux == nullptr) // si lo que regresamos es nulo repetimos
        {
            return;
        }

        buscar(aux->hijoIzquierdo, llave); // llamamos funcion recursiva e hijo izquierdo

        buscar(aux->hijoDerecho, llave); // llamamos funcion recursiva para recorrer el hijo derecho

        if (aux->llave == llave) // comparamos si el nodo tiene la llave que nos pasaron
        {
            cout << "El dato:" << llave << "| Fue encontrado" << endl;
            cout << "nrr" << aux->nrr << endl;
            reg.seekg(0, reg.beg); // posicionarnos al inicio del archivo
            int i = 0;
            for (i = 0; i <= aux->nrr; i++)
            { // leer tantas lineas para llegar ala deseada
                buffer.clear();
                getline(reg, buffer); // leer linea
            }

            cout << buffer; // mostrar informacion
            reg.close();
            return;
        }
        else
        {

            reg.close();
            buffer.clear();
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
void escribirArbol(Arbol *root)
{
    ofstream escribir;
    string llaveTemp;
    string nrrTemp;
    string hd;
    string hi;

    // inicia el flujo de escritura
    escribir.open(ARCHIVO_ARBOL, ios::app);

    // Comprobamos que el arbol no este vacio
    if (root != nullptr)
    {

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
        if (root->hijoDerecho != nullptr)
        {
            if (root->hijoDerecho->nrr < 10)
            {
                hd.append("  ");
            }
            else if (root->hijoDerecho->nrr >= 10 && root->hijoDerecho->nrr < 100)
            {
                hd.append(" ");
            }
            hd.append(to_string(root->hijoDerecho->nrr));
        }
        else
        {
            hd = " -1";
        }

        /*
            modifica la llave para que sea de 3 digitos
        */
        if (root->llave < 10)
        {
            llaveTemp.append("00");
        }
        else if (root->llave >= 10 && root->llave < 100)
        {
            llaveTemp.append("0");
        }

        llaveTemp.append(to_string(root->llave));

        /*
            Agrega espacios al nrr para que se acomode en la tabla
        */
        if (root->nrr < 10)
        {
            nrrTemp.append("  ");
        }
        else if (root->nrr >= 10 && root->nrr < 100)
        {
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

string concatenar(string buffer)
{
    return (buffer + '|');
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
    string buffreg;
    ofstream registros;

    string respuesta;
    do
    {
        cin.get();
        system("clear");
        cout << "Arbol binario" << endl;
        cout << "1 > Insertar registro" << endl;
        cout << "2 > Imprimir Arbol" << endl;
        cout << "3 > Mostrar registro" << endl;
        cout << "0 > Salir" << endl;
        cout << "Respuesta >";
        cin >> res;

        switch (res)
        {
        case 1:
            respuesta.clear();
            buffreg.clear();
            registros.open("Productos_Media.txt", std::fstream::app); // abrimos el archivo

            llave = ancla->generarLlave();
            cout << "Llave generada " << llave << endl; // generacion de llave
            buffreg += to_string(llave);                // concatenar llave
            buffreg += '|';

            // ingresar datos del registro
            cout << "Ingresa un nombre" << endl; //pedir datos
            fflush(stdin);                       // limpieza de buffer
            cin.clear();

            cin >> respuesta; // leer respuesta
            cin.clear();

            buffreg += respuesta; // concatenar respuesta al buffer
            buffreg += '|';       // agregar delimitador
            cout << "Ingresa una descripcion" << endl;
            cin.clear();
            fflush(stdin);

            cin >> respuesta;
            buffreg += respuesta;
            buffreg += '|';
            cout << "Ingresa el precio" << endl;
            cin.clear();
            fflush(stdin);

            cin >> respuesta;
            buffreg += respuesta;
            buffreg += '|';
            cout << "Ingresa la cantidad" << endl;
            cin.clear();
            fflush(stdin);

            cin >> respuesta;
            buffreg += respuesta;
            buffreg += '|';
            cout << "Ingresa la provicincia" << endl;
            cin.clear();
            fflush(stdin);

            cin >> respuesta;
            buffreg += respuesta;
            buffreg += '|';
            cout << "Ingresa la categoria" << endl;
            cin.clear();
            fflush(stdin);

            cin >> respuesta;
            buffreg += respuesta;
            buffreg += '|';

            cout << "registro:" << buffreg;
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

            registros << buffreg << endl;
            registros.close();
            // aumenta el nrr
            nrr++;
            break;
        case 2:
            cout << "[nrr|llave]" << endl
                 << endl;
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