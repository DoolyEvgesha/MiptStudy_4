OBJ = dictionary.o list.o reader.o 
PROG1 = wf1
PROG2 = wf2
CFLAGS += -Wall -g
CXXFLAGS += -std=c++11 -isystem ${GTEST_DIR}/include -I${GTEST_DIR} -pthread 
HDR = list.h reader.h dictionary.h

#g++ -std=c++11 -isystem ${GTEST_DIR}/include -I${GTEST_DIR} \
#        -pthread -c ${GTEST_DIR}/src/gtest-all.cc


all : $(PROG1) $(PROG2)

$(PROG1) : $(OBJ) main.c
	$(CC) -o $@ $^ $(CFLAGS) -DLIST=dict_create

$(PROG2) : $(OBJ) main.c
	$(CC) -o $@ $^ $(CFLAGS) -DLIST=list_create

main.c : $(HDR)
$(OBJ) : $(HDR)

gtest-all.o : ${GTEST_DIR}/src/gtest-all.cc
	$(CXX) $(CXXFLAGS) -o $@ -c $^

clean: 
	$(RM) $(OBJ) $(PROG)
