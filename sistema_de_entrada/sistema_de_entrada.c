#include <stdio.h>
#include <stdlib.h>
#include "sistema_de_entrada.h"

typedef struct
{
    FILE *archivo;
    char *inicio, *delantero;
    char blok_a[BLOCK_SIZE + 1], blok_b[BLOCK_SIZE + 1];
    unsigned long bloks_cargados;

} sistema_de_entrada;

/**
 * Asigna a un bloque de los existentes un bloque de archivo
 * @param sist_entrada puntero a la estructura de entrada.
 * @param block_name bloque donde se almacenará el bloque de archivo. Puede ser [[a]] o bien [[b]]
 * @return 1 (true) si las cosas fueron bien, 0 (false) si no
 */
unsigned siguienteBloqueDeArchivo(sistema_de_entrada *sist_entrada, char block_name)
{
    if (block_name == 'a')
    {
        fread(sist_entrada->blok_a, sizeof(char), BLOCK_SIZE, sist_entrada->archivo + sist_entrada->bloks_cargados);
        sist_entrada->bloks_cargados++;
        return 1;
    }
    else if (block_name == 'b')
    {
        fread(sist_entrada->blok_b, sizeof(char), BLOCK_SIZE, sist_entrada->archivo + sist_entrada->bloks_cargados);
        sist_entrada->bloks_cargados++;
        return 1;
    }
    else
    {
        fprintf(stderr, "Error en el nombre del bloque (no es \"a\" ni \"b\")");
        return 0;
    }
}

/**
 * Abre un archivo para lectura.
 * @param sist_entrada puntero a la estructura de entrada.
 * @param nombre_archivo Nombre del archivo a abrir.
 * @return 1 (true) si las cosas fueron bien, 0 (false) si no 
 * @see sistema_de_entrada_info
 */
unsigned crear(sistema_de_entrada *sist_entrada, char *nombre_archivo)
{
    //creamos el puntero al archivo y lo traemos a memoria
    sist_entrada->archivo = fopen(nombre_archivo, "r");
    if (sist_entrada->archivo == NULL)
    {
        return 0;
    }
    //como hasta ahora no llevamos leido ningún bloque inilizalizamos a cero
    sist_entrada->bloks_cargados = 0;
    //movemos los dos primeros bloques a @blok_a y @blok_b respectivamente
    sist_entrada->blok_a[BLOCK_SIZE] = '\0';
    sist_entrada->blok_b[BLOCK_SIZE] = '\0';
    siguienteBloqueDeArchivo(sist_entrada, 'a');
    siguienteBloqueDeArchivo(sist_entrada, 'b');
    //inicializamos @inicio y @delantero al inicio del primer bloque
    sist_entrada->inicio = sist_entrada->blok_a;
    sist_entrada->delantero = sist_entrada->blok_a;
}

/**
 * @return el caracter que toque leer
 */
char pedirCaracter(sistema_de_entrada *sist_entrada)
{
    //extraemos el caracter que toque leer
    char caracter = *sist_entrada->delantero;
    //movemos el caracter de fin de línea una posición
    sist_entrada->delantero++;
    //si nos encontrasemos con el caracter EOF
    if (caracter == EOF)
    {
        //vamos en qué bloque estamos
    }
}

void devolverCaracter(sistema_de_entrada *sist_entrada, char caracter) {}

void lexemaEncontrado(sistema_de_entrada *sist_entrada){}
