#ifndef TABLA_SIMBOLOS_H
#define TABLA_SIMBOLOS_H

struct TipoTablaSimbolos;
typedef struct TipoTablaSimbolos *TablaSimbolos;

//crea una tabla de símbolos con las palabras clave de wilcoxon.py
TablaSimbolos crearTablaSimbolos();
//imprime por el terminal el contenido de los nodos de la tabla de símbolos
void imprimirTablaSimbolos(TablaSimbolos T);
//libera la memoria de la tabla de símbolos
void destruirTablaSimbolos(TablaSimbolos T);

#endif //TABLA_SIMBOLOS_H