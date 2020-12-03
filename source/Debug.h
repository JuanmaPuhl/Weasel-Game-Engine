#ifndef DEBUG_H
#define DEBUG_H
#include <stdio.h>
#include <string>
#include <iostream>
namespace Debug
{
    void print(std::string msg, void** parameters, int parameters_size);

}
#endif