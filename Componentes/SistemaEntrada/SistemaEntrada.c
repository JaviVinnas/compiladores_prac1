#include <stdio.h>
#include <stdlib.h>
#include <SistemaEntrada.h>
#include <string.h>

//----------------------------------------------------------------------------------------------------------------------
//TIPOS DE DATOS

typedef enum NombreBloque
{
    NingunBloque,
    BloqueA,
    BloqueB,
} NombreBloque;

typedef enum NombrePunteroLectura
{
    PunteroInicio,
    PunteroDelantero,
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

//----------------------------------------------------------------------------------------------------------------------
//FUNCIONES PRIVADAS

//traduce de un nombre de puntero de lectura al puntero como tal. Devuelve null si no lo encuentra
char *nombreToPunteroLectura(SistemaEntrada S, NombrePunteroLectura nombrePunteroLectura)
{
    if (nombrePunteroLectura == PunteroInicio)
    {
        return S->inicio;
    }
    else if (nombrePunteroLectura == PunteroDelantero)
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
        //CORREGIR_ERROR: gestionar error en errores.h
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
 * Devuelve una nueva cadena de texto con los caracteres que se encuentren entre dos punteros INCLUIDO EL CONTENIDO DE ESTOS.
 * Se presupone que apuntan al mismo array
 */
char *crearStringEntreDosPunteros(char *punteroMenor, char *punteroMayor)
{
    char *string = malloc(sizeof(char) * (punteroMayor - punteroMenor + 2)); //+1 por si los punteros son iguales +1 para el caracter de fin de cadena
    for (size_t i = 0; i < punteroMayor - punteroMenor; i++)                 //de cero hasta el puntero mayor
        string[i] = punteroMenor[i];
    string[punteroMayor - punteroMenor + 1] = '\0';
    return string;
}

/**
 * Crea el lexema que correspondería al estado interno del sistema de entrada SIN MODIFICAR ESTE ESTADO
 */
char *crearLexemaEntrePunterosDeLectura(SistemaEntrada S){
    //obtenemos los bloques donde están los punteros de lectura
    NombreBloque nombreBloqueInicio = getBloqueDondeEsta(S, PunteroInicio);
    NombreBloque nombreBloqueDelantero = getBloqueDondeEsta(S, PunteroDelantero);
    if (nombreBloqueInicio == nombreBloqueDelantero)
    { //1º caso => "inicio" y "delante" están en el mismo bloque => situación normal
        return crearStringEntreDosPunteros(S->inicio, S->delantero);
    }
    else
    { //2º caso => "inicio" y "delante" están en bloques distintos => el lexema está entre dos bloques (en dos partes)
        //PARTE 1 => desde "inicio" hasta el final del bloque en el que esté (SIN EL CENTINELA)
        char *parte1 = crearStringEntreDosPunteros(S->inicio, nombreToBloque(S, nombreBloqueInicio) + BLOCK_SIZE - 1);
        //PARTE 2 => desde el comienzo del bloque de "delante" hasta donde esté "delante" como tal
        char *parte2 = crearStringEntreDosPunteros(nombreToBloque(S, nombreBloqueDelantero), S->delantero);
        //construimos la cadena destino y la rellenamos con la concatenación las partes
        char *lexema = malloc(sizeof(char) * (strlen(parte1) + strlen(parte2) + 1));
        strcpy(lexema, parte1);
        strcat(lexema, parte2);
        //3. liberamos la memoria de las partes
        free(parte1);
        free(parte2);
        return lexema;
    }
}

//avanza el puntero de lectura una posición y se ocupa de que termine en una posición válida
void gestionarAvanceDelantero(SistemaEntrada S){
    S->delantero++;

    //GESTIONAMOS LO QUE PASA SI LLEGAMOS A UN CENTINELA (si llegamos al final del archivo no hacemos nada)

    if (estaAlFinalDeUnBloque(S, PunteroDelantero) != NingunBloque)
    { //estamos en un centinela
        if (getBloqueDondeEsta(S, PunteroInicio) == getBloqueDondeEsta(S, PunteroDelantero))
        { //los dos punteros de lectura están en el mismo bloque
            //1. pasamos "delantero" al comienzo del otro bloque de memoria
            S->delantero = nombreToBloque(S, getBloqueOpuesto(getBloqueDondeEsta(S, PunteroDelantero)));
            //2. si tuvieramos la flag que bloquea la carga de bloques activa, la desactivamos para la siguiente vez
            if (S->bloquearCargaBloque)
                S->bloquearCargaBloque = 0;
            else
                //si no, cargamos el siguiente bloque para que lo lea "delantero"
                cargarSiguienteBloqueDeArchivo(S, getBloqueDondeEsta(S, PunteroDelantero));
        }
        else
        {
            //CORREGIR_ERROR: gestionar error en errores.h
            fprintf(stderr, "Overflow de las memorias del sistema de entrada (lexema más largo que las dos memorias juntas)");
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------
//FUNCIONES PUBLICAS

SistemaEntrada crearSistemaEntrada(char *nombre_archivo)
{
    SistemaEntrada S = malloc(sizeof(struct TipoSistemaEntrada));
    //creamos el puntero al archivo y lo traemos a memoria
    S->archivo = fopen(nombre_archivo, "r");
    if (S->archivo == NULL)
        //CORREGIR_ERROR: gestionar error en errores.
        return NULL;
    //como no hemos leido ningún bloque todavía lo inilizalizamos a cero
    S->bloksCargados = 0;
    //desbloqueamos la carga de bloque
    S->bloquearCargaBloque = 0;
    //movemos los dos primeros bloques a "blokA" y "blokB" respectivamente
    S->blokA[BLOCK_SIZE] = '\0';
    S->blokB[BLOCK_SIZE] = '\0';
    cargarSiguienteBloqueDeArchivo(S, BloqueA);
    //hacemos que "inicio" y "delantero" apunten a la primera posición del primer bloque
    S->inicio = S->delantero = S->blokA;
    return S;
}


char siguienteCaracter(SistemaEntrada S)
{
    char caracter = *(S->delantero);
    if (caracter != '\0')
        gestionarAvanceDelantero(S);
    return caracter;
}

void devolverCaracter(SistemaEntrada S)
{
    if (S->delantero != S->inicio)
    {//si los punteros de lectura apuntan a posiciones diferentes
        if (S->delantero == nombreToBloque(S, getBloqueDondeEsta(S, PunteroDelantero)))
        { //"delantero" está en la primera posición de su bloque (del bloque donde está)
            //1. Movemos delantero al final del otro bloque de memoria (el bloque donde no está)
            S->delantero = nombreToBloque(S, getBloqueOpuesto(getBloqueDondeEsta(S, PunteroDelantero))) + BLOCK_SIZE - 1;
            //2. activamos la flag que bloquea la carga de bloques para no perder el bloque 
            S->bloquearCargaBloque = 1;
        }
        else
        { //"delantero" puede retroceder una posición y se quedaría dentro del mismo bloque de memoria en el qye ya estaba (sin conflictos)
            S->delantero--;
        }
    }
}

void lexemaEncontradoSinOutput(SistemaEntrada S){
    S->inicio = S->delantero;
}



char *lexemaEncontrado(SistemaEntrada S)
{

    char * lexema = crearLexemaEntrePunterosDeLectura(S); //creamos el lexema sin modificar el estado interno del sistema de entrada
    lexemaEncontradoSinOutput(S); //modificamos el estado interno como si hubiéramos encontrado un lexema
    return lexema;
}

void destruirSistemaEntrada(SistemaEntrada S)
{
    fclose(S->archivo);
    free(S);
}
