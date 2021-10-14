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
// TIPOS DE DATOS

struct TipoAnalizadorLexico
{
    TuplaLexemaId tupla;
    char caracter;
};

//--------------------------------------------------------------------------------------------------
// FUNCIONES PRIVADAS

// --Autómatas--
// depende de ellos retrasar el sistema de entrada una posición si son del tipo de automatas que reconoce un elemento en el caracter siguiente al final del lexema
// pese a que en muchos casos se pueden implementar de una forma más sencilla preferí mantener la estructura de autómata en todas las funciones para una mejor comprensión

// reconoce los cometarios monolínea ( "#" YA LEIDO)
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
            {
                devolverCaracter(entrada);
                aceptado = 1;
            }
            break;
        }
    }
    lexemaEncontradoSinOutput(entrada);
}

// reconoce docstrings de python (TRES COMILLAS YA LEIDAS)
void reconoceDocString(AnalizadorLexico A, SistemaEntrada entrada, char tipoComilla)
{
    unsigned estado = 0;
    unsigned aceptado = 0;
    while (!aceptado)
    {
        A->caracter = siguienteCaracter(entrada);
        switch (estado)
        {
        case 0: // {comilla}{comilla}{comilla}{cosas distinta de comilla}+
            if (A->caracter == tipoComilla)
                estado = 1;
            break;
        case 1: // {comilla}{comilla}{comilla}{cosas distinta de comilla}+{comilla}
            if (A->caracter == tipoComilla)
                estado = 2; // CORREGIR_ERROR: gestionar error en errores.h si recibimos algo que no son comillas
            break;
        case 2: // {comilla}{comilla}{comilla}{cosas distinta de comilla}+{comilla}{comilla}
            if (A->caracter == tipoComilla)
                aceptado = 1; // CORREGIR_ERROR: gestionar error en errores.h si recibimos algo que no son comillas
            break;
        }
    }
    lexemaEncontradoSinOutput(entrada);
    A->tupla = crearTupla("DocString", DOCSTRING);
}

// reconoce cadenas de texto entrecomilladas (COMILLA INICIAL YA LEIDA) o bien docstrings si fuera el caso
void reconoceStringLiteral(AnalizadorLexico A, SistemaEntrada entrada, char tipoComilla)
{
    unsigned estado = 0;
    unsigned aceptado = 0;
    while (!aceptado)
    {
        A->caracter = siguienteCaracter(entrada);
        switch (estado)
        {
        case 0: //{comilla}
            if (A->caracter == tipoComilla)
                estado = 1;
            else
                estado = 2;
            break;
        case 1: //{comilla}{comilla}
            if (A->caracter == tipoComilla)
            {
                reconoceDocString(A, entrada, tipoComilla);
                return;
            }
            else
            {
                devolverCaracter(entrada);
                aceptado = 1;
            }
            break;
        case 2: //{comilla}{cosa distinta de comilla}+
            if (A->caracter == tipoComilla)
                aceptado = 1;
        }
    }
    A->tupla = crearTupla(lexemaEncontrado(entrada), STRING_LITERAL);
}

// reconoce identificadores especiales de python que empiezan por __ (2) y terminan por __ (2) (1 BARRA BAJA YA LEIDA)
void reconoceDunderName(AnalizadorLexico A, SistemaEntrada entrada)
{
    unsigned estado = 0;
    unsigned aceptado = 0;
    while (!aceptado)
    {
        A->caracter = siguienteCaracter(entrada);
        switch (estado)
        {
        case 0: //_ leido
            if (A->caracter == '_')
                estado = 1;
            break;
        case 1: //__(caracter | numero | _)+
            if (A->caracter == '_')
                estado = 2;
            break;
        case 2: //__(caracter | numero | _)+_
            if (A->caracter == '_')
                aceptado = 1;
            else
                estado = 1;
        }
    }
    A->tupla = crearTupla(lexemaEncontrado(entrada), DUNDER_NAME);
}

// reconoce cadenas que puedan ser identificadores de python (1 LETRA YA LEIDA)
void reconoceIdentificador(AnalizadorLexico A, SistemaEntrada entrada, TablaSimbolos tablaSimbolos)
{
    unsigned estado = 0;
    unsigned aceptado = 0;
    while (!aceptado)
    {
        A->caracter = siguienteCaracter(entrada);
        switch (estado)
        {
        case 0: //[letra|_]+ leida
            if (!isalnum(A->caracter) && A->caracter != '_')
            {
                devolverCaracter(entrada);
                aceptado = 1;
            }
        }
    }
    A->tupla = buscarIdEnTablaSimbolos(tablaSimbolos, lexemaEncontrado(entrada));
}

// reconoce tabulaciones en el código, es decir grupos de 4 espacios seguidos de algo que no es un espacio
// si se reconocen grupos de 1 2 o 3 espacios seguido de algo que no es un espacio se descarta
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
        case 0: // 1 espacio leido
            if (A->caracter == ' ')
                estado = 1;
            else
            {
                devolverCaracter(entrada);
                lexemaEncontradoSinOutput(entrada);
                return;
            }
            break;
        case 1: // 2 espacios leidos
            if (A->caracter == ' ')
                estado = 2;
            else
            {
                devolverCaracter(entrada);
                lexemaEncontradoSinOutput(entrada);
                return;
            }
            break;
        case 2:                     // 3 espacios leidos
            if (A->caracter == ' ') // se lee el cuarto
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

// reconoce cadenas que puedan ser float en python
// puede ser que lleguemos con => .[0-9]  YA LEIDO => estado 0
// puede ser que lleguemos con => [0-9]+. YA LEIDO => estado 1
// puede ser que lleguemos con => [0-9]+(e|E) YA LEIDO => estado 2
void reconocePuntoFlotante(AnalizadorLexico A, SistemaEntrada entrada, unsigned estadoInicial)
{
    unsigned estado = estadoInicial;
    unsigned aceptado = 0;
    while (!aceptado)
    {
        A->caracter = siguienteCaracter(entrada);
        switch (estado)
        {
        case 0: //.[0-9]+ leido
            if (A->caracter == 'E' || A->caracter == 'e')
                estado = 2;
            else if (!isdigit(A->caracter))
            {
                devolverCaracter(entrada);
                aceptado = 1;
            }
            break;
        case 1: //[0-9]+. leido
            if (isdigit(A->caracter))
                estado = 0;
            else
            {
                devolverCaracter(entrada);
                aceptado = 1;
            }
            break;
        case 2: //{parteNoExponencial}(e|E) leido
            if (A->caracter == '+' || A->caracter == '-')
                estado = 3;
            else if (isdigit(A->caracter))
                estado = 4;
            break;
        case 3: //{parteNoExponencial}(e|E)(+|-) leido
            if (isdigit(A->caracter))
                estado = 4;
            break;
        case 4: //{parteNoExponencial}(e|E)(+|-)?[0-9]+ leido
            if (!isdigit(A->caracter))
            {
                devolverCaracter(entrada);
                aceptado = 1;
            }
            break;
        }
    }
    A->tupla = crearTupla(lexemaEncontrado(entrada), FLOAT);
}

// reconoce cadenas que puedan ser enteros de python (1 DIGITO YA LEIDO)
void reconoceEntero(AnalizadorLexico A, SistemaEntrada entrada, unsigned firstIsZero)
{
    unsigned estado = firstIsZero;
    unsigned aceptado = 0;
    while (!aceptado)
    {
        A->caracter = siguienteCaracter(entrada);
        switch (estado)
        {
        case 0: //[1-9]+ leído
            if (A->caracter == '.')
            {
                reconocePuntoFlotante(A, entrada, 1);
                return;
            }
            else if (A->caracter == 'E' || A->caracter == 'e')
            {
                reconocePuntoFlotante(A, entrada, 2);
                return;
            }
            else if (!isdigit(A->caracter))
            {
                devolverCaracter(entrada);
                aceptado = 1;
            }
            break;
        case 1: // 0 leído
            if (A->caracter == '.')
            {
                reconocePuntoFlotante(A, entrada, 1);
                return;
            }
            else if (A->caracter == 'E' || A->caracter == 'e')
            {
                reconocePuntoFlotante(A, entrada, 2);
                return;
            }
            else if (A->caracter == 'x' || A->caracter == 'X')
            {
                estado = 2;
            }
            else if (A->caracter != '0')
            {
                devolverCaracter(entrada);
                aceptado = 1;
            }
            break;
        case 2: // 0x leído
            if (isxdigit(A->caracter))
            {
                estado = 3;
            }
            break;
        case 3: // 0x(HEX)+ leído
            if (!isxdigit(A->caracter))
            {
                devolverCaracter(entrada);
                aceptado = 1;
            }
        }
    }
    A->tupla = crearTupla(lexemaEncontrado(entrada), INT);
}

// reconoce los caracteres que lleguen despues de un punto (posibilidad de floats) (UN PUNTO YA LEIDO)
void reconocePunto(AnalizadorLexico A, SistemaEntrada entrada)
{
    unsigned estado = 0;
    unsigned aceptado = 0;
    while (!aceptado)
    {
        A->caracter = siguienteCaracter(entrada);
        switch (estado)
        {
        case 0: //. leído
            if (isdigit(A->caracter))
            {
                reconocePuntoFlotante(A, entrada, 0);
                return;
            }
            else
            {
                devolverCaracter(entrada);
                aceptado = 1;
            }
            break;
        }
    }
    lexemaEncontradoSinOutput(entrada);
    A->tupla = crearTupla(".", (int)'.');
}

// reconoce los caracteres que lleguen despues de un + (posibilidad de +=) (UN + YA LEIDO)
void reconoceMas(AnalizadorLexico A, SistemaEntrada entrada)
{

    unsigned estado = 0, aceptadoMas = 0, aceptadoMasIgual = 0;
    while (!aceptadoMas && !aceptadoMasIgual)
    {
        A->caracter = siguienteCaracter(entrada);
        switch (estado)
        {
        case 0:
            if (A->caracter == '=')
            {
                aceptadoMasIgual = 1;
            }
            else
            {
                devolverCaracter(entrada);
                aceptadoMas = 1;
            }
        }
    }
    if (aceptadoMas)
    {
        lexemaEncontradoSinOutput(entrada);
        A->tupla = crearTupla("+", (int)'+');
    }
    else
    {
        lexemaEncontradoSinOutput(entrada);
        A->tupla = crearTupla("+=", MAS_IGUAL);
    }
}

// reconoce los caracteres que lleguen despues de un * (posibilidad de **) (UN * YA LEIDO)
void reconoceAsterisco(AnalizadorLexico A, SistemaEntrada entrada)
{

    unsigned estado = 0, aceptadoIgual = 0, aceptadoIgualIgual = 0;
    while (!aceptadoIgual && !aceptadoIgualIgual)
    {
        A->caracter = siguienteCaracter(entrada);
        switch (estado)
        {
        case 0:
            if (A->caracter == '*')
            {
                aceptadoIgualIgual = 1;
            }
            else
            {
                devolverCaracter(entrada);
                aceptadoIgual = 1;
            }
        }
    }
    if (aceptadoIgual)
    {
        lexemaEncontradoSinOutput(entrada);
        A->tupla = crearTupla("*", (int)'*');
    }
    else
    {
        lexemaEncontradoSinOutput(entrada);
        A->tupla = crearTupla("**", EXPONENCIAL);
    }
}

// reconoce los caracteres que lleguen despues de un < (posibilidad de <=) (UN < YA LEIDO)
void reconoceMenor(AnalizadorLexico A, SistemaEntrada entrada)
{

    unsigned estado = 0, aceptadoIgual = 0, aceptadoIgualIgual = 0;
    while (!aceptadoIgual && !aceptadoIgualIgual)
    {
        A->caracter = siguienteCaracter(entrada);
        switch (estado)
        {
        case 0:
            if (A->caracter == '=')
            {
                aceptadoIgualIgual = 1;
            }
            else
            {
                devolverCaracter(entrada);
                aceptadoIgual = 1;
            }
        }
    }
    if (aceptadoIgual)
    {
        lexemaEncontradoSinOutput(entrada);
        A->tupla = crearTupla("<", (int)'<');
    }
    else
    {
        lexemaEncontradoSinOutput(entrada);
        A->tupla = crearTupla("<=", EXPONENCIAL);
    }
}

// reconoce los caracteres que lleguen despues de un = (posibilidad de ==) (UN = YA LEIDO)
void reconoceIgual(AnalizadorLexico A, SistemaEntrada entrada)
{

    unsigned estado = 0, aceptadoIgual = 0, aceptadoIgualIgual = 0;
    while (!aceptadoIgual && !aceptadoIgualIgual)
    {
        A->caracter = siguienteCaracter(entrada);
        switch (estado)
        {
        case 0:
            if (A->caracter == '=')
            {
                aceptadoIgualIgual = 1;
            }
            else
            {
                devolverCaracter(entrada);
                aceptadoIgual = 1;
            }
        }
    }
    if (aceptadoIgual)
    {
        lexemaEncontradoSinOutput(entrada);
        A->tupla = crearTupla("=", (int)'=');
    }
    else
    {
        lexemaEncontradoSinOutput(entrada);
        A->tupla = crearTupla("==", EXPONENCIAL);
    }
}

//--------------------------------------------------------------------------------------------------
// FUNCIONES PÚBLICAS

AnalizadorLexico crearAnalizadorLexico()
{
    return malloc(sizeof(struct TipoAnalizadorLexico));
}

TuplaLexemaId siguienteComponenteLexico(AnalizadorLexico A, SistemaEntrada entrada, TablaSimbolos tablaSimbolos)
{
    A->tupla = NULL;
    while (A->tupla == NULL)
    { // mientras no tengamos una tupla formada (habríamos encontrado un lexema) iteramos
        A->caracter = siguienteCaracter(entrada);
        // jerarquía para ordenar los if's [1>2>3>4...]
        //   1 -> caracteres normales
        //   2 -> caracteres de escape
        //   3 -> evaluaciones complejas
        // para cada nivel una jerarquia [a>b>c>d...]
        //   a -> sin automatas (se crea la tupla directamente usando como nombre el símbolo)
        //   b -> sin autómatas (se crea la tupla directamente usando un nombre de tupla diferente al símbolo)
        //   c -> con automatas (el automata crea la tupla)
        if (A->caracter == '(' ||
            A->caracter == ')' ||
            A->caracter == '{' ||
            A->caracter == '}' ||
            A->caracter == '[' ||
            A->caracter == ']' ||
            A->caracter == '>' ||
            A->caracter == ':' ||
            A->caracter == '/' ||
            A->caracter == '-' ||
            A->caracter == ',')
        {
            char *monoCharString = lexemaEncontrado(entrada);
            A->tupla = crearTupla(monoCharString, (int)monoCharString[0]);
        }
        else if (A->caracter == '=')
        {
            reconoceIgual(A, entrada);
        }
        else if (A->caracter == '<')
        {
            reconoceMenor(A, entrada);
        }
        else if (A->caracter == '*')
        {
            reconoceAsterisco(A, entrada);
        }
        else if (A->caracter == '+')
        {
            reconoceMas(A, entrada);
        }
        else if (A->caracter == '.')
        {
            reconocePunto(A, entrada);
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
            reconoceDunderName(A, entrada);
        }
        else if (A->caracter == '\0')
        {
            lexemaEncontradoSinOutput(entrada);
            A->tupla = crearTupla("--FIN DEL ARCHIVO--", END_OF_FILE);
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
        else if (isalpha(A->caracter))
        {
            reconoceIdentificador(A, entrada, tablaSimbolos);
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
