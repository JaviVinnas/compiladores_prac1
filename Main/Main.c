#include <SistemaEntrada.h>
#include <TablaSimbolos.h>
#include <AnalizadorLexico.h>
#include <AnalizadorSintactico.h>

int main(int argc, char const *argv[])
{
    //1º creamos los componentes del programa
    SistemaEntrada entrada = crearSistemaEntrada("wilcoxon.py");
    TablaSimbolos tabla = crearTablaSimbolos();
    AnalizadorLexico lexico = crearAnalizadorLexico();
    //2º imprimimos la tabla de símbolos
    imprimirTablaSimbolos(tabla);
    //3º ejecutamos el programa (pruebas mientras no esté completo)
    obtenerComponentesLexicos(entrada, tabla, lexico);
    //4º liberamos los recursos
    destruirSistemaEntrada(entrada);
    destruirTablaSimbolos(tabla);
    destruirAnalizadorLexico(lexico);
    return 0;
}