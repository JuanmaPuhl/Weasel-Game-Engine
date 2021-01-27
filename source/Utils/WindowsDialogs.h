#pragma once
#include <tchar.h>
#include <Windows.h>
#include <stdlib.h>
#include <string>
namespace Utils
{
    void openFileDialog(TCHAR* toReturn, int size)
    {
        OPENFILENAME ofn;       // common dialog box structure

        // Initialize OPENFILENAME
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = NULL;
        ofn.lpstrFile = toReturn;
        ofn.nMaxFile = size;
        ofn.lpstrFilter = _T("Text Files\0*.txt\0Any File\0*.*\0");
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if (GetOpenFileName(&ofn) == TRUE)
        {
            //printf("La direccion a abrir es: %s\n",toReturn);
        }
        else
            toReturn = NULL;
    }

    void saveFileDialog(TCHAR* toReturn, int size)
    {
        OPENFILENAME ofn;       // common dialog box structure

        // Initialize OPENFILENAME
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = NULL;
        ofn.lpstrFile = toReturn;
        ofn.nMaxFile = size;
        ofn.lpstrFilter = _T("Text Files\0*.txt\0Any File\0*.*\0");
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if (GetSaveFileName(&ofn) == TRUE)
        {
            //printf("La direccion a guardar es: %s\n",toReturn);
        }
        else
            toReturn =  NULL;
    }

}