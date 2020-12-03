#include "Debug.h"


void Debug::print(std::string msg, void** parameters, int parameters_size)
{
    std::cout << msg << " "<<((std::string**)(parameters)) <<std::endl;
}
