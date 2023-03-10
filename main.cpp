#include <iostream>
using namespace std;


// ESTRUCTURAS

template <typename T>
struct Nodo{
    T info;
    Nodo *vi, *vd;
    int size;
};

template <typename T>
struct NodoLista{
    T info;
    NodoLista* sgte;
};


// LISTA

template <typename T>
bool isInLista(NodoLista<T>* lista, T t)
{
    while(lista != NULL)
    {
        if(t == lista->info){
            return true;
        }
        lista = lista->sgte;
    }
    return false;
}

template <typename T>
NodoLista<T>* insertarEnLista(NodoLista<T>* &lista, T t)
{
    NodoLista<T>* p = new NodoLista<T>();
    p->info = t;

    if (lista == NULL)
    {
        lista = p;
    }
    else
    {
        NodoLista<T>* q = lista;
        while (q->sgte != NULL)
        {
            q = q->sgte;
        }
        q->sgte = p;
    }
    return p;
}

template <typename T>
NodoLista<T>* pop(NodoLista<T>* &lista)
{
    NodoLista<T>* p = lista;
    lista = lista->sgte;
    
    return p;
}

// ARBOL

template <typename T>
int comparar(T a, T b)
{
    return a > b? 1: a < b? -1: 0;
}

template <typename T>
Nodo<T>* insertarArbol(Nodo<T>* &arbol, T t, int comparar(T a, T b))
{
    Nodo<T>* p = new Nodo<T>();
    p->info = t;

    if (arbol == NULL)
    {
        arbol = p;
    }
    else
    {
        Nodo<T>* q = arbol;

        while (q->vi != p && q->vd != p)
        {
            if (comparar(p->info, q->info) < 0)
            {
                q->vi == NULL? q->vi = p: q = q->vi;
            }
            else
            {
                q->vd == NULL? q->vd = p: q = q->vd;
            }
        }
    }
    arbol->size++;
    return p;
}

// IN-ORDER
template <typename T> 
void inOrder(Nodo<T>* arbol)
{
    int cont=0;
    Nodo<T>* q = arbol;
    Nodo<T>* ant;
   
    NodoLista<T>* lista = NULL;

    while (cont < arbol->size)
    {
        while (q->vi != NULL || q->vd != NULL)
        {
            ant = q;
            if(q->vi == NULL){ // derecha
                q = q->vd;  
            }
            else{           
                q = q->vi;  // izquierda
            }
        }
        if (q == ant->vd)
        {
            if(!isInLista(lista, q->info)){
                insertarEnLista(lista, q->info);
                ant->vd = NULL;
                cont++;
            }
        }
        else
        {
            if(!isInLista(lista, q->info)){
                insertarEnLista(lista, q->info); 
                cont++;
            }
            insertarEnLista(lista, ant->info);
            ant->vi = NULL; 
            cont++;
        }
        q = arbol;   
    }

    while (lista != NULL)
    {
        NodoLista<T>* x = pop(lista);
        cout << x->info << endl;
    }   
}

// POST-ORDER
template <typename T>
void postOrder(Nodo<T>* arbol) // postOrder
{
    Nodo<T>* q = arbol;
    Nodo<T>* ant;

    NodoLista<T>* lista = NULL;

    while (arbol->vi != NULL || arbol->vd != NULL)
    {
        while (q->vi != NULL || q->vd != NULL)
        {
            ant = q;
            q->vi == NULL? q = q->vd: q = q->vi;
        }

        insertarEnLista(lista, q->info);

        q == ant->vi? ant->vi = NULL: ant->vd = NULL;
        q = arbol;

        arbol->vi == NULL && arbol->vd == NULL? insertarEnLista<T>(lista, arbol->info): lista;
    }

    while (lista != NULL)
    {
        NodoLista<T>* x = pop(lista);
        cout << x->info << endl;
    }   
}

int main(){

    Nodo<int>* arbol = NULL;
    
    const int n = 7;
    int s[n] = {10,6,14,12,20,4,8};
    
    for (int i = 0; i < n; i++)
    {
        insertarArbol<int>(arbol, s[i], comparar<int>);
    }
    
    postOrder<int>(arbol);
    
    return 0;
}

