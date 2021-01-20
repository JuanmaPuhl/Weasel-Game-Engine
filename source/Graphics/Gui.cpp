#include "Gui.h"
#include "../General/Game.h"
#include "../FileManagement/ImageFileManager.h"
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
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
std::string str = "";
double dt = 0.0;

void Gui::init(GLFWwindow* window)
{
    ventana = window;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImFont* font = io.Fonts->AddFontFromFileTTF("res/fonts/RobotoMono-Regular.ttf",16.0f);
    unsigned char* pixels;
    int width,height, bytes_per_pixels;
    io.Fonts->GetTexDataAsRGBA32(&pixels,&width,&height,&bytes_per_pixels);


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
    //Muestro la preview
    ImGui::Image(tex, ImVec2(my_tex_w, my_tex_h), uv_min, uv_max, tint_col, border_col);
    ImGui::SameLine();
    ImGui::BeginChild("ChildL", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.8f, 100), false);
    static char buf1[64] = ""; 
    char b[64] = "";
    char* arr = (char*)malloc(sizeof(char)*64);
    arr = strdup(spr->getName().c_str());
    ImGui::InputText("Nombre ", arr, 64);
    float  speed = spr->getSpeed();
    ImGui::DragFloat("Velocidad", &speed, 0.005f, 0.0f, FLT_MAX, "%.3f");
    spr->setSpeed(speed);
    
    ImGui::DragFloat("Transparencia", &transparency, 0.005f, 0.0f, 1.0f, "%.3f");
    spr->setTransparency(transparency);
    ImGui::EndChild();
    ImGuiWindowFlags child_flags = ImGuiWindowFlags_HorizontalScrollbar;
    ImGui::BeginChild("Images", ImVec2(ImGui::GetWindowContentRegionWidth(), 130), true, child_flags);
    for(int i = 0; i < spr->getSize(); i++)
    {
        ImTextureID img = (ImTextureID)(spr->getSpriteImage(i));
        ImGui::Image(img, ImVec2(100.0f,100.0f), uv_min, uv_max, tint_col, border_col);
        if((i + 1) < spr->getSize())
        {
            ImGui::SameLine();
        }
    }
    ImGui::EndChild();
    

    
    ImGui::End();
}


void showSprites()
{
    const int max_sprites_per_row = 4;
    ImGui::SetNextWindowSize(ImVec2(180, 500), ImGuiCond_Once);
    ImGui::Begin("Sprites",&sprites_shown);
    std::vector<Sprite*> sprites = Game::getSprites();
    std::vector<Sprite*>::iterator ptr;
    int i = 0; 
    for(ptr = sprites.begin(); ptr<sprites.end(); ptr++)
    {
        ImGui::PushID(i);
        ImGuiIO& io = ImGui::GetIO();
        float my_tex_w = 40.0f;
        float my_tex_h = 51.0f;
        int frame_padding = -1 ;                             // -1 == uses default padding (style.FramePadding)
        ImVec2 size = ImVec2(40.0f, 51.0f);                     // Size of the image we want to make visible
        ImVec2 uv0 = ImVec2(0.0f,1.0f);                        // UV coordinates for lower-left
        ImVec2 uv1 = ImVec2(1.0f, 0.0f);
        ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);         // Black background
        ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);       // No tint
        Sprite* spr = *ptr;
        //unsigned int tex = spr->getSpriteImage(spr->getCurrentSprite(0.0));
        ImTextureID tex = (ImTextureID)(spr->getSpriteImage(0.0));
        ImGui::ImageButton(tex, size, uv0, uv1, frame_padding, bg_col, tint_col);
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
        if((i + 1) % max_sprites_per_row != 0 )
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

static void ShowExampleMenuFile()
{
    ImGui::MenuItem("(demo menu)", NULL, false, false);
    if (ImGui::MenuItem("New")) {}
    if (ImGui::MenuItem("Open", "Ctrl+O")) {}
    if (ImGui::BeginMenu("Open Recent"))
    {
        ImGui::MenuItem("fish_hat.c");
        ImGui::MenuItem("fish_hat.inl");
        ImGui::MenuItem("fish_hat.h");
        if (ImGui::BeginMenu("More.."))
        {
            ImGui::MenuItem("Hello");
            ImGui::MenuItem("Sailor");
            if (ImGui::BeginMenu("Recurse.."))
            {
                ShowExampleMenuFile();
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Save", "Ctrl+S")) {}
    if (ImGui::MenuItem("Save As..")) {}

    ImGui::Separator();
    if (ImGui::BeginMenu("Options"))
    {
        static bool enabled = true;
        ImGui::MenuItem("Enabled", "", &enabled);
        ImGui::BeginChild("child", ImVec2(0, 60), true);
        for (int i = 0; i < 10; i++)
            ImGui::Text("Scrolling Text %d", i);
        ImGui::EndChild();
        static float f = 0.5f;
        static int n = 0;
        ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
        ImGui::InputFloat("Input", &f, 0.1f);
        ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Colors"))
    {
        float sz = ImGui::GetTextLineHeight();
        for (int i = 0; i < ImGuiCol_COUNT; i++)
        {
            const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
            ImVec2 p = ImGui::GetCursorScreenPos();
            ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
            ImGui::Dummy(ImVec2(sz, sz));
            ImGui::SameLine();
            ImGui::MenuItem(name);
        }
        ImGui::EndMenu();
    }

    // Here we demonstrate appending again to the "Options" menu (which we already created above)
    // Of course in this demo it is a little bit silly that this function calls BeginMenu("Options") twice.
    // In a real code-base using it would make senses to use this feature from very different code locations.
    if (ImGui::BeginMenu("Options")) // <-- Append!
    {
        static bool b = true;
        ImGui::Checkbox("SomeOption", &b);
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Disabled", false)) // Disabled
    {
        IM_ASSERT(0);
    }
    if (ImGui::MenuItem("Checked", NULL, true)) {}
    if (ImGui::MenuItem("Quit", "Alt+F4")) {}
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
        if (ImGui::BeginMenu("Editar"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Insertar"))
        {
            if (ImGui::MenuItem("Nuevo nivel")) 
            {
                Game::addLevel();
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
        std::string windowName = "Entidad"+std::to_string(item_index_clicked);
        ImGui::Begin(windowName.c_str(),&item_clicked);
        vec = entityClicked->getPosition();
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
        //ImGui::SetWindowFocus();
        ImGui::End();
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
}
static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
ImGuiTreeNodeFlags node_flags = base_flags;

void showTreeView(ImGuiWindowFlags window_flags)
{
 
    counterPopup = 0;
    static float f = 0.0f;
    static int counter = 0;
    ImGui::SetNextWindowPos(ImVec2(0,18), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(width/4,height),ImGuiCond_Always);
    ImGui::Begin("Hello, world!",NULL,window_flags);                          // Create a window called "Hello, world!" and append into it.
    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
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
                /* if (ImGui::IsItemClicked())
                {
                    //Gui::writeToLog("Hice click en " + std::to_string(j)+"\n");
                    item_clicked = true;
                    item_index_clicked = j;
                    entityClicked = (*ptr)->getCamera();
                    drawPopup = false;
                }
                if (ImGui::BeginPopupContextItem("Cámara"))
                {
                    showEntityContextMenu(node_flags,(*ptr),j);
                    ImGui::EndPopup();
                } */

            }
            ImGui::TreePop();
        }
       i++; 
    }
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
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
    ImGui::PopStyleColor();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void Gui::writeToLog(std::string strMessage)
{
    str += strMessage;
}