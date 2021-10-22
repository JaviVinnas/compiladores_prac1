/* escáner para un lenguaje de juguete al estilo de Pascal */
%{
/* se necesita esto para la llamada a atof() m´as abajo */
#include <math.h>
%}


/*Definimos lo equivalente a enteros*/
DIGIT   [0-9]
NON_ZERO_DIGIT  [1-9]
BIN_DIGIT   0|1
OCT_DIGIT   [0-7]
HEX_DIGIT   (DIGIT)|[a-f]|[a-f]
BIN_INTEGER 0(b|B)(_?(BIN_DIGIT))+
OCT_INTEGER 0(o|O)(_?(OCT_DIGIT))+
HEX_INTEGER 0(x|X)(_?(HEX_DIGIT))+
DEC_INTEGER (NON_ZERO_DIGIT)(_?(DIGIT))*|0+(_?0)*
INTEGER (BIN_INTEGER)|(OCT_INTEGER)|(HEX_INTEGER)|(DEC_INTEGER)


/*Definimos lo equivalente a floats*/

ID  [a-z][a-z0-9]*

%%
{INTEGER}   {
    printf( "Un integer: %s\n", yytext);
}



if|then|begin|end|procedure|function    {
printf( "Una palabra clave: %s\n", yytext );
}

{ID}    printf( "Un identificador: %s\n", yytext );

"+"|"-"|"*"|"/" printf( "Un operador: %s\n", yytext );
"{"[^}\n]*"}"   printf( "Un comentario: %s\n", yytext );
[ \t\n]+    /* se come los espacios en blanco */
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


