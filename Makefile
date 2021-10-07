#CFLAGS -> donde directorios del proyecto donde haya ficheros.h
#OBJETOS -> los .c, pero cambiándoles la extensión por .o con la ruta desde donde está el makefile (la raíz del proyecto)
#FUENTES -> los .c con la ruta desde donde está el makefile (la raíz del proyecto)

CFLAGS=-g -Wall \
-I./ArchivosComunes \
-I./ArchivosComunes/TuplaLexemaId \
-I./Componentes/AnalizadorLexico \
-I./Componentes/AnalizadorSintactico \
-I./Componentes/SistemaEntrada \
-I./Componentes/TablaSimbolos \
-I./Componentes/TablaSimbolos/ABBRojoNegro

OBJETOS=\
./ArchivosComunes/TuplaLexemaId.o \
./Componentes/AnalizadorLexico/AnalizadorLexico.o \
./Componentes/AnalizadorSintactico/AnalizadorSintactico.o \
./Componentes/SistemaEntrada/SistemaEntrada.o \
./Componentes/TablaSimbolos/TablaSimbolos.o \
./Componentes/TablaSimbolos/ABBRojoNegro/ABBRojoNegro.o \
./Main/Main.o

FUENTES=\
./ArchivosComunes/TuplaLexemaId.c \
./Componentes/AnalizadorLexico/AnalizadorLexico.c \
./Componentes/AnalizadorSintactico/AnalizadorSintactico.c \
./Componentes/SistemaEntrada/SistemaEntrada.c \
./Componentes/TablaSimbolos/TablaSimbolos.c \
./Componentes/TablaSimbolos/ABBRojoNegro/ABBRojoNegro.c \
./Main/Main.c

ejecutable: $(OBJETOS)
	gcc -Wall -g $(OBJETOS) -o ejecutable

depend:
	makedepend $(CFLAGS) $(FUENTES)

all:
	$(MAKE) depend
	$(MAKE) ejecutable


#----------------------------------------------------------------------------------------------------------------------
# DO NOT DELETE

./Main/main.o: /usr/include/stdio.h /usr/include/stdlib.h
./Main/main.o: ./ABBRojoNegro/ABBRojoNegro.h ./TuplaLexemaId/TuplaLexemaId.h
./ABBRojoNegro/ABBRojoNegro.o: ./ABBRojoNegro/ABBRojoNegro.h
./ABBRojoNegro/ABBRojoNegro.o: ./TuplaLexemaId/TuplaLexemaId.h
./ABBRojoNegro/ABBRojoNegro.o: /usr/include/stdio.h /usr/include/stdlib.h
./ABBRojoNegro/ABBRojoNegro.o: /usr/include/string.h
./TuplaLexemaId/TuplaLexemaId.o: ./TuplaLexemaId/TuplaLexemaId.h
./TuplaLexemaId/TuplaLexemaId.o: /usr/include/string.h /usr/include/stdio.h
./TuplaLexemaId/TuplaLexemaId.o: /usr/include/stdlib.h
