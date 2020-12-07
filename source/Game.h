#ifndef GAME_H
#define GAME_H
#include "Level.h"
class Game
{
    public:
    Game();
    ~Game();
    /**
     * @brief Añadir un nivel al juego
     * 
     * @param level el nivel que se desea añadir
     * @return el identificador del nivel
     */
    int addLevel(Level* level);
    /**
     * @brief Establece el nivel actual
     * 
     * @param levelId id del nivel (En este caso es el numero en el que se inserto)
     */
    void setLevel(int levelId);
    /**
     * @brief Obtiene el nivel actual
     * 
     * @return Level* una referencia al nivel actual
     */
    Level* getCurrentLevel();
    /**
     * @brief Actualiza el nivel
     * 
     */
    void onUpdate();
    /**
     * @brief Renderiza el nivel
     * 
     */
    void render();
    private:
    std::vector<Level*> levels;
    Level* currentLevel = NULL;
};
#endif