#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>
/**
 * @brief lee un archivo en la direccion dada
 * 
 * @param dir La direccion del archivo
 * @return std::string el contenido del archivo
 */
std::string read_file(std::string dir);
/**
 * @brief Convierte un archivo a una forma mas amigable
 * 
 * @param source El contenido a convertir
 * @return std::vector<std::string> El texto convertido
 */
std::vector<std::string> parse_file(std::string& source);

#endif