#CFLAGS -> donde directorios del proyecto donde haya ficheros.h
#OBJETOS -> los .c, pero cambiándoles la extensión por .o con la ruta desde donde está el makefile (la raíz del proyecto)
#FUENTES -> los .c con la ruta desde donde está el makefile (la raíz del proyecto)

CFLAGS=-g \
-I./ArchivosComunes \
-I./ArchivosComunes/TuplaLexemaId \
-I./ArchivosComunes/Errores \
-I./ArchivosComunes/Utils \
-I./Componentes/AnalizadorLexico \
-I./Componentes/AnalizadorSintactico \
-I./Componentes/SistemaEntrada \
-I./Componentes/TablaSimbolos \
-I./Componentes/TablaSimbolos/ABBRojoNegro \
-I./Main

OBJETOS=\
./ArchivosComunes/TuplaLexemaId/TuplaLexemaId.o \
./ArchivosComunes/Utils/Utils.o \
./ArchivosComunes/Errores/Errores.o \
./Componentes/AnalizadorLexico/AnalizadorLexico.o \
./Componentes/AnalizadorSintactico/AnalizadorSintactico.o \
./Componentes/SistemaEntrada/SistemaEntrada.o \
./Componentes/TablaSimbolos/TablaSimbolos.o \
./Componentes/TablaSimbolos/ABBRojoNegro/ABBRojoNegro.o \
./Main/Main.o

FUENTES=\
./ArchivosComunes/TuplaLexemaId/TuplaLexemaId.c \
./ArchivosComunes/Utils/Utils.c \
./ArchivosComunes/Errores/Errores.c \
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

./ArchivosComunes/TuplaLexemaId/TuplaLexemaId.o: ./ArchivosComunes/TuplaLexemaId/TuplaLexemaId.h
./ArchivosComunes/TuplaLexemaId/TuplaLexemaId.o: /usr/include/string.h
./ArchivosComunes/TuplaLexemaId/TuplaLexemaId.o: /usr/include/stdio.h
./ArchivosComunes/TuplaLexemaId/TuplaLexemaId.o: /usr/include/stdlib.h
./ArchivosComunes/Utils/Utils.o: ./ArchivosComunes/Utils/Utils.h
./ArchivosComunes/Utils/Utils.o: /usr/include/stdio.h /usr/include/stdlib.h
./Componentes/AnalizadorLexico/AnalizadorLexico.o: ./Componentes/AnalizadorLexico/AnalizadorLexico.h
./Componentes/AnalizadorLexico/AnalizadorLexico.o: ./ArchivosComunes/TuplaLexemaId/TuplaLexemaId.h
./Componentes/AnalizadorLexico/AnalizadorLexico.o: ./Componentes/SistemaEntrada/SistemaEntrada.h
./Componentes/AnalizadorLexico/AnalizadorLexico.o: ./Componentes/TablaSimbolos/TablaSimbolos.h
./Componentes/AnalizadorLexico/AnalizadorLexico.o: ./ArchivosComunes/Definiciones.h
./Componentes/AnalizadorLexico/AnalizadorLexico.o: ./ArchivosComunes/Utils/Utils.h
./Componentes/AnalizadorLexico/AnalizadorLexico.o: /usr/include/stdio.h
./Componentes/AnalizadorLexico/AnalizadorLexico.o: /usr/include/stdlib.h
./Componentes/AnalizadorLexico/AnalizadorLexico.o: /usr/include/ctype.h
./Componentes/AnalizadorLexico/AnalizadorLexico.o: /usr/include/features.h
./Componentes/AnalizadorLexico/AnalizadorLexico.o: /usr/include/stdc-predef.h
./Componentes/AnalizadorSintactico/AnalizadorSintactico.o: ./Componentes/SistemaEntrada/SistemaEntrada.h
./Componentes/AnalizadorSintactico/AnalizadorSintactico.o: ./Componentes/TablaSimbolos/TablaSimbolos.h
./Componentes/AnalizadorSintactico/AnalizadorSintactico.o: ./ArchivosComunes/TuplaLexemaId/TuplaLexemaId.h
./Componentes/AnalizadorSintactico/AnalizadorSintactico.o: ./Componentes/AnalizadorLexico/AnalizadorLexico.h
./Componentes/AnalizadorSintactico/AnalizadorSintactico.o: ./ArchivosComunes/Definiciones.h
./Componentes/AnalizadorSintactico/AnalizadorSintactico.o: ./ArchivosComunes/Utils/Utils.h
./Componentes/AnalizadorSintactico/AnalizadorSintactico.o: /usr/include/stdio.h
./Componentes/SistemaEntrada/SistemaEntrada.o: /usr/include/stdio.h
./Componentes/SistemaEntrada/SistemaEntrada.o: /usr/include/stdlib.h
./Componentes/SistemaEntrada/SistemaEntrada.o: ./Componentes/SistemaEntrada/SistemaEntrada.h
./Componentes/SistemaEntrada/SistemaEntrada.o: /usr/include/string.h
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
./Main/Main.o: ./Componentes/SistemaEntrada/SistemaEntrada.h
./Main/Main.o: ./Componentes/TablaSimbolos/TablaSimbolos.h
./Main/Main.o: ./ArchivosComunes/TuplaLexemaId/TuplaLexemaId.h
./Main/Main.o: ./Componentes/AnalizadorLexico/AnalizadorLexico.h
./Main/Main.o: ./Componentes/AnalizadorSintactico/AnalizadorSintactico.h
