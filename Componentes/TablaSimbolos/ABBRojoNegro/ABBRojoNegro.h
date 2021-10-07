#ifndef RED_BLACK_ABB
#define RED_BLACK_ABB

#include <TuplaLexemaId.h>

typedef TuplaLexemaId ContenidoNodo; //es una arbol rojo-negro de punteros a tuplas lexema-id
#define NegInfinity (-10000)

struct NodoRojoNegro;
typedef struct NodoRojoNegro *Posicion;
typedef struct NodoRojoNegro *ABBRojoNegro;

ABBRojoNegro vaciarABBRojoNegro(ABBRojoNegro T);
Posicion buscar(ContenidoNodo X, ABBRojoNegro T);
Posicion buscar_minimo(ABBRojoNegro T);
Posicion buscar_maximo(ABBRojoNegro T);
ABBRojoNegro crearABBRojoNegro(void);
ABBRojoNegro insertarABBRojoNegro(ContenidoNodo X, ABBRojoNegro T);
ABBRojoNegro eliminar(ContenidoNodo X, ABBRojoNegro T);
ContenidoNodo obtener_contenido(Posicion P);
void imprimirABBRojoNegro(ABBRojoNegro T);

#endif // RED_BLACK_ABB