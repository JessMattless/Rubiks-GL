#include "cube.h"
#include <iostream>

Cube::Cube(glm::vec3 pos, float size, Color N, Color E, Color S, Color W, Color U, Color D) {
	// Default constructor, initializes with required position and size, but defaults all face colours to black
	_size = size;
	setPosition(pos);
	setColors(N, E, S, W, U, D);
}

void Cube::setPosition(glm::vec3 position) {
	// Called by the class constructor, 
	_position = position;
	setTriangles();
}

void Cube::setTriangles() {
	// Create each triangle, 3 points per triangle, 2 triangles per face. For a total of 12 triangles per cube
	_triangles = std::vector<glm::vec3>{
		// North face
		{_position.x + _size, _position.y + _size, _position.z + _size},
		{_position.x + _size, _position.y        , _position.z        },
		{_position.x + _size, _position.y + _size, _position.z        },

		{_position.x + _size, _position.y        , _position.z        }, 
		{_position.x + _size, _position.y + _size, _position.z + _size},
		{_position.x + _size, _position.y        , _position.z + _size},
		// East face
		{_position.x + _size, _position.y        , _position.z + _size},
		{_position.x        , _position.y        , _position.z        },
		{_position.x + _size, _position.y        , _position.z        },

		{_position.x + _size, _position.y        , _position.z + _size},
		{_position.x        , _position.y        , _position.z + _size},
		{_position.x        , _position.y        , _position.z        },
		// South face
		{_position.x        , _position.y        , _position.z        },
		{_position.x        , _position.y        , _position.z + _size},
		{_position.x        , _position.y + _size, _position.z + _size},

		{_position.x        , _position.y        , _position.z        },
		{_position.x        , _position.y + _size, _position.z + _size},
		{_position.x        , _position.y + _size, _position.z        },
		// West face
		{_position.x + _size, _position.y + _size, _position.z + _size},
		{_position.x + _size, _position.y + _size, _position.z        },
		{_position.x        , _position.y + _size, _position.z        },

		{_position.x + _size, _position.y + _size, _position.z + _size},
		{_position.x        , _position.y + _size, _position.z        },
		{_position.x        , _position.y + _size, _position.z + _size},
		// Top face
		{_position.x        , _position.y + _size, _position.z + _size},
		{_position.x        , _position.y        , _position.z + _size},
		{_position.x + _size, _position.y        , _position.z + _size},

		{_position.x + _size, _position.y + _size, _position.z + _size},
		{_position.x        , _position.y + _size, _position.z + _size},
		{_position.x + _size, _position.y        , _position.z + _size},
		// Bottom face
		{_position.x + _size, _position.y + _size, _position.z        },
		{_position.x        , _position.y        , _position.z        },
		{_position.x        , _position.y + _size, _position.z        },

		{_position.x + _size, _position.y + _size, _position.z        },
		{_position.x + _size, _position.y        , _position.z        },
		{_position.x        , _position.y        , _position.z        },
	};
}

void Cube::setColors(Color N, Color E, Color S, Color W, Color U, Color D) {
	// Get the colours used for each face on the cube
	std::vector<glm::vec3> colors;
	_colorList = { N, E, S, W, U, D };

	for (int i = 0; i < 6; i++) { // 6 Sides
		for (int j = 0; j < 2; j++) { // 2 Triangles
			for (int k = 0; k < 3; k++) { // 3 Points per triangle
				switch (i) {
					// The actual colours are in a different function to make this easier to read
					case 0:
						colors.push_back(getColorCode(E)); break;
					case 1:
						colors.push_back(getColorCode(D)); break;
					case 2:
						colors.push_back(getColorCode(W)); break;
					case 3:
						colors.push_back(getColorCode(U)); break;
					case 4:
						colors.push_back(getColorCode(N)); break;
					case 5:
						colors.push_back(getColorCode(S)); break;
					default: break;
				}
			}
		}
	}

	_colors = colors;
}

void Cube::setColors(std::vector<glm::vec3> colorArray) {
	// Used when loading data from a file
	_colors = colorArray;
}

glm::vec3 Cube::getColorCode(Cube::Color c) {
	// Grab colours used when drawing a face
	switch (c) {
		case Color::Green:
			return { 0.000f, 0.611f, 0.274f };
		case Color::Red:
			return { 0.721f, 0.039f, 0.192f };
		case Color::Blue:
			return { 0.000f, 0.266f, 0.686f };
		case Color::Orange:
			return { 1.000f, 0.341f, 0.000f };
		case Color::White:
			return { 0.900f, 0.900f, 0.900f };
		case Color::Yellow:
			return { 1.000f, 0.839f, 0.000f };
		case Color::Black: default:
			return { 0.200f, 0.200f, 0.200f };
	}
}

void Cube::rotateCube(Rotation direction) {
	// Values used to know what position and rotation a cube must be in when a face is rotated.
	switch (direction) {
	case Rotation::f: case Rotation::bP:
		// Corner pieces
		if (_position.x == 0 && _position.y == 0) {
			setPosition({ _position.x, _position.y + 2, _position.z });
		}
		else if (_position.x == 0 && _position.y == 2) {
			setPosition({ _position.x + 2, _position.y, _position.z });
		}
		else if (_position.x == 2 && _position.y == 2) {
			setPosition({ _position.x, _position.y - 2, _position.z });
		}
		else if (_position.x == 2 && _position.y == 0) {
			setPosition({ _position.x - 2, _position.y, _position.z });
		}
		// Side Pieces
		else if (_position.x == 0 && _position.y == 1) {
			setPosition({ _position.x + 1, _position.y + 1, _position.z });
		}
		else if (_position.x == 1 && _position.y == 2) {
			setPosition({ _position.x + 1, _position.y - 1, _position.z });
		}
		else if (_position.x == 2 && _position.y == 1) {
			setPosition({ _position.x - 1, _position.y - 1, _position.z });
		}
		else if (_position.x == 1 && _position.y == 0) {
			setPosition({ _position.x - 1, _position.y + 1, _position.z });
		}

		setColors(_colorList[0], _colorList[4], _colorList[2], _colorList[5], _colorList[3], _colorList[1]);

		break;
	case Rotation::fP: case Rotation::b:
		// Corner pieces
		if (_position.x == 0 && _position.y == 0) {
			setPosition({ _position.x + 2, _position.y, _position.z });
		}
		else if (_position.x == 2 && _position.y == 0) {
			setPosition({ _position.x, _position.y + 2, _position.z });
		}
		else if (_position.x == 2 && _position.y == 2) {
			setPosition({ _position.x - 2, _position.y, _position.z });
		}
		else if (_position.x == 0 && _position.y == 2) {
			setPosition({ _position.x, _position.y - 2, _position.z });
		}
		// Side Pieces
		else if (_position.x == 0 && _position.y == 1) {
			setPosition({ _position.x + 1, _position.y - 1, _position.z });
		}
		else if (_position.x == 1 && _position.y == 0) {
			setPosition({ _position.x + 1, _position.y + 1, _position.z });
		}
		else if (_position.x == 2 && _position.y == 1) {
			setPosition({ _position.x - 1, _position.y + 1, _position.z });
		}
		else if (_position.x == 1 && _position.y == 2) {
			setPosition({ _position.x - 1, _position.y - 1, _position.z });
		}

		setColors(_colorList[0], _colorList[5], _colorList[2], _colorList[4], _colorList[1], _colorList[3]);

		break;
	case Rotation::r: case Rotation::lP:
		// Corner pieces
		if (_position.z == 0 && _position.y == 0) {
			setPosition({ _position.x, _position.y, _position.z + 2 });
		}
		else if (_position.z == 2 && _position.y == 0) {
			setPosition({ _position.x, _position.y + 2, _position.z });
		}
		else if (_position.z == 2 && _position.y == 2) {
			setPosition({ _position.x, _position.y, _position.z - 2 });
		}
		else if (_position.z == 0 && _position.y == 2) {
			setPosition({ _position.x, _position.y - 2, _position.z });
		}
		// Side Pieces
		else if (_position.z == 0 && _position.y == 1) {
			setPosition({ _position.x, _position.y - 1, _position.z + 1 });
		}
		else if (_position.z == 1 && _position.y == 0) {
			setPosition({ _position.x, _position.y + 1, _position.z + 1 });
		}
		else if (_position.z == 2 && _position.y == 1) {
			setPosition({ _position.x, _position.y + 1, _position.z - 1 });
		}
		else if (_position.z == 1 && _position.y == 2) {
			setPosition({ _position.x, _position.y - 1, _position.z - 1 });
		}

		setColors(_colorList[5], _colorList[1], _colorList[4], _colorList[3], _colorList[0], _colorList[2]);

		break;
	case Rotation::rP: case Rotation::l:
		// Corner pieces
		if (_position.z == 0 && _position.y == 0) {
			setPosition({ _position.x, _position.y + 2, _position.z });
		}
		else if (_position.z == 0 && _position.y == 2) {
			setPosition({ _position.x, _position.y, _position.z + 2 });
		}
		else if (_position.z == 2 && _position.y == 2) {
			setPosition({ _position.x, _position.y - 2, _position.z });
		}
		else if (_position.z == 2 && _position.y == 0) {
			setPosition({ _position.x, _position.y, _position.z - 2 });
		}
		// Side Pieces
		else if (_position.z == 0 && _position.y == 1) {
			setPosition({ _position.x, _position.y + 1, _position.z + 1 });
		}
		else if (_position.z == 1 && _position.y == 2) {
			setPosition({ _position.x, _position.y - 1, _position.z + 1 });
		}
		else if (_position.z == 2 && _position.y == 1) {
			setPosition({ _position.x, _position.y - 1, _position.z - 1 });
		}
		else if (_position.z == 1 && _position.y == 0) {
			setPosition({ _position.x, _position.y + 1, _position.z - 1 });
		}

		setColors(_colorList[4], _colorList[1], _colorList[5], _colorList[3], _colorList[2], _colorList[0]);

		break;
	case Rotation::u: case Rotation::dP:
				// Corner pieces
		if (_position.x == 0 && _position.z == 0) {
			setPosition({ _position.x + 2, _position.y, _position.z });
		}
		else if (_position.x == 2 && _position.z == 0) {
			setPosition({ _position.x, _position.y, _position.z + 2});
		}
		else if (_position.x == 2 && _position.z == 2) {
			setPosition({ _position.x - 2, _position.y, _position.z });
		}
		else if (_position.x == 0 && _position.z == 2) {
			setPosition({ _position.x, _position.y, _position.z - 2 });
		}
		// Side Pieces
		else if (_position.x == 1 && _position.z == 0) {
			setPosition({ _position.x + 1, _position.y, _position.z + 1 });
		}
		else if (_position.x == 2 && _position.z == 1) {
			setPosition({ _position.x - 1, _position.y, _position.z + 1 });
		}
		else if (_position.x == 1 && _position.z == 2) {
			setPosition({ _position.x - 1, _position.y, _position.z - 1 });
		}
		else if (_position.x == 0 && _position.z == 1) {
			setPosition({ _position.x + 1, _position.y, _position.z - 1 });
		}

		setColors(_colorList[1], _colorList[2], _colorList[3], _colorList[0], _colorList[4], _colorList[5]);

		break;
	case Rotation::uP: case Rotation::d:
		// Corner pieces
		if (_position.x == 0 && _position.z == 0) {
			setPosition({ _position.x, _position.y, _position.z + 2 });
		}
		else if (_position.x == 0 && _position.z == 2) {
			setPosition({ _position.x + 2, _position.y, _position.z });
		}
		else if (_position.x == 2 && _position.z == 2) {
			setPosition({ _position.x, _position.y, _position.z - 2 });
		}
		else if (_position.x == 2 && _position.z == 0) {
			setPosition({ _position.x - 2, _position.y, _position.z });
		}
		// Side Pieces
		else if (_position.x == 0 && _position.z == 1) {
			setPosition({ _position.x + 1, _position.y, _position.z + 1 });
		}
		else if (_position.x == 1 && _position.z == 2) {
			setPosition({ _position.x + 1, _position.y, _position.z - 1 });
		}
		else if (_position.x == 2 && _position.z == 1) {
			setPosition({ _position.x - 1, _position.y, _position.z - 1 });
		}
		else if (_position.x == 1 && _position.z == 0) {
			setPosition({ _position.x - 1, _position.y, _position.z + 1 });
		}

		setColors(_colorList[3], _colorList[0], _colorList[1], _colorList[2], _colorList[4], _colorList[5]);

		break;
	}
}