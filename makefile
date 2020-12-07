LIBRERIAS = -lglew32 -lglfw3 -lopengl32 
CODIGO = source/
all: main.exe quad.o window.o FileManager.o OrtographicCamera.o Shader.o Entity.o Sprite.o Debug.o Animation.o Game.o Level.o 
.PHONY: all
main.exe:$(CODIGO)main.cpp quad.o window.o FileManager.o OrtographicCamera.o Shader.o Entity.o Sprite.o Debug.o Animation.o Game.o Level.o 
	g++  -o main.exe  $(CODIGO)main.cpp quad.o window.o FileManager.o OrtographicCamera.o Shader.o Entity.o Sprite.o Debug.o Animation.o Game.o Level.o  -I .$(CODIGO)ScriptComponent.h  -I ./libs/ -L ./libs/ $(LIBRERIAS)
quad.o: $(CODIGO)quad.cpp $(CODIGO)quad.h
	g++ -c  $(CODIGO)quad.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS) 
window.o: $(CODIGO)window.cpp $(CODIGO)window.h
	g++ -c  $(CODIGO)window.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
FileManager.o: $(CODIGO)FileManager.cpp $(CODIGO)FileManager.h
	g++ -c  $(CODIGO)FileManager.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
OrtographicCamera.o: $(CODIGO)OrtographicCamera.cpp $(CODIGO)OrtographicCamera.h
	g++ -c  $(CODIGO)OrtographicCamera.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Shader.o: $(CODIGO)Shader.cpp $(CODIGO)Shader.h
	g++ -c  $(CODIGO)Shader.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Entity.o: $(CODIGO)Entity.cpp $(CODIGO)Entity.h
	g++ -c  $(CODIGO)Entity.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Sprite.o: $(CODIGO)Sprite.cpp $(CODIGO)Sprite.h
	g++ -c  $(CODIGO)Sprite.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Debug.o: $(CODIGO)Debug.cpp $(CODIGO)Debug.h
	g++ -c  $(CODIGO)Debug.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Animation.o: $(CODIGO)Animation.cpp $(CODIGO)Animation.h
	g++ -c  $(CODIGO)Animation.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Game.o: $(CODIGO)Game.cpp $(CODIGO)Game.h
	g++ -c  $(CODIGO)Game.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Level.o: $(CODIGO)Level.cpp $(CODIGO)Level.h
	g++ -c  $(CODIGO)Level.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Config.o: $(CODIGO)Config.cpp $(CODIGO)Config.h
	g++ -c  $(CODIGO)Config.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
clean:
	del quad.o
	del window.o
	del FileManager.o
	del OrtographicCamera.o
	del Shader.o
	del Entity.o
	del Sprite.o
	del Debug.o
	del Animation.o
	del Game.o
	del Level.o
	del main.exe

        