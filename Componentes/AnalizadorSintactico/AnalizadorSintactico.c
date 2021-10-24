#include <TablaSimbolos.h>
#include <Flex.h>
#include <Definiciones.h>
#include <Utils.h>
#include <stdio.h>

void obtenerComponentesLexicos(Flex flex, TablaSimbolos tabla)
{
    printf("Componentes léxicos de wilcoxon.py:\n");
    TuplaLexemaId tupla;
    while (1)
    {
        tupla = siguienteComponenteLexico(flex, tabla);
        printTupla(tupla);
        if (getTuplaId(tupla) == END_OF_FILE)
            break;
        if (getTuplaId(tupla) < 300 || getTuplaId(tupla) > 334)// si no es una palabra reservada o un identificador (que puede estar en la tabla de símbolos) lo borramos
            destruirTupla(tupla);
    }
    printSeparator();
}
