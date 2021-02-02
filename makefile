
CFLAGS = -I ./include
LFLAGS = -lrt -lX11 -lGLU -lGL -lm -std=c++11
PFILES = image.cpp x11_wrapper.cpp \
			player.cpp enemy.cpp bottle.cpp \
			global.cpp scenes.cpp displays.cpp \
			start.cpp cloud.cpp level_1.cpp level_2.cpp

all: main

main: themilkman.cpp
	g++ $(CFLAGS) $(PFILES) themilkman.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -othemilkman.out

redo: main
	./themilkman.out

clean:
	rm -f themilkman.out
