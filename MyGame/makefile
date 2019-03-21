OBJ =  
PROG = mygame 
CFLAGS += -Wall -g
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system 

$(PROG) : $(OBJ) main.cpp
	$(CC) -o $@ $^ $(CFLAGS) 

main.c : $(HDR)
	$(OBJ) : $(HDR)
clean: 
	$(RM) $(OBJ) $(PROG)
