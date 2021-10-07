#CFLAGS -> donde directorios del proyecto donde haya ficheros.h
#OBJETOS -> los .c, pero cambiándoles la extensión por .o con la ruta desde donde está el makefile (la raíz del proyecto)
#FUENTES -> los .c con la ruta desde donde está el makefile (la raíz del proyecto)

CFLAGS=-g -Wall -I./ABBRojoNegro -I./TuplaLexemaId
OBJETOS=./Main/main.o ./ABBRojoNegro/ABBRojoNegro.o ./TuplaLexemaId/TuplaLexemaId.o
FUENTES=./Main/main.c ./ABBRojoNegro/ABBRojoNegro.c ./TuplaLexemaId/TuplaLexemaId.c

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
