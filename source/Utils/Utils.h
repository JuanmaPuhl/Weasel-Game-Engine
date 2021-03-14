#pragma once
#include <string>
#include <string.h>

std::string& sReplaceAll(std::string& sS, 
                         const std::string& sWhat, 
                         const std::string& sReplacement)
{
    size_t pos = 0, fpos;
    while ((fpos = sS.find(sWhat, pos)) != std::string::npos)
    {
        sS.replace(fpos, sWhat.size(), sReplacement);
        pos = fpos + sReplacement.size();
    }
    return sS;
}