#ifndef CUBE_ARRAY_H
#define CUBE_ARRAY_H

#include <glm/glm.hpp>
#include <vector>

#include "cube.h"

class CubeArray {
private:
	std::vector<Cube> _cube_array;

	std::vector<glm::vec3> getCubeVectorData();
	std::vector<glm::vec3> getCubeColorData();
public:
	void addCubeToArray(Cube cube);

	void createDefaultCubeArray();

	void getCubeData(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& colors);

	std::vector<Cube> getCubeArray() { return _cube_array; };

	void rotateFace(Cube::Rotation rotation);
	void saveDataToFile();
	void loadDataFromFile();
};

#endif