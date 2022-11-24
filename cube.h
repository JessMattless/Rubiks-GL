#ifndef CUBE_H
#define CUBE_H

#include <glm/glm.hpp>
#include <vector>

class Cube {
public:
	enum class Color { Green, Red, Blue, Orange, White, Yellow, Black };
	enum class Rotation { f, fP, r, rP, b, bP, l, lP, u, uP, d, dP };

	Cube(glm::vec3 pos, float size, Color N = Color::Black, Color E = Color::Black, Color S = Color::Black, Color W = Color::Black, Color U = Color::Black, Color D = Color::Black);

	void setPosition(glm::vec3 position);
	void setColors(Color N, Color E, Color S, Color W, Color U, Color D);
	void setColors(std::vector<glm::vec3> colorArray);
	void rotateCube(Rotation direction);

	glm::vec3 getPosition() { return _position; }
	std::vector<glm::vec3> getTriangles() { return _triangles; }
	std::vector<glm::vec3> getColors() { return _colors; }

private:
	glm::vec3 _position;
	float _size;
	std::vector<glm::vec3> _triangles;
	std::vector<glm::vec3> _colors;
	std::vector<Color> _colorList;

	void setTriangles();
	glm::vec3 getColorCode(Cube::Color c);

};

#endif
#pragma once
