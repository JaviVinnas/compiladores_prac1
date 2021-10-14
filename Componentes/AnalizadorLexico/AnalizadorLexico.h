#ifndef ANALIZADOR_LEXICO_H
#define ANALIZADOR_LEXICO_H

#include <TuplaLexemaId.h>
#include <SistemaEntrada.h>
#include <TablaSimbolos.h>

struct TipoAnalizadorLexico;
typedef struct TipoAnalizadorLexico *AnalizadorLexico;

AnalizadorLexico crearAnalizadorLexico();

/**
 * Obtiene el siguiente componente léxico del sistema de entrada (que se le pase por argumentos)
 * usando la tabla de símbolos (que se le pase por argumentos). Devuelve una referencia a una tupla.
 * */
TuplaLexemaId siguienteComponenteLexico(AnalizadorLexico A, SistemaEntrada entrada, TablaSimbolos tablaSimbolos);

//Destruye el analizador lexico y libera la memoria
void destruirAnalizadorLexico(AnalizadorLexico A);

#endif // ANALIZADOR_LEXICO_H