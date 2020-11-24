#include "game.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
/*
@brief Inicia la ventana con unas dimensiones determinadas y ejecuta la funcion de loop
@param width el ancho de la ventana
@param height el alto de la ventana
@param loop_function la funcion que se desea usar de loop, necesita un unico parametro float para el deltaTime
@return el codigo de finalizacion*/
int window_init(int width, int height, void (*loop_function)(float));
