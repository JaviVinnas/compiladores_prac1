#include <stdio.h>
#include <stdlib.h>
#include <ABBRojoNegro.h>
#include <TuplaLexemaId.h>


int main(int argc, char const *argv[])
{
    ABBRojoNegro a = inicializar();

    a = insertar(crearTuplaLexemaId("hola",123), a);
    a = insertar(crearTuplaLexemaId("buenas",56), a);
    a = insertar(crearTuplaLexemaId("tardes",48), a);
    a = insertar(crearTuplaLexemaId("por",888), a);
    a = insertar(crearTuplaLexemaId("la",97), a);
    a = insertar(crearTuplaLexemaId("tarde",11), a);

    imprimir_arbol(a);

    return 0;
}
