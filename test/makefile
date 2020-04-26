test: test.c color.o bitmap.o makefile
	gcc -ansi -Wall -O test.c color.o bitmap.o -o test

color.o: ../src/color.c makefile
	gcc -ansi -Wall -O ../src/color.c -c

bitmap.o: ../src/bitmap.c makefile
	gcc -ansi -Wall -O ../src/bitmap.c -c

clear:
	rm test *.o