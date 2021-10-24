#ifndef ANALIZADOR_SINTACTICO_H
#define ANALIZADOR_SINTACTICO_H

#include <TablaSimbolos.h>
#include <Flex.h>

/**
 * Obtiene e imprime una lista de componentes léxicos
 * En buena lógica devolvería una lista de esos componentes pero como no se hará un análisi sintáctico
 * como tal se imprimen en la terminal dichos componemtes léxicos a medida que vayan llegando para ahorrar memoria
*/
void obtenerComponentesLexicos(Flex flex, TablaSimbolos tabla);

#endif // ANALIZADOR_SINTACTICO_H