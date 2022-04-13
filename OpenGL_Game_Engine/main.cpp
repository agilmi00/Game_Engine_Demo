//
//  main.cpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <GLFW/glfw3.h>

#ifdef __APPLE__


#include "Programa.hpp"
#endif

int main()
{
    Programa programa = Programa();
    programa.run();
}
