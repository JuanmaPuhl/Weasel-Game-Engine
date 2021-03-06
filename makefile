LIBRERIAS = -llua54 -lglew32 -lglfw3 -lopengl32 -lcomdlg32 -lirrKlang
CODIGO = source/
all: main.exe quad.o window.o FileManager.o Shader.o Entity.o Sprite.o Debug.o  Game.o Level.o KeyboardControl.o Config.o ImageFileManager.o ComponentScript.o ComponentCamera.o SpriteAttribute.o ColorAttribute.o Lua_Entity.o Lua_Level.o Lua_Game.o LuaScriptComponent.o ComponentCollisionBox.o ComponentParticle.o Particle.o Lua_Keyboard.o Lua_Attribute.o Lua_Sprite.o ComponentMusic.o Lua_Component.o PixelizationAttribute.o Sharpen.o DilationAttribute.o ejecutable.exe
.PHONY: all
main.exe:$(CODIGO)main.cpp quad.o window.o FileManager.o Shader.o Entity.o Sprite.o Debug.o Game.o Level.o KeyboardControl.o Config.o ImageFileManager.o ComponentScript.o ComponentCamera.o SpriteAttribute.o ColorAttribute.o imgui_widgets.o imgui.o imgui_draw.o imgui_tables.o imgui_impl_opengl3.o imgui_impl_glfw.o imgui_demo.o Gui.o Lua_Entity.o Lua_Level.o Lua_Game.o LuaScriptComponent.o  ComponentCollisionBox.o  Lua_Component.o ComponentParticle.o Particle.o ComponentMusic.o Lua_Keyboard.o Lua_Attribute.o Lua_Sprite.o PixelizationAttribute.o Sharpen.o DilationAttribute.o $(CODIGO)Entities/Scripts.h 
	g++  -o main.exe  $(CODIGO)main.cpp quad.o window.o FileManager.o Shader.o Entity.o Sprite.o Debug.o Game.o Level.o KeyboardControl.o Config.o ImageFileManager.o ComponentScript.o ComponentCamera.o SpriteAttribute.o ColorAttribute.o imgui.o imgui_widgets.o imgui_draw.o imgui_tables.o imgui_impl_opengl3.o imgui_impl_glfw.o imgui_demo.o Gui.o Lua_Entity.o Lua_Level.o Lua_Game.o LuaScriptComponent.o ComponentCollisionBox.o Lua_Component.o ComponentParticle.o ComponentMusic.o Particle.o Lua_Keyboard.o Lua_Attribute.o Lua_Sprite.o PixelizationAttribute.o Sharpen.o DilationAttribute.o -I .$(CODIGO)ScriptComponent.h -I.$(CODIGO)Entities/Scripts.h -I ./libs/  -L ./libs/ $(LIBRERIAS)
quad.o: $(CODIGO)Graphics/quad.cpp $(CODIGO)Graphics/quad.h
	g++ -c  $(CODIGO)Graphics/quad.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS) 
window.o: $(CODIGO)Graphics/window.cpp $(CODIGO)Graphics/window.h
	g++ -c  $(CODIGO)Graphics/window.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
FileManager.o: $(CODIGO)FileManagement/FileManager.cpp $(CODIGO)FileManagement/FileManager.h
	g++ -c  $(CODIGO)FileManagement/FileManager.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
ImageFileManager.o: $(CODIGO)FileManagement/ImageFileManager.cpp $(CODIGO)FileManagement/ImageFileManager.h
	g++ -c  $(CODIGO)FileManagement/ImageFileManager.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
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
LuaScriptComponent.o: $(CODIGO)Entities/LuaScriptComponent.cpp $(CODIGO)Entities/LuaScriptComponent.h
	g++ -c $(CODIGO)Entities/LuaScriptComponent.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
SpriteAttribute.o: $(CODIGO)Entities/SpriteAttribute.cpp $(CODIGO)Entities/SpriteAttribute.h $(CODIGO)Entities/GraphicAttribute.h
	g++ -c  $(CODIGO)Entities/SpriteAttribute.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
ColorAttribute.o: $(CODIGO)Entities/ColorAttribute.cpp $(CODIGO)Entities/ColorAttribute.h $(CODIGO)Entities/GraphicAttribute.h
	g++ -c  $(CODIGO)Entities/ColorAttribute.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
PixelizationAttribute.o: $(CODIGO)Entities/PixelizationAttribute.cpp $(CODIGO)Entities/PixelizationAttribute.h $(CODIGO)Entities/GraphicAttribute.h
	g++ -c  $(CODIGO)Entities/PixelizationAttribute.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Sharpen.o: $(CODIGO)Entities/Sharpen.cpp $(CODIGO)Entities/Sharpen.h $(CODIGO)Entities/GraphicAttribute.h
	g++ -c  $(CODIGO)Entities/Sharpen.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
DilationAttribute.o: $(CODIGO)Entities/DilationAttribute.cpp $(CODIGO)Entities/DilationAttribute.h $(CODIGO)Entities/GraphicAttribute.h
	g++ -c  $(CODIGO)Entities/DilationAttribute.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
imgui.o:
	g++ -c ./libs/imgui/imgui.cpp -I ./libs/
imgui_draw.o:
	g++ -c ./libs/imgui/imgui_draw.cpp -I ./libs/
imgui_widgets.o: 
	g++ -c ./libs/imgui/imgui_widgets.cpp -I ./libs/
imgui_tables.o:
	g++ -c ./libs/imgui/imgui_tables.cpp -I ./libs/
imgui_impl_opengl3.o:
	g++ -c ./libs/imgui/imgui_impl_opengl3.cpp -I ./libs/
imgui_impl_glfw.o:
	g++ -c ./libs/imgui/imgui_impl_glfw.cpp -I ./libs/
imgui_demo.o:
	g++ -c ./libs/imgui/imgui_demo.cpp -I ./libs/
Gui.o: $(CODIGO)Graphics/Gui.h $(CODIGO)Graphics/Gui.cpp $(CODIGO)Utils/WindowsDialogs.h
	g++ -c $(CODIGO)Graphics/Gui.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Lua_Entity.o: $(CODIGO)Scripts/Lua_Entity.h $(CODIGO)Scripts/Lua_Entity.cpp
	g++ -c $(CODIGO)Scripts/Lua_Entity.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Lua_Level.o: $(CODIGO)Scripts/Lua_Level.h $(CODIGO)Scripts/Lua_Level.cpp
	g++ -c $(CODIGO)Scripts/Lua_Level.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Lua_Game.o: $(CODIGO)Scripts/Lua_Game.h $(CODIGO)Scripts/Lua_Game.cpp
	g++ -c $(CODIGO)Scripts/Lua_Game.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
ComponentCollisionBox.o: $(CODIGO)Entities/ComponentCollisionBox.h $(CODIGO)Entities/ComponentCollisionBox.cpp
	g++ -c $(CODIGO)Entities/ComponentCollisionBox.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
ComponentParticle.o: $(CODIGO)Entities/ComponentParticle.h $(CODIGO)Entities/ComponentParticle.cpp
	g++ -c $(CODIGO)Entities/ComponentParticle.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Particle.o: $(CODIGO)Entities/Particle.h $(CODIGO)Entities/Particle.cpp
	g++ -c $(CODIGO)Entities/Particle.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Lua_Keyboard.o: $(CODIGO)Scripts/Lua_Keyboard.h $(CODIGO)Scripts/Lua_Keyboard.cpp
	g++ -c $(CODIGO)Scripts/Lua_Keyboard.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Lua_Attribute.o: $(CODIGO)Scripts/Lua_Attribute.h $(CODIGO)Scripts/Lua_Attribute.cpp
	g++ -c $(CODIGO)Scripts/Lua_Attribute.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Lua_Sprite.o: $(CODIGO)Scripts/Lua_Sprite.h $(CODIGO)Scripts/Lua_Sprite.cpp 
	g++ -c $(CODIGO)Scripts/Lua_Sprite.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
Lua_Component.o: $(CODIGO)Scripts/Lua_Component.h $(CODIGO)Scripts/Lua_Component.cpp 
	g++ -c $(CODIGO)Scripts/Lua_Component.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
ComponentMusic.o: $(CODIGO)Entities/ComponentMusic.h $(CODIGO)Entities/ComponentMusic.cpp
	g++ -c $(CODIGO)Entities/ComponentMusic.cpp -I ./libs/ -L ./libs/ $(LIBRERIAS)
ejecutable.exe:$(CODIGO)ejecutable.cpp quad.o window.o FileManager.o Shader.o Entity.o Sprite.o Debug.o Game.o Level.o KeyboardControl.o Config.o ImageFileManager.o ComponentScript.o ComponentCamera.o SpriteAttribute.o ColorAttribute.o imgui_widgets.o imgui.o imgui_draw.o imgui_tables.o imgui_impl_opengl3.o imgui_impl_glfw.o imgui_demo.o Gui.o Lua_Entity.o Lua_Level.o Lua_Game.o LuaScriptComponent.o  ComponentCollisionBox.o  Lua_Component.o ComponentParticle.o Particle.o ComponentMusic.o Lua_Keyboard.o Lua_Attribute.o Lua_Sprite.o PixelizationAttribute.o Sharpen.o DilationAttribute.o $(CODIGO)Entities/Scripts.h 
	g++  -o ejecutable.exe  $(CODIGO)ejecutable.cpp quad.o window.o FileManager.o Shader.o Entity.o Sprite.o Debug.o Game.o Level.o KeyboardControl.o Config.o ImageFileManager.o ComponentScript.o ComponentCamera.o SpriteAttribute.o ColorAttribute.o imgui.o imgui_widgets.o imgui_draw.o imgui_tables.o imgui_impl_opengl3.o imgui_impl_glfw.o imgui_demo.o Gui.o Lua_Entity.o Lua_Level.o Lua_Game.o LuaScriptComponent.o ComponentCollisionBox.o Lua_Component.o ComponentParticle.o ComponentMusic.o Particle.o Lua_Keyboard.o Lua_Attribute.o Lua_Sprite.o PixelizationAttribute.o Sharpen.o DilationAttribute.o -I .$(CODIGO)ScriptComponent.h -I.$(CODIGO)Entities/Scripts.h -I ./libs/  -L ./libs/ $(LIBRERIAS)

clean:
	del quad.o
	del window.o
	del FileManager.o
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
	del SpriteAttribute.o
	del ColorAttribute.o
	del imgui.o 
	del imgui_draw.o
	del imgui_widgets.o
	del imgui_tables.o
	del imgui_impl_opengl3.o
	del imgui_impl_glfw.o
	del imgui_demo.o
	del Gui.o
	del Lua_Entity.o
	del Lua_Level.o
	del Lua_Game.o
	del LuaScriptComponent.o
	del ComponentCollisionBox.o
	del ComponentParticle.o
	del Particle.o
	del Lua_Keyboard.o
	del Lua_Attribute.o
	del Lua_Sprite.o
	del ComponentMusic.o
	del Lua_Component.o
	del PixelizationAttribute.o
	del Sharpen.o
	del DilationAttribute.o
	del main.exe
	del ejecutable.exe

        