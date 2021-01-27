#pragma once
#include <tchar.h>
#include <Windows.h>
#include <stdlib.h>
#include <string>
namespace Utils
{
    /**
     * @brief Abre un dialogo de windows para abrir un archivo
     * 
     * @param toReturn Es el buffer en el que se guardará la dirección elegida por el usuario
     * @param size El tamaño máximo del buffer ingresado
     */
    void openFileDialog(TCHAR* toReturn, int size)
    {
        OPENFILENAME ofn;       // common dialog box structure

        // Initialize OPENFILENAME
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = NULL; //Despues cambiar por el handler de la ventana del engine para que quede bloqueado
        ofn.lpstrFile = toReturn;
        ofn.nMaxFile = size;
        ofn.lpstrFilter = _T("Text Files\0*.txt\0Any File\0*.*\0"); //Filtro de tipo de archivo
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

    /**
     * @brief Abre un dialogo de windows para guardar un archivo
     * 
     * @param toReturn Es el buffer en el que se guardará la dirección elegida por el usuario
     * @param size El tamaño máximo del buffer ingresado
     */
    void saveFileDialog(TCHAR* toReturn, int size)
    {
        OPENFILENAME ofn;       // common dialog box structure

        // Initialize OPENFILENAME
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = NULL; //Despues cambiar por el handler de la ventana del engine para que quede bloqueado
        ofn.lpstrFile = toReturn;
        ofn.nMaxFile = size;
        ofn.lpstrFilter = _T("Text Files\0*.txt\0Any File\0*.*\0"); //Filtro de tipo de archivo
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