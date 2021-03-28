#include "Gui.h"
#include "../General/Game.h"
#include "../FileManagement/ImageFileManager.h"
#include <windows.h>
#include <shobjidl.h> 
#include "../Utils/WindowsDialogs.h"
#include "../Entities/ComponentCollisionBox.h"
#include "../Entities/LuaScriptComponent.h"
#include "../Entities/ComponentParticle.h"
#include "../Entities/ComponentMusic.h"
#include "../FileManagement/FileManager.h"
#include "../Entities/PixelizationAttribute.h"
#include "../Entities/Sharpen.h"
#include "../Entities/ComponentCamera.h"
#include "../Entities/DilationAttribute.h"
GLFWwindow* ventana;
glm::vec3 vec;
int height = 0, width = 0;
int counterPopup = 0;
bool drawPopup = false;
bool item_clicked = false;
int item_index_clicked = -1;
Entity* entityClicked;
bool show_demo_window = true;
bool sprites_shown = false;
bool sprite_selected = false;
int sprite_index_selected = -1;
bool spriteSelection = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
std::string str = "";
double dt = 0.0;
static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
ImGuiTreeNodeFlags node_flags = base_flags;
Sprite* system_undefined = NULL;
Level* levelClicked;
bool showLevelInfo = false;
ComponentCamera* cameraClicked;
bool showCameraInfo = false;
//Dimensiones
const int DISPLAY_GAME_WIDTH = 0;
const int DISPLAY_GAME_HEIGHT = 0;
int ENTITY_TREE_WIDTH = width/4;
int ENTITY_TREE_HEIGHT = height;
const int LOG_WIDTH = 0;
const int LOG_HEIGHT = 0;
float GAME_CONTROLS_WIDTH = width*3/4;
const int GAME_CONTROLS_HEIGHT = 25;
const float MENU_BAR_WIDTH = 0;
const int MENU_BAR_HEIGHT = 21;
const int SPRITES_EXPLORER_WIDTH = 280;
const int SPRITES_EXPLORER_HEIGHT = 500;
const int SPRITE_PROPERTIES_WIDTH = 280;
const int SPRITE_PROPERTIES_HEIGHT = 260;
const int ENTITY_PROPERTIES_WIDTH = 500;
const int ENTITY_PROPERTIES_HEIGHT = 200;
const float DEFAULT_FONT_SIZE = 16.0f;
const int SPRITES_EXPLORER_MAX_ROW_SIZE = 4;


void recalculate_width_height()
{
    GAME_CONTROLS_WIDTH = width*2/4;
    ENTITY_TREE_WIDTH = width/4;
    ENTITY_TREE_HEIGHT = height;
}


void show_image_context_menu(ImGuiTreeNodeFlags node_flags, Sprite* sprite, int i)
{
    ImGui::TreeNodeEx("Eliminar Imagen",node_flags);
    if(ImGui::IsItemClicked())
    {
        sprite->removeImage(i);
        ImGui::CloseCurrentPopup();
    }
}


void Gui::init(GLFWwindow* window)
{
    ventana = window;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImFont* font = io.Fonts->AddFontFromFileTTF("res/fonts/RobotoMono-Regular.ttf",DEFAULT_FONT_SIZE);
    unsigned char* pixels;
    int width,height, bytes_per_pixels;
    io.Fonts->GetTexDataAsRGBA32(&pixels,&width,&height,&bytes_per_pixels);
    if(system_undefined == NULL)
            system_undefined = Game::findSystemSpriteByName("undefined");
    
}

void showSpriteInfo()
{
    ImGui::Begin("Sprite Info",&sprite_selected);
    ImVec2 pos = ImGui::GetCursorScreenPos();
    float my_tex_w = 100.0f;
    float my_tex_h = 100.0f;
    ImVec2 uv_min = ImVec2(0.0f, 1.0f);
    ImVec2 uv_max = ImVec2(1.0f, 0.0f);    
    
    ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); 
    std::vector<Sprite*> sprites = Game::getSprites();
    Sprite* spr = sprites.at(sprite_index_selected);
    float transparency = spr->getTransparency();
    ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, transparency);   
    ImTextureID tex = (ImTextureID)(spr->getSpriteImage(spr->getCurrentSprite(dt)));
    if(tex != (ImTextureID)-1)
    {
    //Muestro la preview
        ImGui::Image(tex, ImVec2(my_tex_w, my_tex_h), uv_min, uv_max, tint_col, border_col);
    }
    else
    {
        if(system_undefined == NULL)
            system_undefined = Game::findSystemSpriteByName("undefined");
        ImTextureID texUndefined = (ImTextureID)(system_undefined->getSpriteImage(0));
        ImGui::Image(texUndefined, ImVec2(my_tex_w,my_tex_h), uv_min, uv_max, tint_col, border_col);
    }
    ImGui::SameLine();
    ImGui::BeginChild("ChildL", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.8f, 100), false);
    static char buf1[64] = ""; 
    char b[64] = "";
    char* arr = (char*)malloc(sizeof(char)*64);
    arr = strdup(spr->getName().c_str());
    ImGui::InputText("Nombre ", arr, 64);
    float  speed = spr->getSpeed();
    spr->setName(arr);
    ImGui::DragFloat("Velocidad", &speed, 0.005f, 0.0f, FLT_MAX, "%.3f");
    spr->setSpeed(speed);
    
    ImGui::DragFloat("Transparencia", &transparency, 0.005f, 0.0f, 1.0f, "%.3f");
    spr->setTransparency(transparency);
    ImGui::EndChild();
    /*Pongo las imagenes que componen el sprite*/
    ImGuiWindowFlags child_flags = ImGuiWindowFlags_HorizontalScrollbar;
    ImGui::BeginChild("Images", ImVec2(ImGui::GetWindowContentRegionWidth(), 130), true, child_flags);
    for(int i = 0; i < spr->getSize(); i++)
    {
        ImTextureID img = (ImTextureID)(spr->getSpriteImage(i));
        ImGui::Image(img, ImVec2(100.0f,100.0f), uv_min, uv_max, tint_col, border_col);
        std::string str = "image "+i;
        if (ImGui::BeginPopupContextItem(str.c_str()))
        {
            show_image_context_menu(node_flags,spr,i);
            ImGui::EndPopup();
        }
        if((i + 1) < spr->getSize())
        {
            ImGui::SameLine();
        }
    }
    ImGui::EndChild();
    if(ImGui::Button("Agregar imagen",ImVec2(100.0f,32.0f)))
    {
        TCHAR imgDir[260] = {0};
        Utils::saveFileDialog(imgDir,260);
        if(imgDir != NULL && strcmp((const char*)imgDir,""))
        {
            spr->addImage((const char*)imgDir);
        }
    }

    
    ImGui::End();
}

void showGameControls()
{
    
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    window_flags |= ImGuiWindowFlags_NoScrollWithMouse;
    window_flags |= ImGuiWindowFlags_NoScrollbar;
    recalculate_width_height();
    ImGui::SetNextWindowSize(ImVec2(GAME_CONTROLS_WIDTH, GAME_CONTROLS_HEIGHT), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(ENTITY_TREE_WIDTH, MENU_BAR_HEIGHT),ImGuiCond_Always);
    ImGui::Begin("GameControls",NULL,window_flags);
    ImGui::Button("Play",ImVec2(50,18));
    if(ImGui::IsItemClicked())
    {
        //Tengo que poner el juego en estado PLAY
        Game::playGame();
    }
    ImGui::SameLine();
    ImGui::Button("Pause",ImVec2(50,18));
    if(ImGui::IsItemClicked())
    {
        //Tengo que poner el juego en estado PAUSE
        Game::pauseGame();
    }
    ImGui::SameLine();
    ImGui::Button("Stop",ImVec2(50,18));
    if(ImGui::IsItemClicked())
    {
        //Tengo que poner el juego en estado STOPPED
        Game::stopGame();
    }
    ImGui::End();
}


void showSprites()
{
    ImGui::SetNextWindowSize(ImVec2(SPRITES_EXPLORER_WIDTH, SPRITES_EXPLORER_HEIGHT), ImGuiCond_Once);
    ImGui::Begin("Sprites",&sprites_shown);
    std::vector<Sprite*> sprites = Game::getSprites();
    std::vector<Sprite*>::iterator ptr;
    int i = 0; 
    for(ptr = sprites.begin(); ptr<sprites.end(); ptr++)
    {
        ImGui::PushID(i);
        ImGuiIO& io = ImGui::GetIO();
        Sprite* spr = *ptr;
        //int current_sprite = spr->getCurrentSpriteIndex();
        //Image* image_properties = spr->getProperties(0);
        //float my_tex_w = (float)image_properties->width;
        //float my_tex_h = (float)image_properties->height;
        int frame_padding = -1 ;                             // -1 == uses default padding (style.FramePadding)
        ImVec2 size = ImVec2(50.0f, 50.0f);                     // Size of the image we want to make visible
        ImVec2 uv0 = ImVec2(0.0f,1.0f);                        // UV coordinates for lower-left
        ImVec2 uv1 = ImVec2(1.0f, 0.0f);
        ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);         // Black background
        ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);       // No tint
        
        ImTextureID tex = (ImTextureID)(spr->getSpriteImage(0));
        if(tex != (ImTextureID)-1)
        {
        //Muestro la preview
            ImGui::ImageButton(tex, size, uv0, uv1, frame_padding, bg_col, tint_col);
        }
        else
        {
            if(system_undefined == NULL)
                system_undefined = Game::findSystemSpriteByName("undefined");
            ImTextureID texUndefined = (ImTextureID)(system_undefined->getSpriteImage(0));
            ImGui::ImageButton(texUndefined, size, uv0, uv1, frame_padding, bg_col, tint_col);
        }
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::Text("%s",spr->getName().c_str());
            ImGui::EndTooltip();
        }
        if(ImGui::IsItemClicked())
        {
            sprite_index_selected = i;
            sprite_selected = true;
        }
        ImGui::PopID();
        if((i + 1) % SPRITES_EXPLORER_MAX_ROW_SIZE != 0 )
        {
            ImGui::SameLine();
        }
        i++;
    }

    ImGui::End();  
}


void showLog(ImGuiWindowFlags window_flags)
{
    bool b = true;
    static ExampleAppLog log;
    ImGui::SetNextWindowPos(ImVec2(width/4,height*3/4), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(width*2/4, height/4), ImGuiCond_Always);
    ImGui::Begin("Example: Log", NULL, window_flags);
    log.AddLog(str.c_str());
    str.clear();
    ImGui::End();
    log.Draw("Example: Log", NULL);
}

void newProjectPopup()
{
    ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal("New?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Todo el progreso no guardado se perderá.\n ¿Quieres crear un proyecto nuevo?\n\n");
        ImGui::Separator();
        if (ImGui::Button("OK", ImVec2(120, 0))) 
        { 
            ImGui::CloseCurrentPopup(); 
            Game::newGame();
            gamedata->saveFile = "";
        }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button("Cancelar", ImVec2(120, 0))) 
        { 
            ImGui::CloseCurrentPopup(); 
        }
        ImGui::EndPopup();
    }
}

static void ShowExampleMenuFile()
{
    ImGui::MenuItem("New");
    if(ImGui::IsItemClicked()){
        ImGui::OpenPopup("New?");  
        
    }
    
    newProjectPopup();
    if (ImGui::MenuItem("Open")) 
    {
        TCHAR toReturn [260] = {0};
        Utils::openFileDialog(toReturn,260);
        if(toReturn != NULL)
        {
            char buffer [261];
            sprintf (buffer, "%s",toReturn);
            Game::loadProject(buffer);
            gamedata->saveFile = buffer;
        }
    }
    if (ImGui::MenuItem("Save")) 
    {
        if(strcmp(gamedata->saveFile.c_str(),"")==0)
        {
            TCHAR toReturn [260] = {0};
            Utils::saveFileDialog(toReturn,260);
            if(toReturn != NULL)
            {
                char buffer [261];
                sprintf (buffer, "%s",toReturn);
                file_manager::save_project(buffer);
                gamedata->saveFile = buffer;
            }
        }
        else   
            file_manager::save_project(gamedata->saveFile.c_str());       
    }
    if (ImGui::MenuItem("Save As..")) {
        TCHAR toReturn [260] = {0};
        Utils::saveFileDialog(toReturn,260);
        if(toReturn != NULL)
        {
            char buffer [261];
            sprintf (buffer, "%s",toReturn);
            file_manager::save_project(buffer);
            gamedata->saveFile = buffer;
        }
    }
    ImGui::Separator();
}

static void ShowExampleAppMainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Archivo"))
        {
            ShowExampleMenuFile();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Insertar"))
        {
            if (ImGui::MenuItem("Nuevo nivel")) 
            {
                Game::addLevel();
            }
            if (ImGui::MenuItem("Nuevo sprite")) 
            {
                //Tengo que agregar un sprite vacio y despues mostrar la ventana de edit
                Sprite* spr = new Sprite();
                Game::addSprite(spr);
                sprite_selected = true;
                std::vector<Sprite*> sprites = Game::getSprites();
                sprite_index_selected = sprites.size()-1;
                //free(spr);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Ver"))
        {
            if (ImGui::MenuItem("Sprites")) {sprites_shown = true;}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Configuración"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Ayuda"))
        {
            if (ImGui::MenuItem("Acerca de")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void showEntityPopup()
{
    //Tengo que abrir una ventana con datos de la entidad
    //ImGui::SetNextWindowPos(ImVec2(width/4+50,height/2),ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(500,200),ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(width/2-250,height/2-100),ImGuiCond_Once);
    std::string windowName = "Entidad"+std::to_string(item_index_clicked);
    ImGui::Begin(windowName.c_str(),&item_clicked);
    vec = entityClicked->getPosition();
    char* arr = (char*)malloc(sizeof(char)*64);
    arr = strdup(entityClicked->getName().c_str());
    ImGui::InputText("Nombre ", arr, 64);
    entityClicked->setName(arr);
    float vecRotacion[3] = {entityClicked->getRotation().x,entityClicked->getRotation().y,entityClicked->getRotation().z};
    float vecScaling[3] = {entityClicked->getScale().x,entityClicked->getScale().y,entityClicked->getScale().z};
    //Gui::writeToLog(std::to_string(vec.x));
    float vec4f[3] = {entityClicked->getPosition().x,entityClicked->getPosition().y,entityClicked->getPosition().z};
    //Gui::writeToLog(std::to_string(vec4f[0])+"--"+std::to_string(vec.x)+ "\n");
    if(ImGui::DragFloat3("Posición",vec4f))
    {
        entityClicked->setPosition(glm::vec3(vec4f[0],vec4f[1],vec4f[2]));
    }
    if(ImGui::DragFloat3("Rotación",vecRotacion))
    {
        entityClicked->setRotation(glm::vec3(vecRotacion[0],vecRotacion[1],vecRotacion[2]));
    }
    if(ImGui::DragFloat3("Escala",vecScaling))
    {
        entityClicked->setScale(glm::vec3(vecScaling[0],vecScaling[1],vecScaling[2]));
    }
    //Ahora tengo que mostrar la sección de Sprites
    for(GraphicAttribute* attr : entityClicked->getAllAttributes())
    {
        bool openAttribute = ImGui::CollapsingHeader(attr->getName().c_str(), ImGuiTreeNodeFlags_None);
        if(openAttribute)
        {
            if(strcmp(attr->getName().c_str(),"sprite") == 0)
            {
                SpriteAttribute* sprAttr = ((SpriteAttribute*)attr);
                ImGui::Button("Seleccionar Sprite");
                if(ImGui::IsItemClicked())
                {
                    //Abrir una ventana para seleccionar un sprite
                    spriteSelection = true;
                    Gui::writeToLog("Voy a abrir la seleccion de sprite.\n");
                    ImGui::OpenPopup("selecSprite");

                }
                if (ImGui::BeginPopup("selecSprite"))
                {
                    std::vector<Sprite*> sprites = Game::getSprites();
                    std::vector<Sprite*>::iterator ptr;
                    int i = 0; 
                    for(ptr = sprites.begin(); ptr<sprites.end(); ptr++)
                    {
                        ImGui::TreeNodeEx((*ptr)->getName().c_str(),node_flags); 
                        if(ImGui::IsItemClicked())
                        {
                            if(sprAttr == NULL)
                            {
                                //Tengo que agregarle un atributo de sprite
                                entityClicked->addAttribute(new SpriteAttribute((*ptr)));
                            }
                            else
                            {
                                sprAttr->setSprite((*ptr));
                            }
                            ImGui::CloseCurrentPopup();
                        }
                        i++;
                    }
                    ImGui::EndPopup();
                }
                std::string selected_sprite = "undefined";
                if(strcmp(sprAttr->getName().c_str(),""))
                    selected_sprite = sprAttr->getName();
                ImGui::SameLine();
                ImGui::Text(selected_sprite.c_str());
                ImGui::SameLine();
                if(sprAttr!=NULL)
                {
                    int index = sprAttr->getSprite()->getCurrentSpriteIndex();
                    ImGui::Image((ImTextureID)(sprAttr->getSprite()->getSpriteImage(index)),ImVec2(50, 50), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
                }
                else
                {
                    /* ImTextureID texUndefined = (ImTextureID)(system_undefined->getSpriteImage(0));
                    ImGui::Image(texUndefined, ImVec2(50, 50), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f)); */
                }
            }



            if(strcmp(attr->getName().c_str(),"color") == 0)
            {
                ColorAttribute* colAttr = ((ColorAttribute*)attr);
                ImVec4 color = ImVec4(colAttr->getColor().x,colAttr->getColor().y,colAttr->getColor().z,colAttr->getColor().a);
                ImGui::ColorEdit4("MyColor##3", (float*)&color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel );
                if(colAttr!=NULL)
                {   
                    colAttr->setColor(glm::vec4(color.x,color.y,color.z,color.w));
                }

            }
        }
    }


    for(Component* component : entityClicked->getAllComponents())
    {
        bool openComponent = ImGui::CollapsingHeader(component->getVisibleName().c_str(), ImGuiTreeNodeFlags_None);
        if(openComponent)
        {
            //ImGui::BeginChild(component->getName().c_str());
            if(strcmp(component->getName().c_str(),"collider") == 0)
            {
                ComponentCollisionBox* collComp = ((ComponentCollisionBox*)component);
                float collider_numbers[4] = {collComp->getX(),collComp->getY(),collComp->getWidth(),collComp->getHeight()};
                if(ImGui::DragFloat4("x,y,width,height",collider_numbers))
                {
                    ((ComponentCollisionBox*)component)->setX(collider_numbers[0]);
                    ((ComponentCollisionBox*)component)->setY(collider_numbers[1]);
                    ((ComponentCollisionBox*)component)->setWidth(collider_numbers[2]);
                    ((ComponentCollisionBox*)component)->setHeight(collider_numbers[3]);
                }
            }
            if(strcmp(component->getName().c_str(),"lua_script") == 0)
            {
                LuaScriptComponent* scriptComponent = ((LuaScriptComponent*)component);
                std::string text = scriptComponent->getScript();
                if(!strcmp(text.c_str(),""))
                    text = "undefined";
                ImGui::Text(text.c_str());
                ImGui::Button("Seleccionar");
                if(ImGui::IsItemClicked())
                {
                    TCHAR scriptReturn [260] = {0};
                    Utils::openFileDialog(scriptReturn,260);
                    char buffer [261];
                    sprintf (buffer, "%s",scriptReturn);
                    scriptComponent->setScript(buffer);
                }
            }
            if(strcmp(component->getName().c_str(),"particle") == 0)
            {
                ComponentParticle* particleComponent = ((ComponentParticle*)component);
                ImGui::Text("Particulas máximas: ");
                ImGui::SameLine();
                int max_particles = particleComponent->getMaxParticles();
                if(ImGui::DragInt("max",&max_particles,1,1,9999,"%d"))
                particleComponent->setMaxParticles(max_particles);
                ImGui::Text("Particulas por paso: ");
                ImGui::SameLine();
                int step_particles = particleComponent->getNewParticles();
                if(ImGui::DragInt("step", &step_particles, 1, 1, max_particles, "%d"))
                particleComponent->setNewParticles(step_particles);
                ImGui::Text("Color");
                ImGui::SameLine();
                ImVec4 color = ImVec4(particleComponent->getColor().x,particleComponent->getColor().y,particleComponent->getColor().z,particleComponent->getColor().a);
                ImGui::ColorEdit4("MyColor##4", (float*)&color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel );
                particleComponent->setColor(glm::vec4(color.x,color.y,color.z,color.w));
                ImGui::Text("Dirección");
                ImGui::SameLine();
                float dir[3] = {particleComponent->getDirection().x,particleComponent->getDirection().y,particleComponent->getDirection().z};
                ImGui::DragFloat3("dir",dir,0.05f,-1.0f,1.0f,"%.3f");
                particleComponent->setDirection(glm::vec3(dir[0],dir[1],dir[2]));
                ImGui::Text("Tiempo de vida");
                ImGui::SameLine();
                float life = particleComponent->getLifetime();
                ImGui::DragFloat("Lifetime",&life,0.05f,0.0f,999.0f,"%.3f");
                particleComponent->setLifetime(life);



            }
            if(strcmp(component->getName().c_str(),"music") == 0)
            {
                ComponentMusic* componentMusic = (ComponentMusic*)component;
                ImGui::Text("Pista: ");
                ImGui::SameLine();
                ImGui::Text(componentMusic->getMusic().c_str());
                ImGui::Button("Seleccionar pista");
                if(ImGui::IsItemClicked())
                {
                    TCHAR scriptReturn [260] = {0};
                    Utils::openFileDialog(scriptReturn,260);
                    char buffer [261];
                    sprintf (buffer, "%s",scriptReturn);
                    componentMusic->setMusic(buffer);
                }
                ImGui::Text("Volumen: ");
                ImGui::SameLine();
                float volumen = 1.0f;
                if(ImGui::SliderFloat("SliderFloat (0 -> 1)", &volumen, 0.0f, 1.0f, "%.3f"))
                {
                    componentMusic->setVolume(volumen);
                }
                bool playAtStart = componentMusic->getPlaying();
                ImGui::Checkbox("Reproducir al comienzo", &playAtStart);
                componentMusic->setPlaying(playAtStart);
                bool loop = componentMusic->getLoop();
                ImGui::Checkbox("Loop", &loop);
                componentMusic->setLoop(loop);
            }
            ImGui::Button("Eliminar componente");
            if(ImGui::IsItemClicked())
            {
                entityClicked->removeComponent(component->getVisibleName());
            }

        }
    }
    ImGui::Button("Insertar...");
    if(ImGui::IsItemClicked())
    {
        //Abrir una ventana para seleccionar un sprite
        spriteSelection = true;
        Gui::writeToLog("Voy a abrir la seleccion de sprite.\n");
        ImGui::OpenPopup("addCompAttr");
    }
    if (ImGui::BeginPopup("addCompAttr"))
    {
        const int max_components = 6;
        std::string compsAttrs[max_components] = {"collider","lua_script","particle","music","color","sprite"};
        for(int i = 0; i < max_components; i++)
        {
            ImGui::TreeNodeEx(compsAttrs[i].c_str(),node_flags); 
            if(ImGui::IsItemClicked())
            {
                if(i == 0)
                {
                    //Collider
                    entityClicked->addComponent(new ComponentCollisionBox(entityClicked));
                }
                if(i == 1)
                {
                    //lua_script
                    entityClicked->addComponent(new LuaScriptComponent("",Game::getLuaState()));
                }
                if(i == 2)
                {
                    //particle
                    entityClicked->addComponent(new ComponentParticle(500,2,entityClicked));
                }
                if(i == 3)
                {
                    //music
                    entityClicked->addComponent(new ComponentMusic(irrklang::createIrrKlangDevice()));
                }
                if(i == 4)
                {
                    entityClicked->addAttribute(new ColorAttribute(glm::vec4(0.0f,0.0f,0.0f,1.0f)));
                }
                if(i == 5)
                {
                    entityClicked->addAttribute(new SpriteAttribute(Game::findSystemSpriteByName("undefined")));
                }
                ImGui::CloseCurrentPopup();
            }
        }
            
    
        ImGui::EndPopup();
    }


    ImGui::End();
}

void showSpriteSelectionMenu(ImGuiTreeNodeFlags node_flags, Entity* entity)
{
    
}


void showEntityContextMenu(ImGuiTreeNodeFlags node_flags, Level* level, int j)
{
    ImGui::TreeNodeEx("Eliminar",node_flags);
    if(ImGui::IsItemClicked())
    {
        level->removeEntity(j);
        ImGui::CloseCurrentPopup();
        item_clicked = false;
        item_index_clicked = -1;
    }
}

void showLevelContextMenu(ImGuiTreeNodeFlags node_flags, Level* level, int i)
{
    ImGui::TreeNodeEx("Mostrar",node_flags);
    if(ImGui::IsItemClicked())
    {
        Game::setLevel(i);
        ImGui::CloseCurrentPopup();
    }
    ImGui::TreeNodeEx("Agregar entidad",node_flags);
    if(ImGui::IsItemClicked())
    {
        level->addEntity();
        ImGui::CloseCurrentPopup();
    }
    ImGui::TreeNodeEx("Agregar cámara",node_flags);
    if(ImGui::IsItemClicked())
    {
        if(level->getCamera() == NULL)
            Entity* cameraEntity = level->addEntityCamera(width,height);
        else
        {
            Gui::writeToLog("Ya hay una cámara creada\n");
        }
        
        ImGui::CloseCurrentPopup();
    }
}






void showTreeView(ImGuiWindowFlags window_flags)
{
 
    counterPopup = 0;
    static float f = 0.0f;
    static int counter = 0;
    ImGui::SetNextWindowPos(ImVec2(0,18), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(width/4,height),ImGuiCond_Always);
    ImGui::Begin("Hello, world!",NULL,window_flags);                          // Create a window called "Hello, world!" and append into it.
    std::vector<Level*> levels = Game::getLevels();
    std::vector<Level*>::iterator ptr;
    int i = 0;
    int node_clicked = -1;
    for(ptr = levels.begin(); ptr<levels.end(); ptr++)
    {
        std::string str = "Nivel "+ std::to_string(i);
        node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen; // ImGuiTreeNodeFlags_Bullet
        ImGui::SetNextItemOpen(true, ImGuiCond_Once);
        if (ImGui::TreeNode(str.c_str()))
        {
            if(ImGui::IsItemClicked())
            {
                levelClicked = (*ptr);
                showLevelInfo = true;

            }
                
            if (ImGui::BeginPopupContextItem(str.c_str()))
            {
                showLevelContextMenu(node_flags,(*ptr),i);
                ImGui::EndPopup();
            }
            
            std::vector<Entity*> entities = (*ptr)->getEntities();
            std::vector<Entity*>::iterator ptr2;
            int j = 0;
            for(ptr2 = entities.begin(); ptr2<entities.end(); ptr2++)
            {
                
                std::string st = "Entidad "+std::to_string(j);
                bool node_open = ImGui::TreeNodeEx(st.c_str(),node_flags);
                if (ImGui::IsItemClicked())
                {
                    //Gui::writeToLog("Hice click en " + std::to_string(j)+"\n");
                    item_clicked = true;
                    item_index_clicked = j;
                    entityClicked = entities.at(j);
                    drawPopup = false;
                }
                if (ImGui::BeginPopupContextItem(st.c_str()))
                {
                    showEntityContextMenu(node_flags,(*ptr),j);
                    ImGui::EndPopup();
                }
                
                    
                j++;
            }
            if((*ptr)->getCamera()!=NULL)
            {
                ImGui::TreeNodeEx("Cámara",node_flags);
                if (ImGui::IsItemClicked())
                {
                    cameraClicked = (ComponentCamera*)(*ptr)->getCamera()->getComponent("camera");
                    showCameraInfo = true;
                }

                
            }
            ImGui::TreePop();
        }
       i++; 
    }
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();  


}


void showCameraPopup()
{
    //Tengo que abrir una ventana con datos de la entidad
    //ImGui::SetNextWindowPos(ImVec2(width/4+50,height/2),ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(500,200),ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(width/2-250,height/2-100),ImGuiCond_Once);
    std::string windowName = "Camara";//+std::to_string(item_index_clicked);
    ImGui::Begin(windowName.c_str(),&showCameraInfo);
    glm::vec3 p = cameraClicked->getPosition();
    float pos[3] = {p.x,p.y,p.z};
    ImGui::DragFloat3("pos",pos,1.0f,-FLT_MAX,FLT_MAX,"%.3f");
    cameraClicked->setPosition(glm::vec3(pos[0],pos[1],pos[2]));
    float zoom = cameraClicked->getZoom();
    ImGui::DragFloat("zoom",&zoom,0.005f,0.1f,10.0f,"%.3f");
    cameraClicked->zoom(zoom);
     
    ImGui::End();
}

void showLevelPopup()
{
     //Tengo que abrir una ventana con datos de la entidad
    //ImGui::SetNextWindowPos(ImVec2(width/4+50,height/2),ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(500,200),ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(width/2-250,height/2-100),ImGuiCond_Once);
    std::string windowName = "Nivel";//+std::to_string(item_index_clicked);
    ImGui::Begin(windowName.c_str(),&showLevelInfo);
    bool gc = levelClicked->getGammaCorrection();
    ImGui::Checkbox("gammaCorrection",&gc);
    levelClicked->setGammaCorrection(gc);
    ImGui::Separator();
    for(GraphicAttribute* attr : levelClicked->getAttributes())
    {
        bool openAttribute = ImGui::CollapsingHeader(attr->getName().c_str(), ImGuiTreeNodeFlags_None);
        if(openAttribute)
        {
            if(strcmp(attr->getName().c_str(),"pixelization") == 0)
            {
                PixelizationAttribute* sprAttr = ((PixelizationAttribute*)attr);
                int pixelSize = sprAttr->getPixelSize();
                ImGui::DragInt("Pixel Size", &pixelSize, 1, 0, 100, "%.3f");
                sprAttr->setPixelSize(pixelSize);
            }



            if(strcmp(attr->getName().c_str(),"sharpen") == 0)
            {
                Sharpen* colAttr = ((Sharpen*)attr);
                float amount = colAttr->getAmount();
                ImGui::DragFloat("Amount", &amount, 0.05f, 0.0f, FLT_MAX, "%.3f");
                colAttr->setAmount(amount);
            }

            if(strcmp(attr->getName().c_str(),"dilation") == 0)
            {
                DilationAttribute* colAttr = ((DilationAttribute*)attr);
                int size = colAttr->getSize();
                ImGui::DragInt("size",&size, 1,0,999);
                colAttr->setSize(size);
                float separation = colAttr->getSeparation();
                ImGui::DragFloat("Separacion", &separation, 0.05f, 0.0f, FLT_MAX, "%.3f");
                colAttr->setSeparation(separation);
                float minThreshold = colAttr->getMinThreshold();
                ImGui::DragFloat("limite minimo", &minThreshold, 0.05f, 0.0f, FLT_MAX, "%.3f");
                colAttr->setMinThreshold(minThreshold);
                float maxThreshold = colAttr->getMaxThreshold();
                ImGui::DragFloat("limite maximo", &maxThreshold, 0.05f, 0.0f, FLT_MAX, "%.3f");
                colAttr->setMaxThreshold(maxThreshold);
            }
            
            ImGui::Button("Remover atributo");
            if(ImGui::IsItemClicked())
            {
                levelClicked->removeAttribute(attr->getName());
            }
        }
        
    }


    ImGui::Separator();
    ImGui::Button("Insertar atributo...");
    if(ImGui::IsItemClicked())
    {
        ImGui::OpenPopup("addLevelAttr");
    }
    if (ImGui::BeginPopup("addLevelAttr"))
    {
        const int max_components = 3;
        std::string compsAttrs[max_components] = {"pixelization","sharpen","dilation"};
        for(int i = 0; i < max_components; i++)
        {
            ImGui::TreeNodeEx(compsAttrs[i].c_str(),node_flags); 
            if(ImGui::IsItemClicked())
            {
                if(i == 0)
                {
                    //Collider
                    levelClicked->addAttribute(new PixelizationAttribute());
                }
                if(i == 1)
                {
                    //lua_script
                    levelClicked->addAttribute(new Sharpen());
                }
                if(i == 2)
                {
                    levelClicked->addAttribute(new DilationAttribute());
                }
                ImGui::CloseCurrentPopup();
            }
        }
            
    
        ImGui::EndPopup();
    }
    ImGui::End();
}

void Gui::draw(double deltaTime)
{
    dt = deltaTime;
    glfwGetFramebufferSize(ventana, &width, &height);
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(18, 18, 27, 255));
    ShowExampleAppMainMenuBar();
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
   
    showTreeView(window_flags);
    showLog(window_flags);
    if(sprites_shown)
    {
        showSprites();
    }
    if(item_clicked)
    {
        showEntityPopup();
    }
    if(sprite_selected)
    {
        showSpriteInfo();
    }
    int nwidth, nheight;
    glfwGetFramebufferSize(gamedata->window, &nwidth, &nheight);
    ImGui::SetNextWindowPos(ImVec2(width/4,MENU_BAR_HEIGHT+GAME_CONTROLS_HEIGHT),ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(width*2/4,height*2/4),ImGuiCond_Always);
    ImVec2 wsize = ImVec2(width*2/4,height*2/4-18);
    ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
    ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
    ImGui::Begin("JUEGO",NULL,window_flags);
    //ImGui::SetCursorPos((ImVec2((ImGui::GetWindowSize().x*0.5f - wsize.x*0.5f),(ImGui::GetWindowSize().y*0.5f - wsize.y*0.5f))));
    ImGui::Image((ImTextureID)gamedata->texture,wsize, ImVec2(0, 1), ImVec2(1, 0),tint_col,border_col);
    ImGui::End();
    showGameControls();
    if(showLevelInfo)
        showLevelPopup();
    if(showCameraInfo)
        showCameraPopup();
    ImGui::PopStyleColor();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    

}


void Gui::writeToLog(std::string strMessage)
{
    str += strMessage;
}