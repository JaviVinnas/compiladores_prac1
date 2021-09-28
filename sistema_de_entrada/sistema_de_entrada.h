#ifndef SIST_ENTRADA_H
#define SIST_ENTRADA_H

#define BLOCK_SIZE 4096

typedef void *sistema_entrada;

/**
 * Abre un archivo para lectura.
 * @param sist_entrada puntero a la estructura de entrada.
 * @param nombre_archivo Nombre del archivo a abrir.
 * @return 1 (true) si las cosas fueron bien, 0 (false) si no 
 * @see sistema_de_entrada_info
 */
unsigned crear(sistema_entrada *S, char *nombre_archivo);

/**
 * Asigna a un bloque de los existentes un bloque de archivo
 * @param sist_entrada puntero a la estructura de entrada.
 * @param block_name bloque donde se almacenará el bloque de archivo. Puede ser [[a]] o bien [[b]]
 * @return 1 (true) si las cosas fueron bien, 0 (false) si no
 */
unsigned cargarSiguienteBloqueDeArchivo(sistema_entrada *S, char block_name);

/**
 * Devuelve el caracter que toque en el archivo y modifica el estado interno del sistema de entrada.
 * @param sist_entrada puntero a la estructura de entrada.
 * @return el caracter que toque leer o el caracter de fin de archivo ('\0') si se llegase al final.
 */
char pedirCaracter(sistema_entrada *S);

void devolverCaracter(sistema_entrada *S, char caracter);

void lexemaEncontrado(sistema_entrada *S);

#endif SIST_ENTRADA_H