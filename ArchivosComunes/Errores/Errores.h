
#ifndef ERRORES_H
#define ERRORES_H

typedef enum Error
{
    OverflowBuffersEntrada,
    EstadoIlegalSistemaEntradaAlRetroceder,
} Error;

void printCompiladorError(Error error);

#endif // ERRORES_H