#ifndef TABLA_SIMBOLOS_H
#define TABLA_SIMBOLOS_H
#include <TuplaLexemaId.h>

struct TipoTablaSimbolos;
typedef struct TipoTablaSimbolos *TablaSimbolos;

//crea una tabla de símbolos con las palabras clave de wilcoxon.py
TablaSimbolos crearTablaSimbolos();
//imprime por el terminal el contenido de los nodos de la tabla de símbolos
void imprimirTablaSimbolos(TablaSimbolos T);
//libera la memoria de la tabla de símbolos
void destruirTablaSimbolos(TablaSimbolos T);
//busca un identificador en la tabla de símbolos
//si estuviera lo devuelve (pudiendo ser una palabra reservada)
//si no estuviera genera una tupla con ese lexema y componente léxico IDENTIFICADOR lo introduce en el árbol y lo devuelve
TuplaLexemaId buscarIdEnTablaSimbolos(TablaSimbolos T, Lexema identificador);

#endif //TABLA_SIMBOLOS_H