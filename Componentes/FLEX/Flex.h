#include <TablaSimbolos.h>
#include <TuplaLexemaId.h>

struct TipoFlex;
typedef struct TipoFlex *Flex;

Flex crearFlex(char *nombreFichero);

TuplaLexemaId siguienteComponenteLexico(Flex F, TablaSimbolos tablaSimbolos);

void destruirFlex(Flex F);
