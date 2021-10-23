/* escáner para un lenguaje de juguete al estilo de Pascal */
%{
/* se necesita esto para la llamada a atof() m´as abajo */
#include <math.h>
%}
/*Definimos comentarios monolinea*/

COMMENT "#"[^\n]*\n

/*Definimos caracteres de utilidad*/

/*TODO:definir cosas como ** == o cosas así*/
CHARS   "+"|"-"|"*"|"/"|"."|"="|"{"|"}"|"("|")"|"["|"]"|"<"|">"|"^"|"!"|"%"|"&"|"|"|"~"|"@"|":"|","|"\n"

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


{INTEGER}   {
    printf( "Un integer: %s\n", yytext);
}

{FLOAT_NUMBER}  {
    printf( "Un FLOAT_NUMBER: %s\n", yytext);
}

{DOCSTRING}  {
    printf( "Un DOCSTRING: %s\n", yytext);
}

{STRING_LITERAL}  {
    printf( "Un string literal: %s\n", yytext);
}

{IDENTIFICADOR}  {
    printf( "Un identificador literal: %s\n", yytext);
}

{DUNDER_NAME}  {
    printf( "Un dunder name: %s\n", yytext);
}



{CHARS} printf( "Un símbolo: %s\n", yytext );
{COMMENT}   printf( "Un comentario: %s\n", yytext );
{TAB} printf( "Un tab: %s\n", yytext );
{SPACES}    /* se come los espacios en blanco */
.   printf( "Caracter no reconocido: %s\n", yytext );

%%

int main( argc, argv )
int argc;
char **argv;
{
++argv, --argc; /* se salta el nombre del programa */
if ( argc > 0 )
    yyin = fopen( argv[0], "r" );
else
    yyin = stdin;
yylex();
return 0;
}


