#CFLAGS -> donde directorios del proyecto donde haya archivos *.h
#OBJETOS -> los archivos *.c, pero cambiándoles la extensión por .o con la ruta desde donde está el makefile (la raíz del proyecto)
#FUENTES -> los archivos *.c con la ruta desde donde está el makefile (la raíz del proyecto)

FLEX_FILE=./Componentes/FLEX/Flex

CFLAGS=-g \
-I./ArchivosComunes \
-I./ArchivosComunes/TuplaLexemaId \
-I./ArchivosComunes/Errores \
-I./ArchivosComunes/Utils \
-I./Componentes/FLEX \
-I./Componentes/AnalizadorSintactico \
-I./Componentes/TablaSimbolos \
-I./Componentes/TablaSimbolos/ABBRojoNegro \
-I./Main

OBJETOS=\
./ArchivosComunes/TuplaLexemaId/TuplaLexemaId.o \
./ArchivosComunes/Utils/Utils.o \
./ArchivosComunes/Errores/Errores.o \
$(FLEX_FILE).o \
./Componentes/AnalizadorSintactico/AnalizadorSintactico.o \
./Componentes/TablaSimbolos/TablaSimbolos.o \
./Componentes/TablaSimbolos/ABBRojoNegro/ABBRojoNegro.o \
./Main/Main.o

FUENTES=\
./ArchivosComunes/TuplaLexemaId/TuplaLexemaId.c \
./ArchivosComunes/Utils/Utils.c \
./ArchivosComunes/Errores/Errores.c \
$(FLEX_FILE).c \
./Componentes/AnalizadorSintactico/AnalizadorSintactico.c \
./Componentes/TablaSimbolos/TablaSimbolos.c \
./Componentes/TablaSimbolos/ABBRojoNegro/ABBRojoNegro.c \
./Main/Main.c



ejecutable: $(OBJETOS)
	gcc -Wall -g -lfl $(OBJETOS) -o ejecutable

build_flex:
	flex --outfile=$(FLEX_FILE).c $(FLEX_FILE).l

depend:
	makedepend $(CFLAGS) $(FUENTES)

all:
	$(MAKE) depend
	$(MAKE) build_flex
	$(MAKE) ejecutable



#----------------------------------------------------------------------------------------------------------------------
# DO NOT DELETE

./ArchivosComunes/TuplaLexemaId/TuplaLexemaId.o: ./ArchivosComunes/TuplaLexemaId/TuplaLexemaId.h
./ArchivosComunes/TuplaLexemaId/TuplaLexemaId.o: /usr/include/string.h
./ArchivosComunes/TuplaLexemaId/TuplaLexemaId.o: /usr/include/stdio.h
./ArchivosComunes/TuplaLexemaId/TuplaLexemaId.o: /usr/include/stdlib.h
./ArchivosComunes/Utils/Utils.o: ./ArchivosComunes/Utils/Utils.h
./ArchivosComunes/Utils/Utils.o: /usr/include/stdio.h /usr/include/stdlib.h
./ArchivosComunes/Errores/Errores.o: /usr/include/stdio.h
./ArchivosComunes/Errores/Errores.o: /usr/include/string.h
./ArchivosComunes/Errores/Errores.o: /usr/include/stdlib.h
./ArchivosComunes/Errores/Errores.o: ./ArchivosComunes/Errores/Errores.h
./Componentes/FLEX/Flex.o: /usr/include/stdio.h /usr/include/string.h
./Componentes/FLEX/Flex.o: /usr/include/errno.h /usr/include/features.h
./Componentes/FLEX/Flex.o: /usr/include/stdc-predef.h /usr/include/stdlib.h
./Componentes/FLEX/Flex.o: /usr/include/math.h
./Componentes/FLEX/Flex.o: ./ArchivosComunes/TuplaLexemaId/TuplaLexemaId.h
./Componentes/FLEX/Flex.o: ./Componentes/FLEX/Flex.h
./Componentes/FLEX/Flex.o: ./Componentes/TablaSimbolos/TablaSimbolos.h
./Componentes/FLEX/Flex.o: ./ArchivosComunes/Definiciones.h
./Componentes/FLEX/Flex.o: /usr/include/unistd.h
./Componentes/AnalizadorSintactico/AnalizadorSintactico.o: ./Componentes/TablaSimbolos/TablaSimbolos.h
./Componentes/AnalizadorSintactico/AnalizadorSintactico.o: ./ArchivosComunes/TuplaLexemaId/TuplaLexemaId.h
./Componentes/AnalizadorSintactico/AnalizadorSintactico.o: ./Componentes/FLEX/Flex.h
./Componentes/AnalizadorSintactico/AnalizadorSintactico.o: ./ArchivosComunes/Definiciones.h
./Componentes/AnalizadorSintactico/AnalizadorSintactico.o: ./ArchivosComunes/Utils/Utils.h
./Componentes/AnalizadorSintactico/AnalizadorSintactico.o: /usr/include/stdio.h
./Componentes/TablaSimbolos/TablaSimbolos.o: ./Componentes/TablaSimbolos/TablaSimbolos.h
./Componentes/TablaSimbolos/TablaSimbolos.o: ./ArchivosComunes/TuplaLexemaId/TuplaLexemaId.h
./Componentes/TablaSimbolos/TablaSimbolos.o: ./Componentes/TablaSimbolos/ABBRojoNegro/ABBRojoNegro.h
./Componentes/TablaSimbolos/TablaSimbolos.o: ./ArchivosComunes/Definiciones.h
./Componentes/TablaSimbolos/TablaSimbolos.o: ./ArchivosComunes/Utils/Utils.h
./Componentes/TablaSimbolos/TablaSimbolos.o: /usr/include/stdio.h
./Componentes/TablaSimbolos/TablaSimbolos.o: /usr/include/stdlib.h
./Componentes/TablaSimbolos/ABBRojoNegro/ABBRojoNegro.o: ./Componentes/TablaSimbolos/ABBRojoNegro/ABBRojoNegro.h
./Componentes/TablaSimbolos/ABBRojoNegro/ABBRojoNegro.o: ./ArchivosComunes/TuplaLexemaId/TuplaLexemaId.h
./Componentes/TablaSimbolos/ABBRojoNegro/ABBRojoNegro.o: /usr/include/stdio.h
./Componentes/TablaSimbolos/ABBRojoNegro/ABBRojoNegro.o: /usr/include/stdlib.h
./Componentes/TablaSimbolos/ABBRojoNegro/ABBRojoNegro.o: /usr/include/string.h
./Main/Main.o: ./Componentes/TablaSimbolos/TablaSimbolos.h
./Main/Main.o: ./ArchivosComunes/TuplaLexemaId/TuplaLexemaId.h
./Main/Main.o: ./Componentes/AnalizadorSintactico/AnalizadorSintactico.h
./Main/Main.o: ./Componentes/FLEX/Flex.h
