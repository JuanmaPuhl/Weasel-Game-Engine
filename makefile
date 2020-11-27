LIBRERIAS = -lglew32 -lglfw3 -lopengl32 
all: main.exe quad.o window.o FileManager.o OrtographicCamera.o Shader.o Entity.o
.PHONY: all
main.exe:main.cpp quad.o window.o FileManager.o OrtographicCamera.o Shader.o Entity.o
	g++  -o main.exe  main.cpp quad.o window.o FileManager.o OrtographicCamera.o Shader.o Entity.o -I ./libs/ -L ./libs/ $(LIBRERIAS)
quad.o: quad.cpp quad.h
	g++ -c  quad.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS) 
window.o: window.cpp window.h
	g++ -c  window.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
FileManager.o: FileManager.cpp FileManager.h
	g++ -c  FileManager.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
OrtographicCamera.o: OrtographicCamera.cpp OrtographicCamera.h
	g++ -c  OrtographicCamera.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Shader.o: Shader.cpp Shader.h
	g++ -c  Shader.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Entity.o: Entity.cpp Entity.h
	g++ -c  Entity.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
clean:
	del quad.o
	del window.o
	del FileManager.o
	del OrtographicCamera.o
	del Shader.o
	del Entity.o
	del main.exe

        