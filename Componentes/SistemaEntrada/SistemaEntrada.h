#ifndef SIST_ENTRADA_H
#define SIST_ENTRADA_H

#define BLOCK_SIZE 4096
#define BLOCK_SIZE_WITH_GUARD BLOCK_SIZE+1

struct TipoSistemaEntrada;
typedef struct TipoSistemaEntrada *SistemaEntrada;
SistemaEntrada crearSistemaEntrada( char *nombre_archivo);
//retorna el caracter que esté en el puntero delantero y lo avanza una posición
char siguienteCaracter(SistemaEntrada S);
//retorcede el puntero delantero una posición
void devolverCaracter(SistemaEntrada S);
//devuelve una cadena de texto con los caracteres que estén entre los punteros inicio y delante (incluidos)
char *lexemaEncontrado(SistemaEntrada S);
//libera la memoria del sistema de entrada si hubiera
void destruirSistemaEntrada(SistemaEntrada S);

#endif //SIST_ENTRADA_H