all: compile link open

compile:
	g++ -c main.cpp -I"C:\SFML-2.5.1\include"

link: 
	g++ main.o -o main -L"C:\SFML-2.5.1\lib" -lsfml-graphics -lsfml-window -lsfml-system

open:
	./main.exe

clean:
	rm -f main *.o