#CFLAGS -> donde directorios del proyecto donde haya ficheros.h
#OBJETOS -> los .c, pero cambiándoles la extensión por .o con la ruta desde donde está el makefile
#FUENTES -> los .c con la ruta desde donde está el makefile

CFLAGS=-I./ABBRojoNegro -I./Main
OBJETOS=./ABBRojoNegro/ABBRojoNegro.o ./Main/main.o
FUENTES=./ABBRojoNegro/ABBRojoNegro.c ./Main/main.c

ejecutable: $(OBJETOS)
	cc $(OBJETOS) -o ejecutable

depend:
	makedepend $(CFLAGS) $(FUENTES)# DO NOT DELETE

./ABBRojoNegro/ABBRojoNegro.o: ./ABBRojoNegro/ABBRojoNegro.h
./ABBRojoNegro/ABBRojoNegro.o: /usr/include/stdio.h /usr/include/stdlib.h
./Main/main.o: /usr/include/stdio.h /usr/include/stdlib.h
./Main/main.o: ./ABBRojoNegro/ABBRojoNegro.h
# DO NOT DELETE

./ABBRojoNegro/ABBRojoNegro.o: ./ABBRojoNegro/ABBRojoNegro.h
./ABBRojoNegro/ABBRojoNegro.o: /usr/include/stdio.h /usr/include/stdlib.h
