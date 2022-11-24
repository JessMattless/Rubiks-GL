#include "cube_array.h"

#include <iostream>

#include "save_file.h"

void CubeArray::addCubeToArray(Cube cube) {
	// Add a cube to the internal cube array
	_cube_array.push_back(cube);
}

void CubeArray::createDefaultCubeArray() {
	// Create a default cube, unscrambled, and set each colour on the cube correctly (black if it isn't shown on the outside of the cube)
	for (int z = 0; z < 3; z++) {
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				Cube::Color North = Cube::Color::Black;
				Cube::Color East = Cube::Color::Black;
				Cube::Color South = Cube::Color::Black;
				Cube::Color West = Cube::Color::Black;
				Cube::Color Up = Cube::Color::Black;
				Cube::Color Down = Cube::Color::Black;

				Cube cube({ (float)x, (float)y, (float)z }, 1);

				if (z == 2) North = Cube::Color::Green;
				if (x == 0) West = Cube::Color::Orange;
				if (z == 0) South = Cube::Color::Blue;
				if (x == 2) East = Cube::Color::Red;
				if (y == 0) Down = Cube::Color::Yellow;
				if (y == 2) Up = Cube::Color::White;

				cube.setColors(North, East, South, West, Up, Down);

				addCubeToArray(cube);
			}
		}
	}
}

void CubeArray::getCubeData(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& colors) {
	// A function that grabs all of the vector and colour data from each cube in _cube_array to be rendered by the program.
	std::vector<glm::vec3> verts;
	std::vector<glm::vec3> cols;

	std::vector<glm::vec3> tris = getCubeVectorData();
	verts.insert(verts.end(), tris.begin(), tris.end());

	std::vector<glm::vec3> colorCoords = getCubeColorData();
	cols.insert(cols.end(), colorCoords.begin(), colorCoords.end());

	vertices = verts;
	colors = cols;
}

std::vector<glm::vec3> CubeArray::getCubeVectorData() {
	// Get the vector data from every cube in _cube_array
	std::vector<glm::vec3> vectorData;
	for (int i = 0; i < _cube_array.size(); i++) {
		std::vector<glm::vec3> tris = _cube_array[i].getTriangles();
		vectorData.insert(vectorData.end(), tris.begin(), tris.end());
	}

	return vectorData;
}

std::vector<glm::vec3> CubeArray::getCubeColorData() {
	// Get the color data from every cube in _cube_array
	std::vector<glm::vec3> colorData;
	for (int i = 0; i < _cube_array.size(); i++) {
		std::vector<glm::vec3> colors = _cube_array[i].getColors();
		colorData.insert(colorData.end(), colors.begin(), colors.end());
	}

	return colorData;
}

void CubeArray::rotateFace(Cube::Rotation rotation) {
	// Checks where a sub-cube is and rotates it accordingly if it needs to be moved and rotated
	std::vector<Cube> face;
	switch (rotation) {
		case Cube::Rotation::f: case Cube::Rotation::fP:
			for (int i = 0; i < _cube_array.size(); i++) {
				if (_cube_array[i].getPosition().z == 2) {
					_cube_array[i].rotateCube(rotation);
				}
			}; break;
		case Cube::Rotation::r: case Cube::Rotation::rP:
			for (int i = 0; i < _cube_array.size(); i++) {
				if (_cube_array[i].getPosition().x == 2) {
					_cube_array[i].rotateCube(rotation);
				}
			}; break;
		case Cube::Rotation::b: case Cube::Rotation::bP:
			for (int i = 0; i < _cube_array.size(); i++) {
				if (_cube_array[i].getPosition().z == 0) {
					_cube_array[i].rotateCube(rotation);
				}
			}; break;
		case Cube::Rotation::l: case Cube::Rotation::lP:
			for (int i = 0; i < _cube_array.size(); i++) {
				if (_cube_array[i].getPosition().x == 0) {
					_cube_array[i].rotateCube(rotation);
				}
			}; break;
		case Cube::Rotation::u: case Cube::Rotation::uP:
			for (int i = 0; i < _cube_array.size(); i++) {
				if (_cube_array[i].getPosition().y == 2) {
					_cube_array[i].rotateCube(rotation);
				}
			}; break;
		case Cube::Rotation::d: case Cube::Rotation::dP:
			for (int i = 0; i < _cube_array.size(); i++) {
				if (_cube_array[i].getPosition().y == 0) {
					_cube_array[i].rotateCube(rotation);
				}
			}; break;
		default: break;
	}
}

void CubeArray::saveDataToFile() {
	// Used as a passthrough function to save data to a file
	saveFile(_cube_array);
}

void CubeArray::loadDataFromFile() {
	//This function loads saved data from a file, the location of each cube and the colour of each side of the cube.
	// 
	// I wasn't able to get this working before submission sadly, as I was having issues with indexing and didn't have time to fix them
	// 
	//std::vector<glm::vec3> tempColors;
	//std::vector<glm::vec3> tempPositions;
	//loadFile(tempColors, tempPositions);

	//_cube_array = std::vector<Cube>();

	//for (int i = 0; i < 27; i++) {
	//	Cube tempCube(tempPositions[i], 1);
	//	std::vector<glm::vec3> cubeColors;
	//	for (int j = 0; j < 36; j++) {
	//		cubeColors.push_back(tempColors[(i * 34) + j]);
	//	}

	//	addCubeToArray(tempCube);
	//}
}