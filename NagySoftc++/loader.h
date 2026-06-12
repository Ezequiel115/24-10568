#ifndef LOADER_H
#define LOADER_H
#include <vector>
#include <string>
#include "structures.h"

std::vector<Coord_3D> load_data(const std::string& filename);
#endif