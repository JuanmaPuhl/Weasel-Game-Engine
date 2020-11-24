main:main.cpp
	gcc -o main.exe -I ./libs/ main.cpp -L ./libs/ -lglew32 -lglfw3 -lopengl32
clean:
	del main.exe