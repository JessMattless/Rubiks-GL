#include <glm/glm.hpp>

#ifndef VIEW_H
#define VIEW_H

glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
void computeMatrices(GLFWwindow* window);
void toggleDrag(bool active);

#endif