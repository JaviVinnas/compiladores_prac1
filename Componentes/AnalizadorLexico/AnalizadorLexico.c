#include <AnalizadorLexico.h>
#include <TuplaLexemaId.h>
#include <SistemaEntrada.h>
#include <TablaSimbolos.h>
#include <Definiciones.h>
#include <Utils.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum TipoEstado
{
    Vacio,
    LeyendoInt,
    LeyendoFloat,
    LeyendoAlfanumerico,
} TipoEstado;

struct TipoAnalizadorLexico
{
    TipoEstado estado;
};

AnalizadorLexico crearAnalizadorLexico()
{
    AnalizadorLexico A = (AnalizadorLexico)malloc(sizeof(struct TipoAnalizadorLexico));
    A->estado = Vacio;
    return A;
}

TuplaLexemaId siguienteComponenteLexico(AnalizadorLexico A, SistemaEntrada entrada, TablaSimbolos tablaSimbolos)
{
    siguienteCaracter(entrada);
    siguienteCaracter(entrada);
    siguienteCaracter(entrada);
    siguienteCaracter(entrada);
    return crearTupla(charToString(siguienteCaracter(entrada)), END_OF_FILE);
}

void destruirAnalizadorLexico(AnalizadorLexico A)
{
    free(A);
}
