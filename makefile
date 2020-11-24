all: main.exe
.PHONY: all
main.exe:main.cpp
	gcc -o main.exe -I ./libs/ *.cpp -L ./libs/ -lglew32 -lglfw3 -lopengl32
clean:
	del main.exe