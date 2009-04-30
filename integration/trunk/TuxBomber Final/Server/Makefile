#make for TuxBomber server

CC=g++
CFLAGS=-lSDL -lSDL_image -lSDL_mixer -lSDL_gfx -lSDL_ttf

ex: main.o s_network.o s_bomb.o serialize.o s_explosion.o s_init.o s_player.o utils.o init.o statusbar.o user_map.o n_network.o
		$(CC) $(CFLAGS) main.o s_network.o s_bomb.o serialize.o s_explosion.o s_init.o s_player.o utils.o init.o statusbar.o user_map.o n_network.o -o TuxBomber_Server

clean:
		rm -f *.o *.bak.ex

main.o: main.cpp
	$(CC) $(CFLAGS) -O -c main.cpp

s_network.o: s_network.cpp
	$(CC) $(CFLAGS) -O -c s_network.cpp

s_bomb.o: s_bomb.cpp
	$(CC) $(CFLAGS) -O -c s_bomb.cpp

serialize.o: serialize.cpp
	$(CC) $(CFLAGS) -O -c serialize.cpp

s_explosion.o: s_explosion.cpp
	$(CC) $(CFLAGS) -O -c s_explosion.cpp

s_init.o: s_init.cpp
	$(CC) $(CFLAGS) -O -c s_init.cpp

s_player.o: s_player.cpp
	$(CC) $(CFLAGS) -O -c s_player.cpp

utils.o: utils.cpp
	$(CC) $(CFLAGS) -O -c utils.cpp

init.o: Map/init.cpp
	$(CC) $(CFLAGS) -O -c Map/init.cpp

statusbar.o: Map/statusbar.cpp
	$(CC) $(CFLAGS) -O -c Map/statusbar.cpp

user_map.o: Map/user_map.cpp
	$(CC) $(CFLAGS) -O -c Map/user_map.cpp

n_network.o: n_network.cpp
	$(CC) $(CFLAGS) -O -c n_network.cpp
