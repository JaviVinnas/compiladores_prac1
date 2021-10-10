#include <stdio.h>
#include <stdlib.h>
#include <SistemaEntrada.h>
#include <string.h>

typedef enum NombreBloque
{
    NingunBloque,
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
    /**
     * índices de 0 a BLOCK_SIZE => blok[0] a blok[BLOCK_SIZE] => blok+0 a blok+BLOCK_SIZE
     * índices útiles (sin centinela) de 0 a BLOCK_SIZE -1 => blok[0] a blok[BLOCK_SIZE-1] => blok+0 a blok+BLOCK_SIZE-1
    */
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

//traduce un nombre de bloque al puntero al puntero a char que es el inicio del array "bloque". Devuelve null si no lo encuentra
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
 * @param S puntero a la estructura de entrada.
 * @param nombreBloque nombre del bloque donde se almacenará el bloque de archivo. Puede ser [[a]] o bien [[b]]
 */
void cargarSiguienteBloqueDeArchivo(SistemaEntrada S, NombreBloque nombreBloque)
{
    char *bloque = nombreToBloque(S, nombreBloque);
    size_t numItemsLeidos = fread(bloque, sizeof(char), BLOCK_SIZE, S->archivo + (S->bloksCargados * BLOCK_SIZE));
    if (numItemsLeidos < BLOCK_SIZE) //si llegasemos al fin del archivo (array "bloque" parcialmente lleno)
        bloque[numItemsLeidos] = '\0';
    S->bloksCargados++;
}

//dice en qué bloque está un puntero de lectura del sistema de entrada. Si no está en ninguno devuelve -1
NombreBloque getBloqueDondeEsta(SistemaEntrada S, NombrePunteroLectura nombrePunteroLectura)
{
    char *punteroLectura = nombreToPunteroLectura(S, nombrePunteroLectura);
    if (punteroLectura >= S->blokA && punteroLectura <= S->blokA + BLOCK_SIZE)
        return BloqueA;
    else if (punteroLectura >= S->blokB && punteroLectura <= S->blokB + BLOCK_SIZE)
        return BloqueB;
    else
        return NingunBloque;
}

//dice si u puntero está al final de un bloque (donde el centinela), de que bloque se trata.
NombreBloque estaAlFinalDeUnBloque(SistemaEntrada S, NombrePunteroLectura nombrePunteroLectura)
{
    char *punteroLectura = nombreToPunteroLectura(S, nombrePunteroLectura);
    if (punteroLectura == S->blokA + BLOCK_SIZE)
        return BloqueA;
    else if (punteroLectura == S->blokB + BLOCK_SIZE)
        return BloqueB;
    else
        return NingunBloque;
}

//devuelve el nombre de bloque opuesto al pasado por argumentos
NombreBloque getBloqueOpuesto(NombreBloque nombreBloque)
{
    if (nombreBloque == BloqueA)
        return BloqueB;
    else if (nombreBloque == BloqueB)
        return BloqueA;
    else
        return NingunBloque;
}

/**
 * Devuelve una cadena con los caracteres que se encuentren entre dos punteros INCLUIDO EL CONTENIDO DE ESTOS.
 * Se presupone que apuntan al mismo array
 */
char *getStringEntreDosPunteros(char *punteroMenor, char *punteroMayor)
{
    char *string = malloc(sizeof(char) * (punteroMayor - punteroMenor + 2)); //+1 por si los punteros son iguales +1 para el caracter de fin de cadena
    for (size_t i = 0; i < punteroMayor - punteroMenor; i++) //de cero hasta el puntero mayor
        string[i] = punteroMenor[i];
    string[punteroMayor - punteroMenor + 1] = '\0';
    return string;
}

/**
 * Devuelve una cadena con los caracteres que entre el puntero que se le pase por argumento y el final del bloque donde esté.
 * Si el (*) marca el elemnto apuntado por el puntero, para el bloque [a|b|c|d*|e|f|g|\0] devolvería la cadena "defg" bien formada (con el caracter de fin de cadena)
 */
char *getLexemaParcialPuntero(SistemaEntrada S, NombrePunteroLectura nombrePunteroLectura)
{
    char *punteroLectura = nombreToPunteroLectura(S, nombrePunteroLectura);
    char *bloqueDondeEsta = nombreToBloque(S, getBloqueDondeEsta(S, nombrePunteroLectura));
    char *lexema = malloc(sizeof(char) * (BLOCK_SIZE + 1));
}

//FUNCIONES PUBLICAS

SistemaEntrada crearSistemaEntrada(char *nombre_archivo)
{
    SistemaEntrada S = malloc(sizeof(struct TipoSistemaEntrada));
    //creamos el puntero al archivo y lo traemos a memoria
    S->archivo = fopen(nombre_archivo, "r");
    if (S->archivo == NULL)
        //CORREGIR_ERROR: gestionar error en errores.
        return NULL;
    //como hasta ahora no llevamos leido ningún bloque inilizalizamos a cero
    S->bloksCargados = 0;
    //desbloqueamos la carga de bloque
    S->bloquearCargaBloque = 0;
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
        return caracter; //devolvemos el caracter antes de avanzar el puntero
    //si no es un centinela, avanzamos el puntero
    S->delantero++;

    //GESTIONAMOS LO QUE PASA SI LLEGAMOS A UN CENTINELA (si llegamos al final del archivo no hacemos nada)

    if (estaAlFinalDeUnBloque(S, Delantero) != NingunBloque)
    { //estamos en un centinela
        if (getBloqueDondeEsta(S, Inicio) == getBloqueDondeEsta(S, Delantero) != NingunBloque)
        { //los dos punteros de lectura están en el mismo bloque
            //pasamos "delantero" al comienzo del bloque siguiente
            S->delantero = nombreToBloque(S, getBloqueOpuesto(getBloqueDondeEsta(S, Delantero)));
            //si tuvieramos la fag que bloquea la carga de bloques activa la desactivamos para la siguiente
            if (S->bloquearCargaBloque)
                S->bloquearCargaBloque = 0;
            else
                //si no cargamos el siguiente bloque para que lo lea "delantero"
                cargarSiguienteBloqueDeArchivo(S, getBloqueDondeEsta(S, Delantero));
        }
        else
        {
            //CORREGIR_ERROR: gestionar error en errores.h
            fprintf(stderr, "Overflow de las memorias del sistema de entrada (lexema más largo que las dos memorias juntas)");
        }
    }
    return caracter;
}

void devolverCaracter(SistemaEntrada S) {}

char *lexemaEncontrado(SistemaEntrada S)
{
    //varias posibilidades:
    NombreBloque nombreBloqueInicio = getBloqueDondeEsta(S, Inicio);
    NombreBloque nombreBloqueDelantero = getBloqueDondeEsta(S, Delantero);
    if (nombreBloqueInicio == nombreBloqueDelantero != NingunBloque)
    {//1. "inicio" y "delante" están en el mismo bloque => situación normal
        return getStringEntreDosPunteros(S->inicio, S->delantero);
    }
    else
    {//2. "inicio" y "delante" están en bloques distintos => el lexema está entre dos bloques (en dos partes)
        //desde "inicio" hasta el final del bloque en el que esté
        char *parte1 = getStringEntreDosPunteros(S->inicio, nombreToBloque(S, nombreBloqueInicio) + BLOCK_SIZE);
        //desde el comienzo del bloque de "delante" hasta donde esté delante
        char *parte2 = getStringEntreDosPunteros(nombreToBloque(S, nombreBloqueDelantero), S->delantero);
        //construimos la cadena destino y concatenamos las partes
        char *lexema = malloc(sizeof(char) * (strlen(parte1) + strlen(parte2) + 1));
        strcpy(lexema, parte1);
        strcat(lexema, parte2);
        //3. liberamos la memoria de las partes
        free(parte1);
        free(parte2);
        return lexema;
    }
}

void destruirSistemaEntrada(SistemaEntrada S)
{
    fclose(S->archivo);
    free(S);
}
