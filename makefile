SHELL=/bin/sh
.SUFFIXES:
.SUFFIXES: .cpp .o

install: aots

clean:
	-rm main.o aots.exe aots icon.res

icon.res: Assets/icon.rc
	windres Assets/icon.rc -O coff -o Assets/icon.res

main.o: main.cpp
	g++ -c main.cpp 

aots: main.o
	g++ main.o -o aots -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

win: main.o icon.res
	g++ main.o Assets/icon.res -o aots -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system