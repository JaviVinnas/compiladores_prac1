#ifndef TUPLA_LEXEMA_ID_H
#define TUPLA_LEXEMA_ID_H

typedef char *Lexema;
typedef int IdentificadorNumerico;

struct TipoTuplaLexemaId;
typedef struct TipoTuplaLexemaId *TuplaLexemaId;

//crea un nuevo puntero a tupla con los campos que se le pasan por parametro
TuplaLexemaId crearTupla(Lexema lexema, IdentificadorNumerico id);
//obtiene el lexema de la tupla
Lexema getTuplaLexema(TuplaLexemaId T);
//obtiene el identificador numerico de la tupla
IdentificadorNumerico getTuplaId(TuplaLexemaId T);
//compara dos tuplas para ordenarlas. Útil para mantener equilibrado el árbol binario rojo-negro que almacena la tabla de símbolos
//{{si <0 [T1 < T2]}} {{si >0 [T1 > T2]}}  {{si == 0 [T1 == T2]}}
int compareTuplas(TuplaLexemaId T1, TuplaLexemaId T2);
//imprime una tupla por pantalla de forma legible al usuario
void printTupla(TuplaLexemaId T);
//destruye una tupla liberando la memoria
void destruirTupla(TuplaLexemaId T);

#endif //TUPLA_LEXEMA_ID_H