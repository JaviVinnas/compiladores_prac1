#include "TuplaLexemaId.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



struct TipoTuplaLexemaId {
    Lexema lexema;
    IdentificadorNumerico id;
};

TuplaLexemaId crearTuplaLexemaId(Lexema lexema, IdentificadorNumerico id) {
    TuplaLexemaId tupla = malloc(sizeof(struct TipoTuplaLexemaId));
    //strcpy(tupla->lexema, lexema);
    tupla->lexema = lexema;
    tupla->id = id;
    return tupla;
}

Lexema getTuplaLexema(TuplaLexemaId T){
    return T->lexema;
}

IdentificadorNumerico getTuplaId(TuplaLexemaId T){
    return T->id;
}

int compareTuplas(TuplaLexemaId T1, TuplaLexemaId T2){
    return strcmp(T1->lexema, T2->lexema);
}

void printTuplaLexemaId(TuplaLexemaId T){
    printf("T<%s, %d>", getTuplaLexema(T), getTuplaId(T));
}

void borrarTuplaLexemaId(TuplaLexemaId T){
    free(T);
}