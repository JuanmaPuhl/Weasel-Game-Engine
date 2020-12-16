LIBRERIAS = -lglew32 -lglfw3 -lopengl32 
CODIGO = source/
all: main.exe quad.o window.o FileManager.o OrtographicCamera.o Shader.o Entity.o Sprite.o Debug.o  Game.o Level.o KeyboardControl.o Config.o ImageFileManager.o ComponentScript.o ComponentCamera.o
.PHONY: all
main.exe:$(CODIGO)main.cpp quad.o window.o FileManager.o OrtographicCamera.o Shader.o Entity.o Sprite.o Debug.o Game.o Level.o KeyboardControl.o Config.o ImageFileManager.o ComponentScript.o ComponentCamera.o $(CODIGO)Entities/Scripts.h
	g++  -o main.exe  $(CODIGO)main.cpp quad.o window.o FileManager.o OrtographicCamera.o Shader.o Entity.o Sprite.o Debug.o Game.o Level.o KeyboardControl.o Config.o ImageFileManager.o ComponentScript.o ComponentCamera.o -I .$(CODIGO)ScriptComponent.h -I.$(CODIGO)Entities/Scripts.h  -I ./libs/ -L ./libs/ $(LIBRERIAS)
quad.o: $(CODIGO)Graphics/quad.cpp $(CODIGO)Graphics/quad.h
	g++ -c  $(CODIGO)Graphics/quad.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS) 
window.o: $(CODIGO)Graphics/window.cpp $(CODIGO)Graphics/window.h
	g++ -c  $(CODIGO)Graphics/window.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
FileManager.o: $(CODIGO)FileManagement/FileManager.cpp $(CODIGO)FileManagement/FileManager.h
	g++ -c  $(CODIGO)FileManagement/FileManager.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
ImageFileManager.o: $(CODIGO)FileManagement/ImageFileManager.cpp $(CODIGO)FileManagement/ImageFileManager.h
	g++ -c  $(CODIGO)FileManagement/ImageFileManager.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
OrtographicCamera.o: $(CODIGO)Entities/OrtographicCamera.cpp $(CODIGO)Entities/OrtographicCamera.h
	g++ -c  $(CODIGO)Entities/OrtographicCamera.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Shader.o: $(CODIGO)Graphics/Shader.cpp $(CODIGO)Graphics/Shader.h
	g++ -c  $(CODIGO)Graphics/Shader.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Entity.o: $(CODIGO)Entities/Entity.cpp $(CODIGO)Entities/Entity.h
	g++ -c  $(CODIGO)Entities/Entity.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Sprite.o: $(CODIGO)Graphics/Sprite.cpp $(CODIGO)Graphics/Sprite.h
	g++ -c  $(CODIGO)Graphics/Sprite.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Debug.o: $(CODIGO)Debug.cpp $(CODIGO)Debug.h
	g++ -c  $(CODIGO)Debug.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Game.o: $(CODIGO)General/Game.cpp $(CODIGO)General/Game.h
	g++ -c  $(CODIGO)General/Game.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Level.o: $(CODIGO)General/Level.cpp $(CODIGO)General/Level.h
	g++ -c  $(CODIGO)General/Level.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Config.o: $(CODIGO)Config.cpp $(CODIGO)Config.h
	g++ -c  $(CODIGO)Config.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
KeyboardControl.o: $(CODIGO)Controls/KeyboardControl.cpp $(CODIGO)Controls/KeyboardControl.h
	g++ -c  $(CODIGO)Controls/KeyboardControl.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
ComponentScript.o: $(CODIGO)Entities/ComponentScript.cpp $(CODIGO)Entities/ComponentScript.h $(CODIGO)Entities/Component.h
	g++ -c  $(CODIGO)Entities/ComponentScript.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
ComponentCamera.o: $(CODIGO)Entities/ComponentCamera.cpp $(CODIGO)Entities/ComponentCamera.h $(CODIGO)Entities/Component.h
	g++ -c  $(CODIGO)Entities/ComponentCamera.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
clean:
	del quad.o
	del window.o
	del FileManager.o
	del OrtographicCamera.o
	del Shader.o
	del Entity.o
	del Sprite.o
	del Debug.o
	del Game.o
	del Level.o
	del KeyboardControl.o
	del Config.o
	del ImageFileManager.o
	del ComponentScript.o
	del ComponentCamera.o
	del main.exe

        