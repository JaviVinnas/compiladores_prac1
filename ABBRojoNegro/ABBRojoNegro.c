#include "ABBRojoNegro.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum ColorType
{
    Red,
    Black
} ColorType;

struct NodoRojoNegro
{
    ContenidoNodo Element;
    ABBRojoNegro Left;
    ABBRojoNegro Right;
    ColorType Color;
};

static Posicion NullNode = NULL; /* Needs initialization */

/* Initialization procedure */
ABBRojoNegro inicializar(void)
{
    ABBRojoNegro T;

    if (NullNode == NULL)
    {
        NullNode = malloc(sizeof(struct NodoRojoNegro));
        if (NullNode == NULL)
            printf("Out of space!!!");
        NullNode->Left = NullNode->Right = NullNode;
        NullNode->Color = Black;
        NullNode->Element = 12345;
    }

    /* Create the header node */
    T = malloc(sizeof(struct NodoRojoNegro));
    if (T == NULL)
        printf("Out of space!!!");
    T->Element = NegInfinity;
    T->Left = T->Right = NullNode;
    T->Color = Black;

    return T;
}

/* END */

void Output(ContenidoNodo Element)
{
    printf("%d\n", Element);
}

/* Print the tree, watch out for NullNode, */

/* and skip header */

static void
DoPrint(ABBRojoNegro T)
{
    if (T != NullNode)
    {
        DoPrint(T->Left);
        Output(T->Element);
        DoPrint(T->Right);
    }
}

void imprimir_arbol(ABBRojoNegro T)
{
    DoPrint(T->Right);
}

/* END */

static ABBRojoNegro
MakeEmptyRec(ABBRojoNegro T)
{
    if (T != NullNode)
    {
        MakeEmptyRec(T->Left);
        MakeEmptyRec(T->Right);
        free(T);
    }
    return NullNode;
}

ABBRojoNegro
vaciar(ABBRojoNegro T)
{
    T->Right = MakeEmptyRec(T->Right);
    return T;
}

Posicion
buscar(ContenidoNodo X, ABBRojoNegro T)
{
    if (T == NullNode)
        return NullNode;
    if (X < T->Element)
        return buscar(X, T->Left);
    else if (X > T->Element)
        return buscar(X, T->Right);
    else
        return T;
}

Posicion
buscar_minimo(ABBRojoNegro T)
{
    T = T->Right;
    while (T->Left != NullNode)
        T = T->Left;

    return T;
}

Posicion
buscar_maximo(ABBRojoNegro T)
{
    while (T->Right != NullNode)
        T = T->Right;

    return T;
}

/* This function can be called only if K2 has a left child */
/* Perform a rotate between a node (K2) and its left child */

/* Update heights, then return new root */

static Posicion
SingleRotateWithLeft(Posicion K2)
{
    Posicion K1;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    return K1; /* New root */
}

/* This function can be called only if K1 has a right child */
/* Perform a rotate between a node (K1) and its right child */

/* Update heights, then return new root */

static Posicion
SingleRotateWithRight(Posicion K1)
{
    Posicion K2;

    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;

    return K2; /* New root */
}

/* Perform a rotation at node X */
/* (whose parent is passed as a parameter) */

/* The child is deduced by examining Item */

static Posicion
Rotate(ContenidoNodo Item, Posicion Parent)
{

    if (Item < Parent->Element)
        return Parent->Left = Item < Parent->Left->Element ? SingleRotateWithLeft(Parent->Left) : SingleRotateWithRight(Parent->Left);
    else
        return Parent->Right = Item < Parent->Right->Element ? SingleRotateWithLeft(Parent->Right) : SingleRotateWithRight(Parent->Right);
}

static Posicion X, P, GP, GGP;

static void HandleReorient(ContenidoNodo Item, ABBRojoNegro T)
{
    X->Color = Red; /* Do the color flip */
    X->Left->Color = Black;
    X->Right->Color = Black;

    if (P->Color == Red) /* Have to rotate */
    {
        GP->Color = Red;
        if ((Item < GP->Element) != (Item < P->Element))
            P = Rotate(Item, GP); /* Start double rotate */
        X = Rotate(Item, GGP);
        X->Color = Black;
    }
    T->Right->Color = Black; /* Make root black */
}

ABBRojoNegro
insertar(ContenidoNodo Item, ABBRojoNegro T)
{
    X = P = GP = T;
    NullNode->Element = Item;
    while (X->Element != Item) /* Descend down the tree */
    {
        GGP = GP;
        GP = P;
        P = X;
        if (Item < X->Element)
            X = X->Left;
        else
            X = X->Right;
        if (X->Left->Color == Red && X->Right->Color == Red)
            HandleReorient(Item, T);
    }

    if (X != NullNode)
        return NullNode; /* Duplicate */

    X = malloc(sizeof(struct NodoRojoNegro));
    if (X == NULL)
        printf("Out of space!!!");
    X->Element = Item;
    X->Left = X->Right = NullNode;

    if (Item < P->Element) /* Attach to its parent */
        P->Left = X;
    else
        P->Right = X;
    HandleReorient(Item, T); /* Color it red; maybe rotate */

    return T;
}

ABBRojoNegro
eliminar(ContenidoNodo Item, ABBRojoNegro T)
{
    printf("Remove is unimplemented\n");
    if (Item)
        return T;
    return T;
}

ContenidoNodo
obtener_contenido(Posicion P)
{
    return P->Element;
}