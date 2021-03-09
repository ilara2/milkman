
CFLAG = -I ./include
LFLAG = -lrt -lX11 -lGLU -lGL -lm -std=c++11
PFILE = utils/*.cpp scenes/*.cpp enemy/*.cpp player/*.cpp

all: main

main: themilkman.cpp
	g++ $(CFLAG) $(PFILE) themilkman.cpp utils/libggfonts.a -Wall -Wextra $(LFLAG) -othemilkman.out

redo: main
	./themilkman.out

clean:
	rm -f themilkman.out
