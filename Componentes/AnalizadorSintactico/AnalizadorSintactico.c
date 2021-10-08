#include <SistemaEntrada.h>
#include <TablaSimbolos.h>
#include <AnalizadorLexico.h>
#include <Definiciones.h>
#include <Utils.h>
#include <stdio.h>

void obtenerComponentesLexicos(SistemaEntrada entrada, TablaSimbolos tabla, AnalizadorLexico lexico)
{
    printf("Componentes léxicos de wilcoxon.py:\n");
    TuplaLexemaId tupla;
    while (1)
    {
        tupla = siguienteComponenteLexico(lexico, entrada, tabla);
        printTupla(tupla);
        if (getTuplaId(tupla) == END_OF_FILE)
            break;
        destruirTupla(tupla);
    }
    destruirTupla(tupla);
    printSeparator();
}
