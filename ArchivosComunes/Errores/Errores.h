
#ifndef ERRORES_H
#define ERRORES_H

typedef enum ErrorCode
{
    // cuando hay un lexema más largo que el admitido por el buffer de entrada y hay un overflow
    // problema al "avanzar" en el sistema de entrada
    OverflowBuffersEntrada,
    //cuando se provoca una acción ilegal que resultaría en el puntero de lectura del sistema de entrada "inicio" por delante de "delantero"
    // problema al "retroceder" en el sistema de entrada
    EstadoIlegalSistemaEntradaAlRetroceder,
} ErrorCode;

//imprime un error y su descripción dado un código de error
void printCompiladorError(ErrorCode error);

#endif // ERRORES_H