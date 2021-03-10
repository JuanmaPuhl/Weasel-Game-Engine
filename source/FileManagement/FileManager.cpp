#include "FileManager.h"
#include "../General/Game.h"

std::string file_manager::read_file(std::string dir)
{
    std::string s="";
    std::ifstream file(dir);
    std::string temp;
    while(std::getline(file, temp)) {
      s += "\n"+temp;
    }
    return s;
}

std::vector<std::string> file_manager::parse_file(std::string& source)
{
    std::ifstream file{source};
    std::string lineContent;
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    ShaderType type = ShaderType::NONE;
    std::stringstream ss[2];
    while(getline(file,lineContent))
    {
        if(lineContent.find("<Shader>") != std::string::npos)
        {
        if(lineContent.find("Vertex") != std::string::npos)
        {
            type = ShaderType::VERTEX;
        }
        else if(lineContent.find("Fragment") != std::string::npos)
        {
            type = ShaderType::FRAGMENT;
        }
        }
        else
        {
        if((int)type != -1)
            ss[(int)type] << lineContent << '\n';
        }

    }
    std::vector<std::string> vectorSource;
    vectorSource.push_back(ss[0].str());
    vectorSource.push_back(ss[1].str());
    return vectorSource;
}


void file_manager::save_project(std::string output_dir)
{
    //Tengo que empezar a guardar todo en un archivo json
    std::ofstream MyFile(output_dir.c_str());
    MyFile << "{\"Game\": {";
    Game::save(MyFile);
    MyFile << "}}";
    MyFile.close();
}