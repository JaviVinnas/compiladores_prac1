#include <stdio.h>
#include <stdlib.h>
#include <SistemaEntrada.h>

typedef enum NombreBloque
{
    BloqueA,
    BloqueB,
} NombreBloque;

typedef enum NombrePunteroLectura
{
    Inicio,
    Delantero,
} NombrePunteroLectura;

struct TipoSistemaEntrada
{
    FILE *archivo;
    char *inicio, *delantero;
    //índices de 0 a BLOCK_SIZE
    char blokA[BLOCK_SIZE_WITH_GUARD], blokB[BLOCK_SIZE_WITH_GUARD];
    unsigned bloksCargados;
    unsigned bloquearCargaBloque : 1;
};

//FUNCIONES PRIVADAS

//traduce de un nombre de puntero de lectura al puntero como tal. Devuelve null si no lo encuentra
char *nombreToPunteroLectura(SistemaEntrada S, NombrePunteroLectura nombrePunteroLectura)
{
    if (nombrePunteroLectura == Inicio)
    {
        return S->inicio;
    }
    else if (nombrePunteroLectura == Delantero)
    {
        return S->delantero;
    }
    //CORREGIR_ERROR: gestionar error en errores.h
    return NULL;
}

//traduce un nombre de bloque al puntero a su comienzo. Devuelve null si no lo encuentra
char *nombreToBloque(SistemaEntrada S, NombreBloque nombreBloque)
{
    if (nombreBloque == BloqueA)
    {
        return S->blokA;
    }
    else if (nombreBloque == BloqueB)
    {
        return S->blokB;
    }
    //CORREGIR_ERROR: gestionar error en errores.h
    return NULL;
}

/**
 * Asigna a un bloque de los existentes un bloque de archivo
 * @param sist_entrada puntero a la estructura de entrada.
 * @param block_name bloque donde se almacenará el bloque de archivo. Puede ser [[a]] o bien [[b]]
 * @return 1 (true) si las cosas fueron bien, 0 (false) si no
 */
void cargarSiguienteBloqueDeArchivo(SistemaEntrada S, NombreBloque nombreBloque)
{
    fread(nombreToBloque(S,nombreBloque), sizeof(char), BLOCK_SIZE, S->archivo + S->bloksCargados);
    S->bloksCargados++;
}



//dice en qué bloque está un puntero de lectura del sistema de entrada. Si no está en ninguno devuelve -1
NombreBloque bloqueDondeEsta(SistemaEntrada S, NombrePunteroLectura nombrePunteroLectura)
{
    char *punteroLectura = nombreToPunteroLectura(S, nombrePunteroLectura);
    if (punteroLectura >= S->blokA && punteroLectura < S->blokA + BLOCK_SIZE_WITH_GUARD)
        return BloqueA;
    else if (punteroLectura >= S->blokB && punteroLectura < S->blokB + BLOCK_SIZE_WITH_GUARD)
        return BloqueB;
    else
        return -1;
}

//dice si u puntero está al final de un bloque de que bloque se trata. Si no está en ninguno devuelve -1
NombreBloque estaAlFinalDeUnBloque(SistemaEntrada S, NombrePunteroLectura nombrePunteroLectura)
{
    char *punteroLectura = nombreToPunteroLectura(S, nombrePunteroLectura);
    if (punteroLectura == S->blokA + BLOCK_SIZE)
        return BloqueA;
    else if (punteroLectura == S->blokB + BLOCK_SIZE)
        return BloqueB;
    else
        return -1;
}

//FUNCIONES PUBLICAS

SistemaEntrada crearSistemaEntrada(char *nombre_archivo)
{
    SistemaEntrada S = malloc(sizeof(struct TipoSistemaEntrada));
    //creamos el puntero al archivo y lo traemos a memoria
    S->archivo = fopen(nombre_archivo, "r");
    if (S->archivo == NULL)
        return NULL;
    //como hasta ahora no llevamos leido ningún bloque inilizalizamos a cero
    S->bloksCargados = 0;
    //movemos los dos primeros bloques a @blok_a y @blok_b respectivamente
    S->blokA[BLOCK_SIZE] = '\0';
    S->blokB[BLOCK_SIZE] = '\0';
    cargarSiguienteBloqueDeArchivo(S, BloqueA);
    //inicializamos @inicio y @delantero al inicio del primer bloque
    S->inicio = S->delantero = S->blokA;
    return S;
}

char siguienteCaracter(SistemaEntrada S)
{
    //extraemos el caracter que toque leer
    char caracter = *(S->delantero);
    if (caracter == '\0')
    { //si ya es un caracter final antes de moverlo (fin de archivo) devolvemos '\0'
        return caracter;
    }
    //movemos el caracter de fin de línea una posición
    S->delantero++;
    //si nos encontrasemos con el caracter EOF
    if (caracter == '\0')
    {
        /*3 casos:
            1. final del bloque 1
            2. final del bloque 2
            3. final del archivo (no hacemos nada más que devolver '\0', ya hecho)
        */
        if (estaAlFinalDeUnBloque(S, Delantero) == BloqueA)
        { //llega al final del bloque a
            if (bloqueDondeEsta(S, Inicio) != BloqueB)
            { //el inicio no está en el bloque b
                S->delantero = S->blokB;
                cargarSiguienteBloqueDeArchivo(S, BloqueB);
            }
            else
            {
                //CORREGIR_ERROR: gestionar error en errores.h
                fprintf(stderr, "Overflow de las memorias del sistema de entrada (lexema más largo que las dos memorias juntas)");
            }
        }
        else if (estaAlFinalDeUnBloque(S, Delantero) == BloqueB)
        { //llega al final del bloque b
            if (bloqueDondeEsta(S, Inicio) != BloqueA)
            { //el inicio no está en el bloque a
                S->delantero = S->blokA;
                cargarSiguienteBloqueDeArchivo(S, BloqueA);
            }
            else
            {
                //CORREGIR_ERROR: gestionar error en errores.h
                fprintf(stderr, "Overflow de las memorias del sistema de entrada (lexema más largo que las dos memorias juntas)");
            }
        }
    }
    return caracter;
}

void devolverCaracter(SistemaEntrada S) {}

char *lexemaEncontrado(SistemaEntrada S)
{
    //varias posibilidades:
    //1. "inicio" y "delante" están en el mismo bloque => situación normal
    //2. "inicio" y "delante" están en bloques distintos => el lexema está entre dos bloques
    char *lexema;
    NombreBloque nombreBloqueInicio = bloqueDondeEsta(S, Inicio);
    NombreBloque nombreBloqueDelantero = bloqueDondeEsta(S, Delantero);
    if (nombreBloqueInicio == nombreBloqueDelantero)
    {
        //1. construimos una cadena con los caracteres entre los dos punteros sin mayor preocupación
        lexema = malloc(sizeof(char) * (S->delantero - S->inicio + 1));
        for (size_t i = 0; i < S->delantero - S->inicio; i++)
            lexema[i] = *(S->inicio + i);
        lexema[S->delantero - S->inicio] = '\0'; //caracter de fin de cadena
    }
    else
    {
        //2. construimos una cadena manejando el cambo de buffer
        unsigned charsEnBlokInicio, charsEnBlokDelantero;
        //celdas desde "inicio" (elemento menor) hasta el fin del bloque donde esté sin contar el centinela (elemnto mayor)
        charsEnBlokInicio = (nombreToBloque(S, nombreBloqueInicio) + BLOCK_SIZE - 1) - S->inicio;
        //celdas desde el comienzo del bloque (elemento menor) hasta "delante" (elemnto mayor)
        charsEnBlokDelantero = S->delantero - nombreToBloque(S, nombreBloqueDelantero);
        //reservamos memoria
        lexema = malloc(sizeof(char) * (charsEnBlokInicio + charsEnBlokDelantero + 1));
        for (size_t i = 0; i < S->delantero - S->inicio; i++)
            //si estamos en el bloque del puntero "inicio"
            if (i <= charsEnBlokInicio)
                lexema[i] = *(S->inicio + i);
            //si estamos en el bloque del puntero "delantero"
            else
                lexema[i] = *(nombreToBloque(S, nombreBloqueDelantero) - charsEnBlokInicio -1 + i);
        lexema[charsEnBlokInicio + charsEnBlokDelantero] = '\0'; //caracter de fin de cadena
    }
    //adelantamos inicio a la posición de delantero
    S->inicio = S->delantero;
    return lexema;
}

void destruirSistemaEntrada(SistemaEntrada S)
{
    fclose(S->archivo);
    free(S);
}
