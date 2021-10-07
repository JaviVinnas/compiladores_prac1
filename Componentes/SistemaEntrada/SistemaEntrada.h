#ifndef SIST_ENTRADA_H
#define SIST_ENTRADA_H

#define BLOCK_SIZE 4096

struct TipoSistemaEntrada;
typedef struct TipoSistemaEntrada *SistemaEntrada;
SistemaEntrada crearSistemaEntrada( char *nombre_archivo);
//retorna el caracter que esté en el puntero delantero y lo avanza una posición
char pedirCaracter(SistemaEntrada S);
//retorcede el puntero delantero una posición
void devolverCaracter(SistemaEntrada S);
//devuelve los caracteres que estén entre los pinteros inicio y delante
char *devolverLexema(SistemaEntrada S);
//libera la memoria del sistema de entrada si hubiera
void destruirSistemaEntrada(SistemaEntrada S);

#endif //SIST_ENTRADA_H