zad1: zad1.y zad1.l
	bison -d -o zad1y.cpp zad1.y
	flex -o zad1l.c zad1.l
	g++ -o zad1 zad1y.cpp zad1l.c

clean:
	rm zad1y.cpp zad1y.hpp zad1l.c zad1
	
.PHONY:
	zad1
