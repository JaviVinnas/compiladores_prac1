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

typedef enum EstadoAutomata
{
    Aceptado,
    Rechazado,
    Final,
} NombreBloque;

struct TipoAnalizadorLexico
{
    TuplaLexemaId tupla;
    char caracter;
};

//--------------------------------------------------------------------------------------------------
//FUNCIONES PRIVADAS

// --Autómatas--
// devolveran NULL si IGNORAN EL LEXEMA RECONOCIDO
// devolverán un puntero a chra con el lexema si GUARDAN EL LEXEMA RECONOCIDO
// depende de ellos retrasar el sistema de entrada una posición si son del tipo de automatas que reconoce un elemento en el caracter siguiente al final del lexema

//reconoce los cometarios monolínea ( "#" YA LEIDO)
void reconoceComentario(AnalizadorLexico A, SistemaEntrada entrada)
{
    unsigned estado = 0;
    unsigned aceptado = 0;
    while (!aceptado)
    {
        A->caracter = siguienteCaracter(entrada);
        switch (estado)
        {
        case 0: //# + cero o más cosas por en medio reconocidas
            if (A->caracter == '\n')
                aceptado = 1;
            break;
        }
    }
    lexemaEncontradoSinOutput(entrada);
}

//reconoce cadenas de texto entrecomilladas (COMILLA INICIAL YA LEIDA) o bien docstrings si fuera el caso
void reconoceStringLiteral(AnalizadorLexico A, SistemaEntrada entrada, char tipoComilla)
{
    unsigned estado = 1;
    unsigned aceptado = 0;
    while (!aceptado)
    {
        A->caracter = siguienteCaracter(entrada);
        switch (estado)
        {
        case 1: // comilla inicial leída
            if (A->caracter != tipoComilla)
                estado = 2;
            else
                estado = 3;
            break;
        case 2: //comilla y cero o más cosas leidas
            if (A->caracter == tipoComilla)
                aceptado = 1;
            break;
        case 3: //dos comillas leídas unicamente
            if (A->caracter == tipoComilla)
                estado = 4;
        case 4: //tres comillas leídas unicamente
            if (A->caracter == '\n')
            {
                reconoceDocString(A, entrada, tipoComilla);
                return;
            }
            else
            {
                devolverCaracter(entrada); //devolvemos \n
                devolverCaracter(entrada); //devolvemos la tercera comilla
                devolverCaracter(entrada); //devolvemos la segunda comilla
                estado = 2;
            }
            //evaluaría la segunda comilla y aceptaría
            break;
        }
    }
    A->tupla = crearTupla(lexemaEncontrado(entrada), STRING_LITERAL);
}

//reconoce docstrings de python (TRES COMILLAS Y RETORNO DE CARRO YA LEIDOS)
void reconoceDocString(AnalizadorLexico A, SistemaEntrada entrada, char tipoComilla)
{
    unsigned estado = 0;
    unsigned aceptado = 0;
    while (!aceptado)
    {
        A->caracter = siguienteCaracter(entrada);
        switch (estado)
        {
        case 0: // 3 comillas + retorno de carro ya leidos
            if (A->caracter != tipoComilla || A->caracter != '\n')
                estado = 1;
            break;
        case 1: //  3 comillas + retorno de carro ya leidos + al menos un caracter
            if (A->caracter == '\n')
                estado = 2;
            break;
        case 2: //  3 comillas + retorno de carro ya leidos + al menos un caracter + retorno de carro
            if (A->caracter == tipoComilla)
                estado = 3;
            break;
        case 3: //  3 comillas + retorno de carro ya leidos + al menos un caracter + retorno de carro + 1 comilla
            if (A->caracter == tipoComilla)
                estado = 4;
            break;
        case 4: //  3 comillas + retorno de carro ya leidos + al menos un caracter + retorno de carro + 2 comilla
            if (A->caracter == tipoComilla)
                aceptado = 1;
            break;
        }
    }
    A->tupla = crearTupla(lexemaEncontrado(entrada), DOCSTRING);
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
            reconoceStringLiteral(A, entrada, '\'');
            break;
        case '\"':
            reconoceStringLiteral(A, entrada, '\'');
        }
    }
    return A->tupla;
}

void destruirAnalizadorLexico(AnalizadorLexico A)
{
    free(A);
}
