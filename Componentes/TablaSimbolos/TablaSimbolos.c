#include <TablaSimbolos.h>
#include <ABBRojoNegro.h>
#include <Definiciones.h>
#include <TuplaLexemaId.h>
#include <stdio.h>
#include <stdlib.h>

struct TipoTablaSimbolos{
    ABBRojoNegro almacenamiento;
};

TablaSimbolos crearTablaSimbolos(){
    TablaSimbolos T = malloc(sizeof(struct TipoTablaSimbolos));
    T->almacenamiento = crearABBRojoNegro();
    //añadimos las palabras reservadas
    insertarABBRojoNegro(crearTupla("False",FALSE), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("True",TRUE), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("None",NONE), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("and",AND), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("as",AS), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("assert",ASSERT), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("async",ASYNC), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("await",AWAIT), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("break",BREAK), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("class",CLASS), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("continue",CONTINUE), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("def",DEF), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("elif",ELIF), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("else",ELSE), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("except",EXCEPT), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("finally",FINALLY), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("for",FOR), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("from",FROM), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("global",GLOBAL), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("if",IF), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("import",IMPORT), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("in",IN), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("is",IS), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("lambda",LAMBDA), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("nonlocal",NONLOCAL), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("not",NOT), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("or",OR), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("pass",PASS), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("raise",RAISE), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("return",RETURN), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("try",TRY),T->almacenamiento);
    insertarABBRojoNegro(crearTupla("while",WHILE), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("with",WITH), T->almacenamiento);
    insertarABBRojoNegro(crearTupla("yield",YIELD), T->almacenamiento);
    return T;
}

void imprimirTablaSimbolos(TablaSimbolos T){
    printf("------------------\n");
    printf("Tabla de símbolos:\n");
    imprimirABBRojoNegro(T->almacenamiento);
    printf("------------------\n");
}

void destruirTablaSimbolos(TablaSimbolos T){
    vaciarABBRojoNegro(T->almacenamiento);
    free(T);
}



