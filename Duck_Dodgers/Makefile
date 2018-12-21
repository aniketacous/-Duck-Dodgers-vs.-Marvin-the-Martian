CFLAGS = -c -I$(HOME)/Programming/include
LFLAGS = -L$(HOME)/Programming/lib
LIBS = -ldataStructures

project3: main.o 
	g++ $(LFLAGS) -o project3 main.o $(LIBS)

main.o: main.cpp
	g++ $(CFLAGS) main.cpp

clean:
	 rm -f project3 main.o  
