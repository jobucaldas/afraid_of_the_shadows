SHELL=/bin/sh
.SUFFIXES:
.SUFFIXES: .cpp .o

all: aots

clean:
	-rm main.o aots.exe aots icon.res

icon.res: icon.rc
	windres icon.rc -O coff -o icon.res

main.o: main.cpp
	g++ -c main.cpp

aots: main.o
	g++ main.o -o aots -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

aots_win: main.o icon.res
	g++ main.o icon.res -o aots -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system