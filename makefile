CC:=g++
STD:=-std=c++17
FLAGS:=-g -O2
LIBS:=-lm
OUTPUT:=-obin/pakit
SRC:=src/*.cpp

main:
	@$(CC) $(SRC) $(LIBS) $(FLAGS) $(STD) $(OUTPUT)
