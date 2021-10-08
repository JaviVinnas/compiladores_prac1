#include <stdio.h>
#include <stdlib.h>
#include <SistemaEntrada.h>

typedef enum NombreBloque
{
    BLOQUE_A,
    BLOQUE_B,
} NombreBloque;

struct TipoSistemaEntrada{
    FILE *archivo;
    char *inicio, *delantero;
    char blokA[BLOCK_SIZE + 1], blokB[BLOCK_SIZE + 1];
    unsigned bloksCargados;
    unsigned bloquearCargaBloque:1;
};

/**
 * Asigna a un bloque de los existentes un bloque de archivo
 * @param sist_entrada puntero a la estructura de entrada.
 * @param block_name bloque donde se almacenará el bloque de archivo. Puede ser [[a]] o bien [[b]]
 * @return 1 (true) si las cosas fueron bien, 0 (false) si no
 */
void cargarSiguienteBloqueDeArchivo(SistemaEntrada S, NombreBloque nombreBloque)
{
    if (nombreBloque == BLOQUE_A)
    {
        fread(S->blokA, sizeof(char), BLOCK_SIZE, S->archivo + S->bloksCargados);
        S->bloksCargados++;
    }
    else if (nombreBloque == BLOQUE_B)
    {
        fread(S->blokB, sizeof(char), BLOCK_SIZE, S->archivo + S->bloksCargados);
        S->bloksCargados++;
    }
    S->bloksCargados++;
}

SistemaEntrada crearSistemaEntrada(char *nombre_archivo)
{
    SistemaEntrada S = malloc(sizeof(struct TipoSistemaEntrada));
    //creamos el puntero al archivo y lo traemos a memoria
    S->archivo = fopen(nombre_archivo, "r");
    if (S->archivo == NULL)
        return NULL;
    //como hasta ahora no llevamos leido ningún bloque inilizalizamos a cero
    S->bloksCargados = 0;
    //movemos los dos primeros bloques a @blok_a y @blok_b respectivamente
    S->blokA[BLOCK_SIZE] = '\0';
    S->blokB[BLOCK_SIZE] = '\0';
    cargarSiguienteBloqueDeArchivo(S, BLOQUE_A);
    //inicializamos @inicio y @delantero al inicio del primer bloque
    S->inicio = S->delantero = S->blokA;
    return S;
}

char siguienteCaracter(SistemaEntrada S)
{
    //extraemos el caracter que toque leer
    char caracter = *(S->delantero);
    if (caracter == '\0')
    { //si ya es un caracter final antes de moverlo (fin de archivo) devolvemos '\0'
        return caracter;
    }
    //movemos el caracter de fin de línea una posición
    S->delantero++;
    //si nos encontrasemos con el caracter EOF
    if (caracter == '\0')
    {
        /*3 casos:
            1. final del bloque 1
            2. final del bloque 2
            3. final del archivo (no hacemos nada más que devolver '\0', ya hecho)
        */
        if (S->delantero == S->blokA + BLOCK_SIZE)
        { //llega al final del bloque a
            if (S->inicio < S->blokB || S->inicio >= S->blokB + BLOCK_SIZE)
            { //el inicio no está en el bloque b
                S->delantero = S->blokB;
                cargarSiguienteBloqueDeArchivo(S, BLOQUE_B);
            }
            else
            {
                fprintf(stderr, "Overflow de las memorias del sistema de entrada (lexema más largo que las dos memorias juntas)");
            }
        }
        else if (S->delantero == S->blokB + BLOCK_SIZE)
        { //llega al final del bloque b
            if (S->inicio < S->blokA || S->inicio >= S->blokA + BLOCK_SIZE)
            { //el inicio no está en el bloque a
                S->delantero = S->blokA;
                cargarSiguienteBloqueDeArchivo(S, BLOQUE_A);
            }
            else
            {
                fprintf(stderr, "Overflow de las memorias del sistema de entrada (lexema más largo que las dos memorias juntas)");
            }
        }
    }
    return caracter;
}

void devolverCaracter(SistemaEntrada S) {}

char *lexemaEncontrado(SistemaEntrada S) {return NULL;}

void destruirSistemaEntrada(SistemaEntrada S)
{
    fclose(S->archivo);
    free(S);
}
