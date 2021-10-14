#ifndef RED_BLACK_ABB
#define RED_BLACK_ABB

#include <TuplaLexemaId.h>

typedef TuplaLexemaId ContenidoNodo; //es una arbol rojo-negro de punteros a tuplas lexema-id
#define NegInfinity (-10000)

struct NodoRojoNegro;
typedef struct NodoRojoNegro *Posicion;
typedef struct NodoRojoNegro *ABBRojoNegro;

//destruye el árbol nodo a nodo recursivamente
ABBRojoNegro vaciarABBRojoNegro(ABBRojoNegro T);
//devuelve el nodo del árbol que contiene la tupla con el lexema pasado por parámetros
Posicion buscarABBRojoNegro(Lexema lexema, ABBRojoNegro T);
//reserva memoria para el nodo raíz del árbol y lo devuelve
ABBRojoNegro crearABBRojoNegro(void);
//inserta una tupla en el árbol si esta no está todavía. Si no genera un nodo nuevo donde se alojará y lo sitúa en el árbol balanceándolo si fuera preciso
ABBRojoNegro insertarABBRojoNegro(ContenidoNodo X, ABBRojoNegro T);
//a partir de un nodo del árbol obtiene su contenido, ya que es un tipo opaco
ContenidoNodo obtenerContenidoPosicionABBRojoNegro(Posicion P);
//muestra por la terminal el contenido de un árbol pasado por parámetros de forma recursiva
void imprimirABBRojoNegro(ABBRojoNegro T);

#endif // RED_BLACK_ABB