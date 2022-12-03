test: test.o
	g++ test.o -o test

test.o: test.cpp
	g++ -c test.cpp

MENA: MENA.o
	g++ MENA.o -o MENA

MENA.o: MENA.cpp
	g++ -c MENA.cpp

clean:
	rm *.o driver test MENA
