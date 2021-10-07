#include <stdio.h>
#include <SistemaEntrada.h>
#include <TablaSimbolos.h>

int main(int argc, char const *argv[])
{
    //1º creamos los componentes del programa
    SistemaEntrada entrada = crearSistemaEntrada("wilcoxon.py");
    TablaSimbolos tabla = crearTablaSimbolos();
    //2º imprimimos la tabla de símbolos
    imprimirTablaSimbolos(tabla);
    //3º ejecutamos el programa (pruebas mientras no esté completo)

    //4º liberamos los recursos
    destruirSistemaEntrada(entrada);
    destruirTablaSimbolos(tabla);
    return 0;
}