#ifndef SIST_ENTRADA_H
#define SIST_ENTRADA_H

// El tamaño óptimo del bloque será el del lexema más largo,
// para que en caso de leerlo y que "inicio" estuviera al final de un bloque (previo al centinela) PEOR CASO,
// tener la garantía de no perder la referencia del comienzo del lexema
#define BLOCK_SIZE 82
#define BLOCK_SIZE_WITH_GUARD BLOCK_SIZE + 1

struct TipoSistemaEntrada;
typedef struct TipoSistemaEntrada *SistemaEntrada;
// reserva memoria para el sistema de entrada
SistemaEntrada crearSistemaEntrada(char *nombre_archivo);
// retorna el caracter que esté en el puntero delantero y lo avanza una posición si se pudiese
char siguienteCaracter(SistemaEntrada S);
// devuelve el caracter consumido
void devolverCaracter(SistemaEntrada S);
// efectua los cambios internos que tienen lugar cuando se reconoce un lexema y devuelve una cadena con el lexema reconocido
char *lexemaEncontrado(SistemaEntrada S);
// efectua los cambios internos que tienen lugar cuando se reconoce un lexema pero no construye una cadena output
//útil cuando no nos interese el lexema pero no el output
void lexemaEncontradoSinOutput(SistemaEntrada S);
// libera la memoria del sistema de entrada si hubiera
void destruirSistemaEntrada(SistemaEntrada S);

#endif // SIST_ENTRADA_H