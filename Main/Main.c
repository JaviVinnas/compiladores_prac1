#include <TablaSimbolos.h>
#include <AnalizadorSintactico.h>
#include <Flex.h>

int main(int argc, char const *argv[])
{
    //1º creamos los componentes del programa
    TablaSimbolos tabla = crearTablaSimbolos();
    Flex flex = crearFlex("wilcoxon.py");
    //2º imprimimos la tabla de símbolos
    imprimirTablaSimbolos(tabla);
    //3º ejecutamos el programa
    obtenerComponentesLexicos(flex, tabla);
    // 4º liberamos los recursos
    destruirFlex(flex);
    destruirTablaSimbolos(tabla);
    return 0;
}