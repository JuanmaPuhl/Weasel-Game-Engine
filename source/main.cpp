#include "Graphics/window.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "Entities/Entity.h"
#include "Graphics/Sprite.h"
#include "Entities/ScriptComponent.h"
#include "General/Game.h"
#include "General/Level.h"
#include "Config.h"
#include "Entities/Scripts.h"
#include "Entities/Component.h"
#include "Entities/ComponentScript.h"
#include "Entities/GraphicAttribute.h"
#include "Entities/SpriteAttribute.h"
#include "Entities/ColorAttribute.h"
#include "imgui/imconfig.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imstb_rectpack.h"
#include "imgui/imstb_textedit.h"
#include "imgui/imstb_truetype.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"
#define DEBUG
const int WIDTH = 1920;
const int HEIGHT = 1080;
const int MAX_ENTITIES = 10;
bool show_demo_window = true;
    bool show_another_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
int window_loop(GLFWwindow* window)
{
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        glfwSwapInterval(0);
        glfwPollEvents();
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        /* currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        //Llamo la función del usuario
        loop_function(deltaTime); */
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
    }
    glfwTerminate();
    return 0;
}


void key_callback2(GLFWwindow* window, int key, int scancode, int action, int mode)
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
int metodoPrincipal()
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  ImGui::StyleColorsDark();
  printf("Main::Creando ventana...\n");
  /* Game::init(WIDTH,HEIGHT); */
  GLFWwindow* window;
    if (!glfwInit())
    {
        //return NULL;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    //glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);
    window = glfwCreateWindow(1920, 1080, "Game", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        //return NULL;
    }
    
    //glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();
    glGetError();
    //glfwSetKeyCallback(window,key_callback2);
    //glfwSetMouseButtonCallback(window,ImGui_ImplGlfw_MouseButtonCallback);
    //glfwSetErrorCallback(error_callback);
    /*====================TERMINA CREACION DE VENTANA==========================*/
    glViewport(0, 0, WIDTH, HEIGHT);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 130");
  window_loop(window);
  /* Level* level1 = Game::addLevel();
  Entity* cameraEntity = level1->addEntityCamera(WIDTH,HEIGHT);
  ComponentCamera* cmpCamera = (ComponentCamera*)cameraEntity->getComponent(0);
  cmpCamera->zoom(0.35f);
  cmpCamera->move(glm::vec3(-2610.0f,-185.5f,0.0f));
  //Creo el personaje
  ScriptComponent* scrCamera = new CameraController();
  ((CameraController*)(scrCamera))->camera = cameraEntity;

  //cameraEntity->addComponent(new ComponentScript(scrCamera));
  Entity* personaje = level1->addEntity();
  const char* arr[6] = {"res/sprites/e1.png","res/sprites/e2.png","res/sprites/e3.png","res/sprites/e4.png","res/sprites/e5.png","res/sprites/e6.png"};
  Sprite* sprIdle = new Sprite(arr,6,"idle");
  Game::addSprite(sprIdle);
  sprIdle->setSpeed(0.16*60);
  GraphicAttribute* attrColor1 = new SpriteAttribute(sprIdle);
  personaje->addAttribute(attrColor1);
  Game::setLevel(0);
  
  const char* walkingAnimation[9] = {"res/sprites/ew1.png","res/sprites/ew2.png","res/sprites/ew3.png","res/sprites/ew4.png","res/sprites/ew5.png","res/sprites/ew6.png","res/sprites/ew7.png","res/sprites/ew8.png","res/sprites/ew9.png"};
  Sprite* walkingSpr = new Sprite(walkingAnimation,9,"walking");
  Game::addSprite(walkingSpr);
  const char* shootingAnimation[2] = {"res/sprites/es1.png","res/sprites/es2.png"};
  Sprite* shootingSpr = new Sprite(shootingAnimation,2,"shooting");
  Game::addSprite(shootingSpr);
  shootingSpr->setSpeed(0.5*60.0);
  const char* fireAnimation[3] = {"res/sprites/f1.png","res/sprites/f2.png","res/sprites/f3.png"};
  Sprite* fireSpr = new Sprite(fireAnimation,3,"fire");
  Game::addSprite(fireSpr);
  fireSpr->setSpeed(0.3*60.0);
  walkingSpr->setSpeed(0.2*60.0);
  
/*   scr->spriteIdle = sprIdle;
  scr->spriteWalking = walkingSpr;
  scr->spriteShooting = shootingSpr;
  scr->spriteFire = fireSpr; */
  /* Entity* fireEntity = level1->addEntity();
  
  personaje->scale(glm::vec3(1.4f,1.8f,1.0f));
  personaje->setPosition(glm::vec3(-2459.0f,-120.0f,0.0f));
  

  
  fireEntity->setPosition(glm::vec3(-2459.0f,-120.0f,0.0f));
  GraphicAttribute* fireAttr = new SpriteAttribute(fireSpr);
  fireEntity->addAttribute(fireAttr);
  //Creo el piso
  GraphicAttribute* attrColor = new ColorAttribute(glm::vec3(0.5f,0.1f,0.2f));
  for(int i = 0; i < 20; i++)
  {
    Entity* piso = level1->addEntity();
    float division = float(20-1)/2.0f;
    float new_x = float((32.0f)*i-(32.0f)*division);
    piso->addAttribute(attrColor);
    piso->translate(glm::vec3(new_x,-32.0f,0.0f));
  }
  //Creo el fondo
  const char* bg[1] = {"res/sprites/background.png"};
  Entity* entityBg = level1->addEntity();
  GraphicAttribute* attrFondo = new SpriteAttribute(new Sprite(bg,1,"fondo"));
  entityBg->addAttribute(attrFondo);
  entityBg->scale(glm::vec3(173.625f,86.98f,1.0f));
  entityBg->translate(glm::vec3(0.0f,0.0f,-0.1f));

  const char* bgLevel[1] = {"res/sprites/level-bg.png"};
  Entity* entityLevelBg = level1->addEntity();
  GraphicAttribute* attrFondoLevel = new SpriteAttribute(new Sprite(bgLevel,1,"fondo2"));
  entityLevelBg->addAttribute(attrFondoLevel);
  entityLevelBg->scale(glm::vec3(173.625f,26.75f,1.0f));
  entityLevelBg->translate(glm::vec3(0.0f,0.0f,-0.01f));

  //Creo el pajaro
  const char* birdSprite[5] = {"res/sprites/c1.png","res/sprites/c2.png","res/sprites/c3.png","res/sprites/c4.png","res/sprites/c5.png"};
  Entity* bird = level1->addEntity();
  Sprite* sprBird = new Sprite(birdSprite,5,"bird");
  sprBird->setSpeed(0.2*60);
  GraphicAttribute* attrBird = new SpriteAttribute(sprBird);
  bird->addAttribute(attrBird);
  bird->scale(glm::vec3(-1.0f,0.6f,0.0f));
  bird->setPosition(glm::vec3(-2460.0f,-80.0f,0.0f));
  BirdMovement* birdScr = new BirdMovement();
  birdScr->bird = bird;
  ComponentScript* birdScrComponent = new ComponentScript(birdScr);
  bird->addComponent(birdScrComponent); 
  PlayerMovement* scr = new PlayerMovement();
  scr->player = personaje;
  scr->fire = fireEntity;
  Component* scriptComponent = new ComponentScript(scr);
  
  personaje->addComponent(scriptComponent);
  

  Game::loop();
  printf("Main::Eliminando objetos...\n");
  Game::close();  */

  //delete(level1);
  //delete(attrColor);
  printf("Main::Objetos eliminados. Cerrando programa.\n");
  return 0;
}

int main(int argc, char** argv)
{
  int toReturn = metodoPrincipal();
  switch(toReturn)
  {
    case 0:
      printf("Main::Ejecucion exitosa.\n");
      break;
    default:
      printf("Main::ERROR. Codigo: %d.\n",toReturn);
  }
  return 0;
}