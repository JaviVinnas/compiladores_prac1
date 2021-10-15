#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Errores.h>

void printCompiladorError(ErrorCode error)
{
    char *baseMessage = "ErrorCode del compilador >> ";
    char *contextMessage;
    switch (error)
    {
    case OverflowBuffersEntrada:
        contextMessage = "Overflow del buffer del sistema de entrada: se ha intentado leer un lexema más grande que el tamaño máximo permitido";
        break;
    case EstadoIlegalSistemaEntradaAlRetroceder:
        contextMessage = "Se ha intentado retroceder una posición en el sistema de entrada pero no se puede: ya que daría lugar a una posición ilegal de los punteros de lectura";
        break;
    }
    // construimos el mensaje completo
    char *fullMessage = malloc(sizeof(char) * (strlen(baseMessage) + strlen(contextMessage) + 1));
    strcpy(fullMessage, baseMessage);
    strcat(fullMessage, contextMessage);

    fprintf(stderr,"%s\n", fullMessage);
}