#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui/imconfig.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imstb_rectpack.h"
#include "imgui/imstb_textedit.h"
#include "imgui/imstb_truetype.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

namespace Gui
{
    void init(GLFWwindow* window);
    void draw();
}