test: test.c color.o bitmap.o makefile
	gcc -ansi -Wall -O test.c color.o bitmap.o -o test

color.o: ../src/color.c ../src/color.h makefile
	gcc -ansi -Wall -O ../src/color.c -c

jpeg.o: ../src/jpeg.c ../src/jpeg.h makefile
	gcc -ansi -Wall -O ../src/jpeg.c -c

clear:
	rm test *.o