CC=g++
ADD=-lX11 -std=c++14

main: clean R2G R3G Rot GW InterPlane
	$(CC) -o inter main.cpp R2Graph.o R3Graph.o Rotation.o gwindow.o DrawInterWindow.o $(ADD) -lm

R2G: R2Graph.cpp
	$(CC) -c R2Graph.cpp $(ADD)

R3G: R3Graph.cpp
	$(CC) -c R3Graph.cpp $(ADD)

Rot: Rotation.cpp
	$(CC) -c Rotation.cpp $(ADD)

InterPlane: DrawInterWindow.cpp
	$(CC) -c DrawInterWindow.cpp $(ADD)

GW: gwindow.cpp
	$(CC) -c gwindow.cpp $(ADD)

clean:
	rm -f *.o
