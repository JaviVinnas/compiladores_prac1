#include <stdio.h>
#include <stdlib.h>
#include "sistema_de_entrada.h"

struct tipo_sistema_entrada
{
    FILE *archivo;
    char *inicio, *delantero;
    char blok_a[BLOCK_SIZE + 1], blok_b[BLOCK_SIZE + 1];
    unsigned long bloks_cargados;
};

typedef struct tipo_sistema_entrada *sistema_entrada;

unsigned cargarSiguienteBloqueDeArchivo(sistema_entrada *S, char block_name)
{
    if (block_name == 'a')
    {
        fread((*S)->blok_a, sizeof(char), BLOCK_SIZE, (*S)->archivo + (*S)->bloks_cargados);
        (*S)->bloks_cargados++;
        return 1;
    }
    else if (block_name == 'b')
    {
        fread((*S)->blok_b, sizeof(char), BLOCK_SIZE, (*S)->archivo + (*S)->bloks_cargados);
        (*S)->bloks_cargados++;
        return 1;
    }
    else
    {
        fprintf(stderr, "Error en el nombre del bloque (no es \"a\" ni \"b\")");
        return 0;
    }
}

unsigned crear(sistema_entrada *S, char *nombre_archivo)
{
    //creamos el puntero al archivo y lo traemos a memoria
    (*S)->archivo = fopen(nombre_archivo, "r");
    if ((*S)->archivo == NULL)
    {
        return 0;
    }
    //como hasta ahora no llevamos leido ningún bloque inilizalizamos a cero
    (*S)->bloks_cargados = 0;
    //movemos los dos primeros bloques a @blok_a y @blok_b respectivamente
    (*S)->blok_a[BLOCK_SIZE] = '\0';
    (*S)->blok_b[BLOCK_SIZE] = '\0';
    cargarSiguienteBloqueDeArchivo(S, 'a');
    //inicializamos @inicio y @delantero al inicio del primer bloque
    (*S)->inicio = (*S)->blok_a;
    (*S)->delantero = (*S)->blok_a;
}

char pedirCaracter(sistema_entrada *S)
{
    //extraemos el caracter que toque leer
    char caracter = (*(*S)->delantero);
    if (caracter == '\0')
    { //si ya es un caracter final antes de moverlo (fin de archivo) devolvemos '\0'
        return caracter;
    }
    //movemos el caracter de fin de línea una posición
    (*S)->delantero++;
    //si nos encontrasemos con el caracter EOF
    if (caracter == '\0')
    {
        /*3 casos: 
            1. final del bloque 1
            2. final del bloque 2
            3. final del archivo (no hacemos nada más que devolver '\0')
        */
        if ((*S)->delantero == (*S)->blok_a + BLOCK_SIZE)
        { //llega al final del bloque a
            if ((*S)->inicio < (*S)->blok_b || (*S)->inicio >= (*S)->blok_b + BLOCK_SIZE)
            { //el inicio no está en el bloque b
                (*S)->delantero = (*S)->blok_b;
                cargarSiguienteBloqueDeArchivo(S, 'b');
            }
            else
            {
                fprintf(stderr, "Overflow de las memorias del sistema de entrada (lexema más largo que las dos memorias juntas)");
            }
        }
        else if ((*S)->delantero == (*S)->blok_b + BLOCK_SIZE)
        { //llega al final del bloque b
            if ((*S)->inicio < (*S)->blok_a || (*S)->inicio >= (*S)->blok_a + BLOCK_SIZE)
            { //el inicio no está en el bloque a
                (*S)->delantero = (*S)->blok_a;
                cargarSiguienteBloqueDeArchivo(S, 'a');
            }
            else
            {
                fprintf(stderr, "Overflow de las memorias del sistema de entrada (lexema más largo que las dos memorias juntas)");
            }
        }
    }
    return caracter;
}

void devolverCaracter(sistema_entrada *S, char caracter) {}

void lexemaEncontrado(sistema_entrada *S) {}
