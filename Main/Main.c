#include <stdio.h>
#include <stdlib.h>
#include <ABBRojoNegro.h>
#include <TuplaLexemaId.h>


int main(int argc, char const *argv[])
{

    int b = 5;

    printf("%d\n", b);
    printf("%p\n", &b);

    TuplaLexemaId tupla = crearTuplaLexemaId("hola", 123);
    int id = getTuplaId(tupla);
    char* lexema = getTuplaLexema(tupla);
    ABBRojoNegro a = inicializar();

    insertar(crearTuplaLexemaId("hola",123), a);
    insertar(crearTuplaLexemaId("buenas",56), a);
    insertar(crearTuplaLexemaId("tardes",48), a);
    insertar(crearTuplaLexemaId("por",888), a);
    insertar(crearTuplaLexemaId("la",97), a);
    insertar(crearTuplaLexemaId("tarde",11), a);

    imprimir_arbol(a);

    printf("%d\n", b);
    
    
    
    

    return 0;
}
