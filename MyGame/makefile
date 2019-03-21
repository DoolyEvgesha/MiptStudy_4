OBJ=main.o 
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS += -std=c++11
PROG=MyGame

all:${PROG} 

main.o:main.cpp
	g++ -c main.cpp -o main.o

${PROG}:main.o
	g++ main.o -o ${PROG} ${LIBS} 


clean:
	$(RM) $(PROG)
