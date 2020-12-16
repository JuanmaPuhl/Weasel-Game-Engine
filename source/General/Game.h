#ifndef GAME_H
#define GAME_H
#include "Level.h"
#include "../Graphics/Shader.h"
#include "../Config.h"
#include "../Graphics/window.h"
#include "../Graphics/Quad.h"

struct GameData
    {
        GLFWwindow* window = NULL;
        std::vector<Level*> levels;
        Level* currentLevel = NULL;
        Shader* shader = NULL;
    };
    extern GameData* gamedata;
namespace Game
{
    void init(int width, int height);
    Level* addLevel();
    Level* getCurrentLevel();
    void setLevel(int level);
    void onUpdate(double deltaTime);
    void render(double deltaTime);
    GLFWwindow* getWindow();
    void loop();
    void close();
}





/* class Game
{
    public:
    Game(int width, int height);
    ~Game(); */
    /**
     * @brief Añadir un nivel al juego
     * 
     * @param level el nivel que se desea añadir
     * @return el identificador del nivel
     */
/*     Level* addLevel(); */
    /**
     * @brief Establece el nivel actual
     * 
     * @param levelId id del nivel (En este caso es el numero en el que se inserto)
     */
/*     void setLevel(int levelId); */
    /**
     * @brief Obtiene el nivel actual
     * 
     * @return Level* una referencia al nivel actual
     */
/*     Level* getCurrentLevel(); */
    /**
     * @brief Actualiza el nivel
     * 
     */
/*     void onUpdate(double deltaTime); */
    /**
     * @brief Renderiza el nivel
     * 
     */
/*     void render(double deltaTime);
    GLFWwindow* window = NULL;
    private:
    std::vector<Level*> levels;
    Level* currentLevel = NULL;
    Shader* shader = NULL; 
    
};*/
#endif