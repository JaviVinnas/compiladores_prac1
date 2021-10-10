#ifndef SIST_ENTRADA_H
#define SIST_ENTRADA_H

#define BLOCK_SIZE 4096
#define BLOCK_SIZE_WITH_GUARD BLOCK_SIZE+1

struct TipoSistemaEntrada;
typedef struct TipoSistemaEntrada *SistemaEntrada;
//reserva memoria para el sistema de entrada
SistemaEntrada crearSistemaEntrada( char *nombre_archivo);
//retorna el caracter que esté en el puntero delantero y lo avanza una posición si se pudiese
char siguienteCaracter(SistemaEntrada S);
//de vuelve el caracter consumido
void devolverCaracter(SistemaEntrada S);
//efectua los cambios internos que tienen lugar cuando se reconoce un lexema y devuelve una cadena con el lexema reconocido
char *lexemaEncontrado(SistemaEntrada S);
//efectua los cambios internos que tienen lugar cuando se reconoce un lexema pero no construye una cadena que saca como output
//útil cuando no nos interese el lexema pero no interesa el output
void lexemaEncontradoSinOutput(SistemaEntrada S);
//libera la memoria del sistema de entrada si hubiera
void destruirSistemaEntrada(SistemaEntrada S);

#endif //SIST_ENTRADA_H