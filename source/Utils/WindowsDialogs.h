#pragma once
#include <tchar.h>
#include <Windows.h>
#include <stdlib.h>
#include <string>
namespace Utils
{
    TCHAR* openFileDialog()
    {
        OPENFILENAME ofn;       // common dialog box structure
        TCHAR szFile[260] = {0};       // if using TCHAR macros

        // Initialize OPENFILENAME
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = NULL;
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = _T("Text Files\0*.txt\0Any File\0*.*\0");
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if (GetOpenFileName(&ofn) == TRUE)
        {
            printf("%s\n",szFile);
            return szFile;
        }
        return NULL;
    }
}