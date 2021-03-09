
CFLAG = -I ./include
LFLAG = -lrt -lX11 -lGLU -lGL -lm -std=c++11
# PFILE = utils/image.cpp x11_wrapper.cpp \
# 	global.cpp scenes.cpp displays.cpp \
# 	player.cpp enemy/enemy.cpp bottle.cpp \
# 	start.cpp cloud.cpp level_1.cpp level_2.cpp
PFILE = utils/*.cpp scenes/*.cpp enemy/*.cpp player/*.cpp

all: main

main: themilkman.cpp
	g++ $(CFLAG) $(PFILE) themilkman.cpp utils/libggfonts.a -Wall -Wextra $(LFLAG) -othemilkman.out
	# g++ $(CFLAG) $(PFILE) themilkman.cpp utils/libggfonts.a -Wall -Wextra $(LFLAG) -othemilkman.out

redo: main
	./themilkman.out

clean:
	rm -f themilkman.out
