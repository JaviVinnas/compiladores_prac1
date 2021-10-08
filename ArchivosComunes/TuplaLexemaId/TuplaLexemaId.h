#ifndef TUPLA_LEXEMA_ID_H
#define TUPLA_LEXEMA_ID_H

typedef char *Lexema;
typedef int IdentificadorNumerico;

struct TipoTuplaLexemaId;
typedef struct TipoTuplaLexemaId *TuplaLexemaId;

TuplaLexemaId crearTupla(Lexema lexema, IdentificadorNumerico id);
Lexema getTuplaLexema(TuplaLexemaId T);
IdentificadorNumerico getTuplaId(TuplaLexemaId T);
//{{si <0 [T1 < T2]}} {{si >0 [T1 > T2]}}  {{si == 0 [T1 == T2]}}
int compareTuplas(TuplaLexemaId T1, TuplaLexemaId T2);
void printTupla(TuplaLexemaId T);
void destruirTupla(TuplaLexemaId T);

#endif //TUPLA_LEXEMA_ID_H