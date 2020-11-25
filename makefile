all: main.exe quad.o window.o
.PHONY: all
main.exe:main.cpp quad.o window.o
	g++  -o main.exe  main.cpp quad.o window.o -I ./libs/ -L ./libs/ -lglew32 -lglfw3 -lopengl32 
quad.o: quad.cpp quad.h
	g++ -c  quad.cpp -I ./libs/ -L ./libs/ -lglew32 -lglfw3 -lopengl32 
window.o: window.cpp window.h
	g++ -c  window.cpp -I ./libs/ -L ./libs/ -lglew32 -lglfw3 -lopengl32 
clean:
	del quad.o
	del window.o
	del main.exe