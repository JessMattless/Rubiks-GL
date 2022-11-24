#ifndef SAVE_FILE_H
#define SAVE_FILE_H

#include <vector>
#include "cube.h"

void saveFile(std::vector<Cube> cubeArray);
void loadFile(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& colors);

#endif
