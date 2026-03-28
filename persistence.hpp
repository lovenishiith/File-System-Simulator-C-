#ifndef PERSISTENCE_HPP
#define PERSISTENCE_HPP

#include "filesystem.hpp"

void saveState(Directory*, ofstream&);
Directory* loadstate();

#endif