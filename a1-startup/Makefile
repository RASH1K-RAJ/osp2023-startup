
##
 # startup code provided by Paul Miller for COSC1114 - Operating Systems
 # Principles
 ##

# provide make targets here to build the two programs 
FILES = main.cpp Reader.cpp Writer.cpp
OBJECTS = copier_files/main.o copier_files/Reader.o copier_files/Writer.o
MT_OBJECTS = mtcopier_files/main.o mtcopier_files/reader.o mtcopier_files/writer.o
FLAGS = g++ -g -Wall -Werror -std=c++20 -O
LD_FLAGS = -lpthread

.default: all

all: copier

copier: $(OBJECTS)
	$(FLAGS) -o $@ $^

mtcopier: $(MT_OBJECTS)
	${FLAGS} -o $@ $^ $(LD_FLAGS)

%.o: %.cpp
	$(FLAGS) -c $^ -o $@

clean: 
	rm -f copier mtcopier mtcopier_files/*.o copier_files/*.o


