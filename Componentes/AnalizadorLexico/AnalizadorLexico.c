#include <AnalizadorLexico.h>
#include <TuplaLexemaId.h>
#include <SistemaEntrada.h>
#include <TablaSimbolos.h>
#include <Definiciones.h>
#include <Utils.h>
#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------------------------------------------------------
//TIPOS DE DATOS

struct TipoAnalizadorLexico
{
    TuplaLexemaId tupla;
    char caracter;
    unsigned estado;
    unsigned aceptado;
};

//--------------------------------------------------------------------------------------------------
//FUNCIONES PRIVADAS

// --Autómatas--
// devolveran NULL si IGNORAN EL LEXEMA RECONOCIDO
// devolverán un puntero a chra con el lexema si GUARDAN EL LEXEMA RECONOCIDO
// depende de ellos retrasar el sistema de entrada una posición si son del tipo de automatas que reconoce un elemento en el caracter siguiente al final del lexema

//TODO: reconocer las declaraciones de codificación

//reconoce los cometarios monolínea ( "#" ya leido)
void reconoceComentario(AnalizadorLexico A, SistemaEntrada entrada)
{
    A->estado = 1;
    A->aceptado = 0;
    while (!A->aceptado)
    {
        A->caracter = siguienteCaracter(entrada);
        switch (A->estado)
        {
        case 0: //aun no reconocido nada
            if (A->caracter == '#')
                A->estado = 1;
            break;
        case 1: //# + cero o más cosas por en medio reconocidas
            if (A->caracter == '\n')
                A->estado = 2;
            break;
        case 2: //# + cero o más cosas por en medio + \n reconocido
            A->aceptado = 1;
            break;
        }
    }
    lexemaEncontradoSinOutput(entrada);
}

//reconoce cadenas de texto entrecomilladas con comillas simples ( ' ya leido)
char *reconoceStringEntrecomilladoSimple(AnalizadorLexico A, SistemaEntrada entrada)
{
    A->estado = 1;
    A->aceptado = 0;
    while (!A->aceptado)
    {
        A->caracter = siguienteCaracter(entrada);
        switch (A->estado)
        {
        case 0: // ' aún no leido
            if (A->caracter == '\'')
                A->estado = 1;
            break;
        case 1: // ' + cero o más cosas por en medio reconocidas
            if (A->caracter == '\'')
                A->estado = 2;
            break;
        case 2: // ' + otras cosa por en medio + ' reconocido -> estado final
            A->aceptado = 1;
        }
    }
    return lexemaEncontrado(entrada);
}

void reconoceStringEntrecomilladoDoble(AnalizadorLexico A, SistemaEntrada entrada)
{
    A->estado = 1;
    A->aceptado = 0;
    while (!A->aceptado)
    {
        A->caracter = siguienteCaracter(entrada);
        switch (A->estado)
        {
        case 0: // ' aún no leido
            if (A->caracter == '\"')
                A->estado = 1;
            break;
        case 1: // ' + cero o más cosas por en medio reconocidas
            if (A->caracter == '\"')
                A->estado = 2;
            break;
        case 2: // ' + otras cosa por en medio + ' reconocido -> estado final
            A->aceptado = 1;
        default:
            break;
        }
    }
    return lexemaEncontrado(entrada);
}

//--------------------------------------------------------------------------------------------------
//FUNCIONES PÚBLICAS

AnalizadorLexico crearAnalizadorLexico()
{
    //TODO: dejar por ahora pero eliminar si al final no se acaba usanndo
    return malloc(sizeof(struct TipoAnalizadorLexico));
}

TuplaLexemaId siguienteComponenteLexico(AnalizadorLexico A, SistemaEntrada entrada, TablaSimbolos tablaSimbolos)
{
    A->tupla = NULL;
    //obtenemos el caracter que toque según el sistema de entrada
    char caracter = siguienteCaracter(entrada);
    while (A->tupla == NULL)
    { //mientras no tengamos una tupla formada (habríamos encontrado un lexema) iteramos
        switch (caracter)
        {
        case '#':
            reconoceComentario(A, entrada);
            break;
        case '\'':
            reconoceStringEntrecomilladoSimple(A, entrada);

            break;
        case '\t':
            break;
        }
    }
}

void destruirAnalizadorLexico(AnalizadorLexico A)
{
    free(A);
}
