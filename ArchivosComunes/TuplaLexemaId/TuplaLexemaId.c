#include <TuplaLexemaId.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct TipoTuplaLexemaId
{
    Lexema lexema;
    IdentificadorNumerico id;
};

TuplaLexemaId crearTupla(Lexema lexema, IdentificadorNumerico id)
{
    TuplaLexemaId tupla = malloc(sizeof(struct TipoTuplaLexemaId));
    tupla->lexema = lexema;
    tupla->id = id;
    return tupla;
}

Lexema getTuplaLexema(TuplaLexemaId T)
{
    return T->lexema;
}

IdentificadorNumerico getTuplaId(TuplaLexemaId T)
{
    return T->id;
}

int compareTuplas(TuplaLexemaId T1, TuplaLexemaId T2)
{
    return strcmp(T1->lexema, T2->lexema);
}

void printTupla(TuplaLexemaId T)
{
    if (strchr(T->lexema, '>') != NULL || strchr(T->lexema, '<') != NULL || strchr(T->lexema, '=') != NULL)
        printf("[%s,%d]\n", T->lexema, T->id);
    else if (strchr(T->lexema, ','))
        printf("<%s|%d>\n", T->lexema, T->id);
    else
        printf("<%s,%d>\n", T->lexema, T->id);
}

void destruirTupla(TuplaLexemaId T)
{
    free(T->lexema);
    free(T);
}