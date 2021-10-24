/* escáner para un lenguaje de juguete al estilo de Pascal */
%{
/* se necesita esto para la llamada a atof() m´as abajo */
#include <math.h>
#include <TuplaLexemaId.h>
#include <Flex.h>
#include <Definiciones.h>

struct TipoFlex
{
    TuplaLexemaId tupla;
    TablaSimbolos tabla;
};

/*Variable global que actúa como struct de flex*/
Flex currentFlex = NULL;

%}
/*Definimos comentarios monolinea*/

COMMENT "#"[^\n]*

/*Definimos caracteres de utilidad*/

RETORNO_DE_CARRO    \n

MAS_IGUAL   \+=
MENOR_IGUAL <=
EXPONENTIAL_OPERATOR    \*\*
DOUBLE_EQUAL    ==
SIMBOLO "+"|"-"|"*"|"/"|"."|"="|"{"|"}"|"("|")"|"["|"]"|"<"|">"|"^"|"!"|"%"|"&"|"|"|"~"|"@"|":"|","

/*Definimos tabulaciones*/
TAB [ ]{4}
SPACES [ ]{1,3}

/*Definimos lo equivalente a enteros*/
DIGIT   [0-9]
NON_ZERO_DIGIT  [1-9]
BIN_DIGIT   [0-1]
OCT_DIGIT   [0-7]
HEX_DIGIT   {DIGIT}|[a-f]|[A-F]
BIN_INTEGER 0(b|B)(_?{BIN_DIGIT})+
OCT_INTEGER 0(o|O)(_?{OCT_DIGIT})+
HEX_INTEGER 0(x|X)(_?{HEX_DIGIT})+
DEC_INTEGER {NON_ZERO_DIGIT}(_?{DIGIT})*|0+(_?0)*
INTEGER {BIN_INTEGER}|{OCT_INTEGER}|{HEX_INTEGER}|{DEC_INTEGER}
/*Definimos lo equivalente a floats*/
DIGIT_PART  {DIGIT}(_?{DIGIT})*
FRACTION    \.{DIGIT_PART}
EXPONENT    (e|E)(\+|-)?{DIGIT_PART}
POINT_FLOAT ({DIGIT_PART}?{FRACTION})|({DIGIT_PART}\.)
EXPONENT_FLOAT  ({DIGIT_PART}|{POINT_FLOAT}){EXPONENT}
FLOAT_NUMBER    {POINT_FLOAT}|{EXPONENT_FLOAT}
/*Definimos string literlas y docstrings*/

DOCSTRING   (\"{3}([^\\\"]|\\.)*\"{3})|(\'{3}([^\\\']|\\.)*\'{3})
STRING_LITERAL  (\"([^\\\"]|\\.)*\")|(\'([^\\\']|\\.)*\')


/*Definimos lo equivalente a identificadores*/
DUNDER_NAME \_\_([[:alnum:]]|_)*\_\_
IDENTIFICADOR  [[:alpha:]]([[:alnum:]]|_)*


%%

<<EOF>> {
    currentFlex->tupla = crearTupla("--FIN DEL ARCHIVO--", END_OF_FILE);
    return 1;
}

{MAS_IGUAL} {
    currentFlex->tupla = crearTupla("+=", MAS_IGUAL);
    return 1;
}

{MENOR_IGUAL} {
    currentFlex->tupla = crearTupla("<=", MENOR_O_IGUAL);
    return 1;
}

{EXPONENTIAL_OPERATOR}  {
    currentFlex->tupla = crearTupla("**", EXPONENCIAL);
    return 1;
}

{DOUBLE_EQUAL}  {
    currentFlex->tupla = crearTupla("==", IGUAL_IGUAL);
    return 1;
}

{INTEGER}   {
    currentFlex->tupla = crearTupla(strdup(yytext), INT);
    return 1;
}

{FLOAT_NUMBER}  {
    currentFlex->tupla = crearTupla(strdup(yytext), FLOAT);
    return 1;
}

{DOCSTRING}  {
    currentFlex->tupla = crearTupla("DOCSTRING", DOCSTRING);
    return 1;
}

{STRING_LITERAL}  {
    currentFlex->tupla = crearTupla(strdup(yytext), STRING_LITERAL);
    return 1;
}

{IDENTIFICADOR}  {
    currentFlex->tupla = buscarIdEnTablaSimbolos(currentFlex->tabla, strdup(yytext));
    return 1;
}

{DUNDER_NAME}  {
    currentFlex->tupla = crearTupla(strdup(yytext), DUNDER_NAME);
    return 1;
}

{RETORNO_DE_CARRO}  {
    currentFlex->tupla = crearTupla("ENTER", (int)'\n');
    return 1;
}

{SIMBOLO}   {
    char* monoCharString = strdup(yytext);
    currentFlex->tupla = crearTupla(monoCharString, (int)monoCharString[0]);
    return 1;
}

{COMMENT}   /*Ignoramos los comentarios*/



{TAB} {
    currentFlex->tupla = crearTupla("TABULACION", TABULACION);
    return 1;
}

{SPACES}    /* se come los espacios en blanco */

.   printf( "Caracter no reconocido: %s\n", yytext );

%%

Flex crearFlex(char *nombreFichero)
{
    Flex F = malloc(sizeof(struct TipoFlex));
    F->tupla = NULL;
    yyin = fopen(nombreFichero, "r");
    return F;
}

TuplaLexemaId siguienteComponenteLexico(Flex F,  TablaSimbolos tablaSimbolos){
    F->tabla = tablaSimbolos;
    currentFlex = F;
    yylex();
    return F->tupla;
}

void destruirFlex(Flex F){
    free(F);
}



