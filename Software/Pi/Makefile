driver: driver.o
	g++ driver.o -o driver -lwiringPi

driver.o: driver.cpp
	g++ -c driver.cpp -lwiringPi

clean:
	rm *.o driver
