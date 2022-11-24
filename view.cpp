#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>
#include <stdio.h>

#include "view.h"
#include <string>

bool dragView = false;

glm::vec3 position = glm::vec3(6, 6, 6); // The position of the camera
glm::vec3 focus = glm::vec3(1.5f, 1.5f, 1.5f); // The point in the world the camera is looking at

float FoV = 60.0f; // Field of view

float speedMultiplier = 0.5f; // How fact the camera rotates when dragged

// Initialize matrices to be used later
glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix() {
    // Returns the view matrix
    return ViewMatrix;
}
glm::mat4 getProjectionMatrix() {
    // Returns the projection matrix
    return ProjectionMatrix;
}

void toggleDrag(bool active) {
    // returns true if the user is holding right mouse
    switch (active) {
        case true:
            dragView = true; break;
        case false:
            dragView = false; break;
    }
}

void computeMatrices(GLFWwindow* window) {
    // Do the math to determine where the camera is, using its position and rotation
    static double lastTime = glfwGetTime();

    int windowW, windowH;
    glfwGetWindowSize(window, &windowW, &windowH);

    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    // We save previous mouse speed so next frame we can see the accelleration of the mouse
    // Initialized to the centre of the screen on the first frame
    static float lastMouseX = windowW / 2;
    static float lastMouseY = windowH / 2;

    // Get the curront cursor position on the screen
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    // Grab the current mouse speed, multiplying it by a speed multiplier to make it smooth
    float mouseSpeedX = (mouseX - lastMouseX) * speedMultiplier;
    float mouseSpeedY = (mouseY - lastMouseY)* speedMultiplier;

    // multiply the angles by delta time to make sure they don't change too fast
    float pitchAngle = -(mouseSpeedX * deltaTime);
    float yawAngle = (mouseSpeedY * deltaTime);

    //Initialize direction vector, as well as up and right vectors. Normalize the up and right vectors.
    glm::vec3 direction = normalize(position - focus);
    glm::vec3 up = { 0.0f, -1.0f, 0.0f };
    glm::vec3 right = normalize(glm::cross(up, direction));
    up = normalize(glm::cross(right, direction));

    // Get a vector of where the camera is looking
    glm::vec3 focusVector = position - focus;
    
    // Make some base matrices for pitch and yaw, initialize them to 1
    glm::mat4 pitchMatrix = glm::mat4(1.f);
    glm::mat4 yawMatrix = glm::mat4(1.f);

    // Rotate the pitch and yaw matrices by the angles given
    pitchMatrix = (glm::rotate(pitchMatrix, pitchAngle, up));
    yawMatrix = (glm::rotate(yawMatrix, yawAngle, right));

    // Move the focusVector along the rotation lines
    focusVector = glm::vec3(pitchMatrix * glm::vec4(focusVector, 0.f));
    focusVector = glm::vec3(yawMatrix * glm::vec4(focusVector, 0.f));

    // If the right mouse is held, move the current camera position to the new location defined by the focusVector
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)) position = focusVector + focus;

    // Projection matrix : 45° Field of View, 1:1 ratio, display range : 0.1 unit <-> 100 units
    ProjectionMatrix = glm::perspective(glm::radians(FoV), 1.0f, 0.1f, 100.0f);

    ViewMatrix = glm::lookAt(
        position,   // Camera is here
        focus,      // Look at the world origin (0, 0, 0)
        up          // Head is up (set to 0,-1,0 to look upside-down
    );

    
    // For the next frame, the "last time" will be "now"
    // Also set the "last" mouse x/y to the current one ready for the next frame
    lastTime = currentTime;
    lastMouseX = mouseX;
    lastMouseY = mouseY;
}