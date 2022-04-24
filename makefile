# Variables to control Makefile operation

CC = g++
MYDIR = .
objCFLAGS = -Wextra -g -fmax-errors=10
binCFLAGS = -Wall -g -lsfml-graphics -lsfml-window -lsfml-system

# ****************************************************
# Targets needed to bring the executable up to date

main: main.o graphics.o ant.o
	$(CC) $(binCFLAGS) -o bin/main obj/main.o obj/graphics.o obj/entities/ant.o


graphics.o:
	$(CC) $(objCFLAGS) -o obj/graphics.o -c src/graphics.cpp

ant.o:
	$(CC) $(objCFLAGS) -o obj/entities/ant.o -c src/entities/ant.cpp

main.o:
	$(CC) $(objCFLAGS) -o obj/main.o -c src/main.cpp
