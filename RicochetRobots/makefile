CFLAGS=-Wall

all: RicochetRobots

RicochetRobots: main.o game.o board.o interface.o player.o utils.o
	gcc main.o game.o board.o interface.o player.o utils.o -lncurses -lmenu -o RicochetRobots

clean:
	rm -rf *.o RicochetRobots