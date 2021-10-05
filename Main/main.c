#include <stdio.h>
#include <stdlib.h>
#include <ABBRojoNegro.h>


int main(int argc, char const *argv[])
{
    ABBRojoNegro a = inicializar();

    a = insertar(123, a);
    a = insertar(456, a);
    a = insertar(789, a);
    a = insertar(1011, a);
    a = insertar(1213, a);

    imprimir_arbol(a);

    return 0;
}
