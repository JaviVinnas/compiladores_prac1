#include <AnalizadorLexico.h>
#include <TuplaLexemaId.h>
#include <SistemaEntrada.h>
#include <TablaSimbolos.h>
#include <Definiciones.h>
#include <Utils.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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

//reconoce docstrings de python (TRES COMILLAS YA LEIDAS)
void reconoceDocString(AnalizadorLexico A, SistemaEntrada entrada, char tipoComilla)
{
    unsigned estado = 0;
    unsigned aceptado = 0;
    while (!aceptado)
    {
        A->caracter = siguienteCaracter(entrada);
        switch (estado)
        {
        case 0: // 3 comillas ya leidas + cero o más cosas que no son comillas
            if (A->caracter == tipoComilla)
                estado = 1;
            break;
        case 1: // 3 comillas + cero o más cosas que no son comillas + 1 comilla
            if (A->caracter == tipoComilla)
                estado = 2; //CORREGIR_ERROR: gestionar error en errores.h si recibimos algo que no son comillas
            break;
        case 2: // 3 comillas + cero o más cosas que no son comillas + 2 comilla
            if (A->caracter == tipoComilla)
                aceptado = 1; //CORREGIR_ERROR: gestionar error en errores.h si recibimos algo que no son comillas
            break;
        }
    }
    lexemaEncontradoSinOutput(entrada);
    A->tupla = crearTupla("DocString", DOCSTRING);
}

//reconoce cadenas de texto entrecomilladas (COMILLA INICIAL YA LEIDA) o bien docstrings si fuera el caso
void reconoceStringLiteral(AnalizadorLexico A, SistemaEntrada entrada, char tipoComilla)
{
    unsigned estado = 0;
    unsigned aceptado = 0;
    while (!aceptado)
    {
        A->caracter = siguienteCaracter(entrada);
        switch (estado)
        {
        case 0: //comilla inicial leida
            if (A->caracter == tipoComilla)
                estado = 1;
            else
                estado = 2;
            break;
        case 1: //comilla inicial + mínimo un caracter que no es la comilla
            if (A->caracter == tipoComilla)
                aceptado = 1; //si llega un caracter tenemos un string literal bien formado
        case 2:               //comilla inicial + comilla inicial
            if (A->caracter == tipoComilla)
            {
                reconoceDocString(A, entrada, tipoComilla); //si llega otra comilla tenemos un docstrings
                return;
            }
            else
            {                              //si no es una comilla es que teníamos una cadena vacía
                devolverCaracter(entrada); //devolvemos el  caracter diferente a la comilla
                aceptado = 1;
            }
            break;
        }
    }
    A->tupla = crearTupla(lexemaEncontrado(entrada), STRING_LITERAL);
}

//reconoce identificadores especiales de python que empiezan por __ (2) y terminan por __ (2) (2 BARRAS BAJAS YA LEIDAS)
void reconoceDunderName(AnalizadorLexico A, SistemaEntrada entrada)
{
    unsigned estado = 0;
    unsigned aceptado = 0;
    while (!aceptado)
    {
        A->caracter = siguienteCaracter(entrada);
        switch (estado)
        {
        case 0: //dos barras bajas leidas
            if (!isalpha(A->caracter) || !isdigit(A->caracter))
                estado = 1;
            break;
        case 1: //dos barras bajas + 1 o más caracter o numero
            if (A->caracter == '_')
                estado = 2;
            break;
        case 2: //dos barras bajas + 1 o más caracter o numero + 1 barra baja
            if (A->caracter != '_')
                estado = 1;
            else
            {
                aceptado = 1;
            }
        }
    }
    A->tupla = crearTupla(lexemaEncontrado(entrada), DUNDER_NAME);
}

//reconoce cadenas que puedan ser identificadores de python (LETRA O _ YA LEIDO)
void reconoceIdentificador(AnalizadorLexico A, SistemaEntrada entrada)
{
    unsigned estado = 0;
    unsigned aceptado = 0;
    while (!aceptado)
    {
        A->caracter = siguienteCaracter(entrada);
        switch (estado)
        {
        case 0: //alfabetico o _ ya leido
            if (A->caracter == '_')
            {
                reconoceDunderName(A, entrada);
                return;
            }
            else if (isalnum(A->caracter))
            {
                estado = 1;
            }
            else
            { //llegamos a otro caracter que no es cadena de texto
                devolverCaracter(entrada);
                aceptado = 1;
            }
            break;
        case 1: //alfabetico o _ + letra o numero (o _)
            if (!isalnum(A->caracter) && A->caracter != '_')
            { //llegamos a otro caracter que no es cadena de texto
                devolverCaracter(entrada);
                aceptado = 1;
            }
        }
    }
    A->tupla = crearTupla(lexemaEncontrado(entrada), IDENTIFICADOR);
}

//reconoce tabulaciones en el código, es decir grupos de 4 espacios seguidos de algo que no es un espacio
//si se reconocen grupos de 1 2 o 3 espacios seguido de algo que no es un espacio se descarta
//(ESPACIO YA LEIDO)
void reconoceTabulacion(AnalizadorLexico A, SistemaEntrada entrada)
{
    unsigned estado = 0;
    unsigned aceptado = 0;
    while (!aceptado)
    {
        A->caracter = siguienteCaracter(entrada);
        switch (estado)
        {
        case 0: //1 espacio leido
            if (A->caracter == ' ')
                estado = 1;
            else
            {
                devolverCaracter(entrada);
                lexemaEncontradoSinOutput(entrada);
                return;
            }
            break;
        case 1: //2 espacios leidos
            if (A->caracter == ' ')
                estado = 2;
            else
            {
                devolverCaracter(entrada);
                lexemaEncontradoSinOutput(entrada);
                return;
            }
            break;
        case 2:                     //3 espacios leidos
            if (A->caracter == ' ') //se lee el cuarto
                aceptado = 1;
            else
            {
                devolverCaracter(entrada);
                lexemaEncontradoSinOutput(entrada);
                return;
            }
        }
    }
    lexemaEncontradoSinOutput(entrada);
    A->tupla = crearTupla("Tabulacion", TABULACION);
}

//reconoce cadenas que puedan ser enteros de python (1 DIGITO YA LEIDO)
void reconoceEntero(AnalizadorLexico A, SistemaEntrada entrada, unsigned firstIsZero)
{
    unsigned estado = firstIsZero;
    unsigned aceptado = 0;
    while (!aceptado)
    {
        A->caracter = siguienteCaracter(entrada);
        switch (estado)
        {
        case 0: //0 leido
            if(A->caracter == '0')
                estado = 2;
            else if (A->caracter == 'B' || A->caracter == 'b')
                estado = 3;
            else if (A->caracter == 'O' || A->caracter == 'o')
                estado = 4;
            else if (A->caracter == 'X' || A->caracter == 'x')
                estado = 5;
            else //siguiente cadena
            {
                devolverCaracter(entrada);
                lexemaEncontradoSinOutput(entrada);
                return;
            }
            break;
        case 1: //número distinto de cero leido
            if (A->caracter == '_')
                estado = 6;
            else if (!isdigit(A->caracter) && A->caracter != '_')
            {
                devolverCaracter(entrada);
                aceptado = 1;
            }
            break;
        case 2: //recibido ceros sin 
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        }
    }
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
    while (A->tupla == NULL)
    { //mientras no tengamos una tupla formada (habríamos encontrado un lexema) iteramos
        A->caracter = siguienteCaracter(entrada);
        //jerarquía para ordenar los if's [1>2>3>4...]
        //  1 -> caracteres normales
        //  2 -> caracteres de escape
        //  3 -> evaluaciones complejas
        //para cada nivel una jerarquia [a>b>c>d...]
        //  a -> sin automatas (se crea la tupla directamente usando como nombre el símbolo)
        //  b -> sin autómatas (se crea la tupla directamente usando un nombre de tupla diferente al símbolo)
        //  c -> con automatas (el automata crea la tupla)
        if (A->caracter == '.' ||
            A->caracter == '=' ||
            A->caracter == '(' ||
            A->caracter == ')' ||
            A->caracter == '{' ||
            A->caracter == '}' ||
            A->caracter == ',')
        {
            char *monoCharString = lexemaEncontrado(entrada);
            A->tupla = crearTupla(monoCharString, (int)monoCharString[0]);
        }
        else if (A->caracter == ' ')
        {
            reconoceTabulacion(A, entrada);
        }
        else if (A->caracter == '#')
        {
            reconoceComentario(A, entrada);
        }
        else if (A->caracter == '_')
        {
            reconoceComentario(A, entrada);
        }

        else if (A->caracter == '\n')
        {
            lexemaEncontradoSinOutput(entrada);
            A->tupla = crearTupla("Retorno de carro", (int)'\n');
        }
        else if (A->caracter == '\'' || A->caracter == '\"')
        {
            reconoceStringLiteral(A, entrada, A->caracter);
        }
        else if (isalpha(A->caracter) || (A->caracter == '_'))
        {
            reconoceIdentificador(A, entrada);
            //TODO: debemos chequear la tabla de símbolos
        }
        else if (isdigit(A->caracter))
        {
            reconoceEntero(A, entrada, A->caracter == '0');
        }
    }
    return A->tupla;
}

void destruirAnalizadorLexico(AnalizadorLexico A)
{
    free(A);
}
