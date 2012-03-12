# MAKEFILE FOR TUXBOMBER PROJECT
# -Created by The Data Communication Students of BCIT, 2009

CC = g++
CFLAGS = -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lSDL_gfx

TuxBomber: Funcs.o InputOkCancel.o logic.o main.o MainMenu.o network.o n_network.o OkCancel.o POptMenu.o session.o s_player.o statusbar.o textbox.o user_map.o
	$(CC) $(CFLAGS) Funcs.o InputOkCancel.o logic.o main.o MainMenu.o network.o n_network.o OkCancel.o POptMenu.o session.o s_player.o statusbar.o textbox.o user_map.o -o TuxBomber

clean:
	rm -f *.o *.bak TuxBomber

Funcs.o: source/Funcs.cpp
	$(CC) $(CFLAGS) -O -c source/Funcs.cpp

InputOkCancel.o: source/InputOkCancel.cpp
	$(CC) $(CFLAGS) -O -c source/InputOkCancel.cpp

logic.o: source/logic.cpp
	$(CC) $(CFLAGS) -O -c source/logic.cpp

main.o: source/main.cpp
	$(CC) $(CFLAGS) -O -c source/main.cpp

MainMenu.o: source/MainMenu.cpp
	$(CC) $(CFLAGS) -O -c source/MainMenu.cpp

network.o: source/network.cpp
	$(CC) $(CFLAGS) -O -c source/network.cpp

n_network.o: source/n_network.cpp
	$(CC) $(CFLAGS) -O -c source/n_network.cpp

OkCancel.o: source/OkCancel.cpp
	$(CC) $(CFLAGS) -O -c source/OkCancel.cpp

POptMenu.o: source/POptMenu.cpp
	$(CC) $(CFLAGS) -O -c source/POptMenu.cpp

session.o: source/session.cpp
	$(CC) $(CFLAGS) -O -c source/session.cpp

s_player.o: source/s_player.cpp
	$(CC) $(CFLAGS) -O -c source/s_player.cpp

statusbar.o: source/statusbar.cpp
	$(CC) $(CFLAGS) -O -c source/statusbar.cpp

textbox.o: source/textbox.cpp
	$(CC) $(CFLAGS) -O -c source/textbox.cpp

user_map.o: source/user_map.cpp
	$(CC) $(CFLAGS) -O -c source/user_map.cpp
