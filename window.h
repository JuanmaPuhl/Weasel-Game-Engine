#include <GL/glew.h>
#include <GLFW/glfw3.h>
namespace window
{
    /**
     *@brief Inicia la ventana con unas dimensiones determinadas
    *@param width el ancho de la ventana
    *@param height el alto de la ventana
    *@return la ventana generada*/
    GLFWwindow* window_init(int width, int height);
    /**
     * @brief Hace ciclar la ventana con la funcion que se haya determinado
     * @param loop_function la funcion que queremos que se ejecute en el loop
     * @return int el codigo de finalizacion
     */
    int window_loop(GLFWwindow* window, void (*loop_function)(float));

    void set_key_callback(GLFWwindow*window,void callback(GLFWwindow*,int,int,int,int));
}
    

