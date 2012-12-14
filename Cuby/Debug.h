#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

#define NOTE(msg) std::cout <</* "[" << __FILE__ << "][Line " << __LINE__ << "] " <<*/ msg << std::endl;

#endif