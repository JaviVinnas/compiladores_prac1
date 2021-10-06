#CFLAGS -> donde directorios del proyecto donde haya ficheros.h
#OBJETOS -> los .c, pero cambiándoles la extensión por .o con la ruta desde donde está el makefile
#FUENTES -> los .c con la ruta desde donde está el makefile

CFLAGS=-I./ABBRojoNegro -I./TuplaLexemaId -I./Main 
OBJETOS=./ABBRojoNegro/ABBRojoNegro.o ./TuplaLexemaId/TuplaLexemaId.o ./Main/main.o
FUENTES=./ABBRojoNegro/ABBRojoNegro.c ./TuplaLexemaId/TuplaLexemaId.c ./Main/main.c

ejecutable: $(OBJETOS)
	gcc -g $(OBJETOS) -o ejecutable

depend:
	makedepend $(CFLAGS) $(FUENTES)

# DO NOT DELETE

./ABBRojoNegro/ABBRojoNegro.o: ./ABBRojoNegro/ABBRojoNegro.h
./ABBRojoNegro/ABBRojoNegro.o: ./TuplaLexemaId/TuplaLexemaId.h
./ABBRojoNegro/ABBRojoNegro.o: /usr/include/stdio.h /usr/include/stdlib.h
./ABBRojoNegro/ABBRojoNegro.o: /usr/include/string.h
./TuplaLexemaId/TuplaLexemaId.o: ./TuplaLexemaId/TuplaLexemaId.h
./TuplaLexemaId/TuplaLexemaId.o: /usr/include/string.h
./Main/main.o: /usr/include/stdio.h /usr/include/stdlib.h
./Main/main.o: ./ABBRojoNegro/ABBRojoNegro.h ./TuplaLexemaId/TuplaLexemaId.h