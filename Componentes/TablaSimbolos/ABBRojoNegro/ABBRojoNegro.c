#include <ABBRojoNegro.h>
#include <TuplaLexemaId.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum TipoColor
{
    Rojo,
    Negro
} TipoColor;

struct NodoRojoNegro
{
    ContenidoNodo contenido;
    ABBRojoNegro izq;
    ABBRojoNegro der;
    TipoColor color;
};

static Posicion NodoNulo = NULL; //necesita inicialización -> nodo que actua de nulo y que estará en las hojas

/* Initialization procedure */
ABBRojoNegro crearABBRojoNegro(void)
{
    ABBRojoNegro T;

    if (NodoNulo == NULL)
    {
        NodoNulo = malloc(sizeof(struct NodoRojoNegro));
        if (NodoNulo == NULL)
            printf("Out of space!!!");
        NodoNulo->izq = NodoNulo->der = NodoNulo; //se tiene a si mismo como contenido (fin del arbol)
        NodoNulo->color = Negro;                  //siempre negro como la raiz
        NodoNulo->contenido = crearTupla(NULL, 123);
    }

    //se crea el nodo raiz del árbol
    T = malloc(sizeof(struct NodoRojoNegro));
    if (T == NULL)
        printf("Out of space!!!");
    T->contenido = crearTupla("    ", NegInfinity);
    T->izq = T->der = NodoNulo;
    T->color = Negro; //raiz siempre negra

    return T;
}

/* END */

void Output(ContenidoNodo contenido)
{
    printTupla(contenido);
}

/* Print the tree, watch out for NodoNulo, */

/* and skip header */

static void DoPrint(ABBRojoNegro T)
{
    if (T != NodoNulo)
    {
        DoPrint(T->izq);
        Output(T->contenido);
        DoPrint(T->der);
    }
}

void imprimirABBRojoNegro(ABBRojoNegro T)
{
    DoPrint(T->der);
}

/* END */

static ABBRojoNegro MakeEmptyRec(ABBRojoNegro T)
{
    if (T != NodoNulo)
    {
        MakeEmptyRec(T->izq);
        MakeEmptyRec(T->der);
        destruirTupla(T->contenido);
        free(T);
    }
    return NodoNulo;
}

ABBRojoNegro vaciarABBRojoNegro(ABBRojoNegro T)
{
    T->der = MakeEmptyRec(T->der);
    T->izq = MakeEmptyRec(T->izq);
    destruirTupla(T->contenido);
    free(T);
    return NULL;
}

Posicion buscarABBRojoNegro(Lexema lexema, ABBRojoNegro T)
{
    if (T == NodoNulo)
        return NULL;
    //buscamos y ordenamos por el lexema
    if (strcmp(lexema, getTuplaLexema(T->contenido)) < 0) //si es menor
        return buscarABBRojoNegro(lexema, T->izq);
    else if (strcmp(lexema, getTuplaLexema(T->contenido)) > 0) //si es mayor
        return buscarABBRojoNegro(lexema, T->der);
    else //si son iguales
        return T;
}

Posicion buscar_minimo(ABBRojoNegro T)
{
    T = T->der;
    while (T->izq != NodoNulo)
        T = T->izq;

    return T;
}

Posicion buscar_maximo(ABBRojoNegro T)
{
    while (T->der != NodoNulo)
        T = T->der;

    return T;
}

/* This function can be called only if K2 has a left child */
/* Perform a rotate between a node (K2) and its left child */

/* Update heights, then return new root */

static Posicion SingleRotateWithLeft(Posicion K2)
{
    Posicion K1;

    K1 = K2->izq;
    K2->izq = K1->der;
    K1->der = K2;

    return K1; /* New root */
}

/* This function can be called only if K1 has a right child */
/* Perform a rotate between a node (K1) and its right child */

/* Update heights, then return new root */

static Posicion SingleRotateWithRight(Posicion K1)
{
    Posicion K2;

    K2 = K1->der;
    K1->der = K2->izq;
    K2->izq = K1;

    return K2; /* New root */
}

/* Perform a rotation at node X */
/* (whose parent is passed as a parameter) */

/* The child is deduced by examining Item */

static Posicion Rotate(ContenidoNodo Item, Posicion Parent)
{
    if (compareTuplas(Item, Parent->contenido) < 0)
        return Parent->izq = compareTuplas(Item, Parent->izq->contenido) < 0 ? SingleRotateWithLeft(Parent->izq) : SingleRotateWithRight(Parent->izq);
    else
        return Parent->der = compareTuplas(Item, Parent->der->contenido) < 0 ? SingleRotateWithLeft(Parent->der) : SingleRotateWithRight(Parent->der);
}

static Posicion X, P, GP, GGP;

static void HandleReorient(ContenidoNodo Item, ABBRojoNegro T)
{
    X->color = Rojo; /* Do the color flip */
    X->izq->color = Negro;
    X->der->color = Negro;

    if (P->color == Rojo) /* Have to rotate */
    {
        GP->color = Rojo;
        if ((compareTuplas(Item, GP->contenido) < 0) != (compareTuplas(Item, P->contenido) < 0))
            P = Rotate(Item, GP); /* Start double rotate */
        X = Rotate(Item, GGP);
        X->color = Negro;
    }
    T->der->color = Negro; /* Make root black */
}

ABBRojoNegro insertarABBRojoNegro(ContenidoNodo Item, ABBRojoNegro T)
{
    X = P = GP = T;
    NodoNulo->contenido = Item;
    while (compareTuplas(X->contenido, Item) != 0) /* Descend down the tree */
    {
        GGP = GP;
        GP = P;
        P = X;
        if (compareTuplas(Item, X->contenido) < 0)
            X = X->izq;
        else
            X = X->der;
        if (X->izq->color == Rojo && X->der->color == Rojo)
            HandleReorient(Item, T);
    }

    if (X != NodoNulo)
        return NodoNulo; /* Duplicate */

    X = malloc(sizeof(struct NodoRojoNegro));
    if (X == NULL)
        printf("Out of space!!!");
    X->contenido = Item;
    X->izq = X->der = NodoNulo;

    if (compareTuplas(Item, P->contenido) < 0) //si la tupla hija es menor que la tupla padre va a la izquierda (nunca cuando insertamos la primera vez)
        P->izq = X;
    else
        P->der = X;
    HandleReorient(Item, T); /* color it red; maybe rotate */

    return T;
}

ABBRojoNegro eliminar(ContenidoNodo Item, ABBRojoNegro T)
{
    printf("Remove is unimplemented\n");
    if (Item)
        return T;
    return T;
}

ContenidoNodo obtenerContenidoPosicionABBRojoNegro(Posicion P)
{
    return P->contenido;
}