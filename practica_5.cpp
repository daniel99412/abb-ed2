#include <iostream>
#include <windows.h>
#include <conio.h>
#include<bits/stdc++.h>



using namespace std;
#define COUNT 10
class Arbol {
public:
    int dato;
    Arbol *hijoIzquierdo;
    Arbol *hijoDerecho;

    Arbol(){

        this->hijoIzquierdo = nullptr;
        this->hijoDerecho = nullptr;
    }

    void insertar( Arbol **aux, int dato ){

        if(*aux == nullptr) {

            (*aux) = new Arbol;
            (*aux)->dato = dato;
            (*aux)->hijoDerecho = nullptr;
            (*aux)->hijoIzquierdo = nullptr;
        } else {
            if( dato < (*aux)->dato ){

                insertar(((&(*aux)->hijoIzquierdo)),dato);
            } else {

                insertar(((&(*aux)->hijoDerecho)),dato);
            }
        }
    }

    void inorder( Arbol **aux) {
        if( *aux != nullptr){
            inorder(((&(*aux)->hijoIzquierdo)));
            if((*aux)->dato<10000){
                 cout<<(*aux)->dato<<"||";
            }
            inorder(((&(*aux)->hijoDerecho)));
        }
    }

    void preorder( Arbol **aux) {
        if( *aux != nullptr){
            if((*aux)->dato<10000){
                 cout<<(*aux)->dato<<"||";
            }
            preorder(((&(*aux)->hijoIzquierdo)));
            preorder(((&(*aux)->hijoDerecho)));
        }
    }

    void postorder( Arbol **aux) {
        if( *aux != nullptr){
            postorder(((&(*aux)->hijoIzquierdo)));
            postorder(((&(*aux)->hijoDerecho)));
            if((*aux)->dato<10000){
                cout<<(*aux)->dato<<"||";
            }
        }
    }




    void elimina( Arbol **subarbol, int dato ){

        if( *subarbol == nullptr){
            return;
        }
        if( (*subarbol)->dato == dato) {

            if((*subarbol)->hijoIzquierdo == nullptr && (*subarbol)->hijoDerecho == nullptr ) {
                 delete *subarbol;
                *subarbol = nullptr;
                return;
            }

             if((*subarbol)->hijoIzquierdo == nullptr && (*subarbol)->hijoDerecho != nullptr ) {
                (*subarbol)->dato = (*subarbol)->hijoDerecho->dato;
                delete (*subarbol)->hijoDerecho;
                (*subarbol)->hijoDerecho = nullptr;
                return;
            }

            if((*subarbol)->hijoIzquierdo != nullptr && (*subarbol)->hijoDerecho == nullptr ) {
                (*subarbol)->dato = (*subarbol)->hijoIzquierdo->dato;
                delete (*subarbol)->hijoIzquierdo;
                (*subarbol)->hijoIzquierdo = nullptr;
                return;
            }


             if((*subarbol)->hijoIzquierdo != nullptr && (*subarbol)->hijoDerecho != nullptr ) {


                Arbol *aux = nullptr;
                aux = new Arbol;
                aux = (*subarbol);

                Arbol *auxz = nullptr;
                auxz = new Arbol;
                auxz = (*subarbol)->hijoDerecho;
                cout<<auxz->dato;

                Arbol *auxi = nullptr;
                auxi = new Arbol;
                auxi = (*subarbol)->hijoDerecho;

                Arbol *auxe = nullptr;
                auxe = new Arbol;


                while( auxz->hijoIzquierdo != nullptr ){

                    auxz = auxz->hijoIzquierdo;
                }
                cout<<auxz->dato;
                //Solo una vuelta
                if( (*subarbol)->hijoDerecho == auxz ){
                     auxe = (*subarbol)->hijoDerecho;


                    (*subarbol)->hijoDerecho = (*subarbol)->hijoDerecho->hijoDerecho;



                } else {

                     while( auxi->hijoIzquierdo != auxz ){
                        if( auxi->hijoIzquierdo->hijoIzquierdo->dato == dato )
                            break;
                        auxi = auxi->hijoIzquierdo;

                    }
                }

                if( (*subarbol)->hijoDerecho != auxz ){
                    auxi->hijoIzquierdo = nullptr;
                }

                aux->dato = auxz->dato;
                return;
             }






        }else {

            if( (*subarbol)->dato > dato ){

                 elimina(((&(*subarbol)->hijoIzquierdo)),dato);
            } else {

                elimina(((&(*subarbol)->hijoDerecho)),dato);
            }
        }

    }

    void buscar( Arbol *&aux, int dato ){

        if( aux == nullptr ){
            return;
        }

        buscar( aux->hijoIzquierdo, dato );

        buscar( aux->hijoDerecho, dato );

         if( aux->dato == dato){

                cout<<"El dato:"<<dato<<"| Fue encontrado"<<endl;
                getch();
            } else {

                cout<<"El dato no fue encontrado"<<endl;
            }
    }

    void anula( Arbol *&aux) {

        if( aux == nullptr )
            return;

        anula(aux->hijoIzquierdo);
        anula(aux->hijoDerecho);
        delete aux;
        aux = nullptr;
    }


};


void padding ( char ch, int n )
{
  int i;
  for ( i = 0; i < n; i++ )
    putchar ( ch );
}
void structure ( Arbol *root, int level )
{
  int i;
  if ( root == NULL ) {
    padding ( '\t', level );
    puts ( "~" );
  }
  else {
    structure ( root->hijoDerecho, level + 1 );
    padding ( '\t', level );
    printf ( "%d\n", root->dato );
    structure ( root->hijoIzquierdo, level + 1 );
  }
}



int main() {
    int res = 0;
    int dato = 0;
    int resBusqueda = 0;
    Arbol *ancla;
    ancla = new Arbol;
    ancla->insertar(&ancla,10);
    ancla->insertar(&ancla,7);
    ancla->insertar(&ancla,15);
    ancla->insertar(&ancla,12);
    ancla->insertar(&ancla,11);
    ancla->insertar(&ancla,13);
    ancla->insertar(&ancla,17);
    ancla->insertar(&ancla,20);
    ancla->insertar(&ancla,8);
    ancla->insertar(&ancla,9);
    ancla->insertar(&ancla,5);
    ancla->insertar(&ancla,6);
    ancla->insertar(&ancla,3);

    do{
        system("cls");
        cout<<"Arbol binario"<<endl;
        cout<<"1 > Insertar"<<endl;
        cout<<"2 > Imprimir en preOrden"<<endl;
        cout<<"3 > Imprimir en postOrden"<<endl;
        cout<<"4 > Imprimir en Orden"<<endl;
        cout<<"5 > Imprimir Arbol"<<endl;
        cout<<"6 > Eliminar"<<endl;
        cout<<"7 > Anular"<<endl;
        cout<<"Respuesta >";cin>>res;

        switch( res ) {
            case 1:
                cout<<"Ingresa un numero....";cin>>dato;
                cout<<endl;
                ancla->insertar(&ancla,dato);
                cout<<"Dato ingresado correctamente"<<endl;
                getch();
                break;
            case 2:
                ancla->preorder(&ancla);
                getch();
                break;
            case 3:
                ancla->postorder(&ancla);
                getch();
                break;
            case 4:
                ancla->inorder(&ancla);
                getch();
                break;
            case 5:
                structure(ancla, 0);
                getch();
                break;
            case 6:
                cout<<"Ingresa el numero que quieres eliminar....";cin>>dato;
                ancla->elimina(&ancla,dato);
                getch();
                break;
            case 7:
                ancla->anula(ancla);
                cout<<"Anulado correctamente";
                break;
            case 8:
                cout<<"Ingresa el numero que quieres buscar....";cin>>dato;
                ancla->buscar(ancla,dato);

                break;
        }

    }while( res != 0 );
    delete ancla;
    return 0;
}