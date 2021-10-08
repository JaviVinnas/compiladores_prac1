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

//FUNCIONES PRIVADAS

//1º managers: funciones que se comportan como un automata

//2º ommitters: funciones que avanzan una serie de caracteres para pasar de secciones no interesantes del código (comentarios)

//avanza el puntero delantero hasta que llegamos a un retorno de carro
void ommitUntilEndOfLine(SistemaEntrada entrada){
    char c;
    while((c = getChar(entrada)) != '\n'){
        if(c == EOF){
            return;
        } else {
            continue;
        }

}
}


//FUNCIONES PÚBLICAS

AnalizadorLexico crearAnalizadorLexico()
{
    AnalizadorLexico A = (AnalizadorLexico)malloc(sizeof(struct TipoAnalizadorLexico));
    A->estado = Vacio;
    return A;
}

TuplaLexemaId siguienteComponenteLexico(AnalizadorLexico A, SistemaEntrada entrada, TablaSimbolos tablaSimbolos)
{
    TuplaLexemaId tupla;
    char caracter;
    //el estado siempre va a ser vacío
    if(caracter == '#'){

    }
    siguienteCaracter(entrada);
    siguienteCaracter(entrada);
    siguienteCaracter(entrada);
    siguienteCaracter(entrada);
    return crearTupla(charToString(siguienteCaracter(entrada)), EOF);
}

void destruirAnalizadorLexico(AnalizadorLexico A)
{
    free(A);
}
