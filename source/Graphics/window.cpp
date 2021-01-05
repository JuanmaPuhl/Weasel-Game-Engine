#include "window.h"
#include <stdio.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
float currentFrame = 0.0f;

void error_callback(int code, const char* description)
{
    printf("GLFW ERROR::code: %d, description: %s.\n",code, description);
    printf("Window::Terminando ejecucion...\n");
    exit(code);
}


GLFWwindow* window::window_init(int width, int height)
{
    /*=====================INICIA CREACION DE VENTANA==========================*/
    GLFWwindow* window;
    if (!glfwInit())
    {
        return NULL;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    //glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);
    window = glfwCreateWindow(width, height, "Game", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return NULL;
    }
    
    //glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();
    glGetError();
    glfwSetKeyCallback(window,key_callback);
    //glfwSetMouseButtonCallback(window,ImGui_ImplGlfw_MouseButtonCallback);
    glfwSetErrorCallback(error_callback);
    /*====================TERMINA CREACION DE VENTANA==========================*/
    glViewport(0, 0, width, height);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    return window;
}


int window::window_loop(GLFWwindow* window,void (*loop_function)(double))
{
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
      glfwPollEvents();
      glfwSwapInterval(0);
      currentFrame = glfwGetTime();
      deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;
      //Llamo la función del usuario
      loop_function(deltaTime);
      
      
      glfwSwapBuffers(window);
        
    }
    glfwTerminate();
    return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  //
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
  if (key >= 0 && key < 1024)
  {
    if (action == GLFW_PRESS)
    {
      keyboardControl->setKey(key,true);
    }
    else 
        if (action == GLFW_RELEASE)
        {
          keyboardControl->setKey(key,false);
        }
    
  }
  //ImGui_ImplGlfw_KeyCallback(window,key,scancode,action,mode);
}