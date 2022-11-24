#include <iostream>
#include <fstream>
#include <string>
#include <glm/gtx/io.hpp>
#include <algorithm>
#include <numbers>
#include <iterator>
#include <sstream>
#include <cassert>

#include "save_file.h"

void saveFile(std::vector<Cube> cubeArray) {
	// Save the data from the current array of cubes (colors and positions) to a file, ready to be read from later to load the file
	std::ofstream _file("Save.cube");

	for (int i = 0; i < cubeArray.size(); i++) {
		// For each cube, get the position and colours, and add them to the file.
		Cube cube = cubeArray[i];
		glm::vec3 cubePos = cube.getPosition();
		std::vector<glm::vec3> cubeColors = cube.getColors();

		_file << "v " << cubePos << "\n";
		for (int j = 0; j < cubeColors.size(); j++) {
			_file << "c " << cubeColors[j] << "\n";
		}
	}

	_file.close();
}

void loadFile(std::vector<glm::vec3> &positions, std::vector<glm::vec3> &colors) {
	// Load a file and extract the data from it (colours of vertices, and positions of cubes)
	bool isPos = false; // set to true if the current line of the file being red is a position vertex instead of a colour one
	std::string data;

	// Open the file
	std::ifstream _file("Save.cube");

	while (getline(_file, data)) {
		// Read the file line by line.
		if (data[0] == 'v') isPos = true;
		else isPos = false;

		// The way the data was saved added some whitespace and square brackets, remove those and clean the data so it can be loaded into a vector.
		std::string formattedData = data.substr(3, data.size() -4);

		// Remove all spaces from the formatted string
		formattedData.erase(std::remove_if(formattedData.begin(), formattedData.end(), [](unsigned char x) { return std::isspace(x); }), formattedData.end());
		std::replace(formattedData.begin(), formattedData.end(), ',', ' ');

		// Create a temporary vector to be used for outputting data
		std::vector<float> tempVector;

		// Build an istream that holds the input string
		std::istringstream iss(formattedData);

		// Iterate over the istream, using >> to grab floats from the line of data
		// and push_back to store them in the vector
		std::copy(std::istream_iterator<float>(iss),
			std::istream_iterator<float>(),
			std::back_inserter(tempVector));

		// If the vector is a position one, load it into the correct list, else load it into the colour one.
		if (isPos) positions.push_back({ tempVector[0], tempVector[1], tempVector[2] });
		else colors.push_back({ tempVector[0], tempVector[1], tempVector[2] });
	}
}