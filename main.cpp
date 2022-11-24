#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "cube.h"
#include "cube_array.h"

#include "shaders.h"
#include "view.h"
#include "save_file.h"

using namespace glm;

CubeArray cubeArray;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Used for checking key presses, recieves key press/release events as well as their mods (shift, ctrl, alt, etc.)
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                // If the escape key is pressed, prepare to close the window
                glfwSetWindowShouldClose(window, GLFW_TRUE); break;
            case GLFW_KEY_Q:
                cubeArray.rotateFace(Cube::Rotation::f); break;
            case GLFW_KEY_A:
                cubeArray.rotateFace(Cube::Rotation::fP); break;
            case GLFW_KEY_W:
                cubeArray.rotateFace(Cube::Rotation::r); break;
            case GLFW_KEY_S:
                cubeArray.rotateFace(Cube::Rotation::rP); break;
            case GLFW_KEY_E:
                cubeArray.rotateFace(Cube::Rotation::b); break;
            case GLFW_KEY_D:
                cubeArray.rotateFace(Cube::Rotation::bP); break;
            case GLFW_KEY_R:
                cubeArray.rotateFace(Cube::Rotation::l); break;
            case GLFW_KEY_F:
                cubeArray.rotateFace(Cube::Rotation::lP); break;
            case GLFW_KEY_T:
                cubeArray.rotateFace(Cube::Rotation::u); break;
            case GLFW_KEY_G:
                cubeArray.rotateFace(Cube::Rotation::uP); break;
            case GLFW_KEY_Y:
                cubeArray.rotateFace(Cube::Rotation::d); break;
            case GLFW_KEY_H:
                cubeArray.rotateFace(Cube::Rotation::dP); break;
            case GLFW_KEY_BACKSPACE:
                // Save data to an external file
                cubeArray.saveDataToFile(); break;
            case GLFW_KEY_ENTER:
                //Load data from an external file
                // I didn't complete this in time, but most of the code is there
                //cubeArray.loadDataFromFile(); break;
            default:
                break;
        }
    }
}

void printIntroMessage() {
    // Just put into a separate function to stopfrom clogging up main()
    // Instructions on how to use the program
    printf("Welcome to RubiksGL, a 3d Rubiks cube made using OpenGL and C++\n");
    printf("To play, hold right click and drag the mouse to move the camera\n");
    printf("To rotate the different faces, there are some hotkeys:\n");
    printf("Green Face  : Q for clockwise and A for anti-clockwise\n");
    printf("Red Face    : W for clockwise and S for anti-clockwise\n");
    printf("Blue Face   : E for clockwise and D for anti-clockwise\n");
    printf("Orange Face : R for clockwise and F for anti-clockwise\n");
    printf("White Face  : T for clockwise and G for anti-clockwise\n");
    printf("Yellow Face : Y for clockwise and H for anti-clockwise\n");
    printf("Preff Escape to exit without saving\n");
    printf("Press Backspace to Save your cube before you exit\n");
    printf("Press Enter to Load a saved cube (If there is one)");
}

int main() {
    // Initialize an empty window
    GLFWwindow* window;

    // Check if glfw init happened, if not then exit
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Used for MacOS
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

    // The actual window, sets the width, height, name, fullscreen window (null for windowed)
    // and any other windows to share context with (null for none) 
    window = glfwCreateWindow(728, 728, "RubiksGL", NULL, NULL);
    // If there is no window, close the program
    if (!window) {
        glfwTerminate();
        return -1;
    }
    // Set the current context of the window
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return -1;
    }

    // Load shaders from a shader file to be used to calculate graphics
    GLuint programID = LoadShaders("VertexShader.vert", "FragmentShader.frag");

    // get a handle to be used during initialization for the view matrix
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");


    // Create a Vertex Array Object (VAO), before binding it as the current VAO
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    cubeArray.createDefaultCubeArray();

    // Make empty vectors to be filled with data from the cube array
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;

    // Fill the above vectors with data
    cubeArray.getCubeData(vertices, colors);

    // Create vertex buffer
    // Generate a buffer, and put the identifier to it inside vertexBuffer
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_DYNAMIC_DRAW);

    // Same thing with a colour buffer
    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), &colors[0], GL_DYNAMIC_DRAW);

    // Enable some graphics settings for things like background culling
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);


    // Initialize width/height, Get the frame buffer size to use for glfwViewport
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    printIntroMessage();

    // While the current window should stay open, run the loop, if not then close the window
    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Create Matrices used to draw the scene
        computeMatrices(window);
        glm::mat4 ProjectionMatrix = getProjectionMatrix();
        glm::mat4 ViewMatrix = getViewMatrix();

        glm::mat4 ModelMatrix = glm::mat4(1.0f);

        glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);


        // Get the current time since initialization
        double time = glfwGetTime();

        glUseProgram(programID);

        //////////////////////////////
        ///////Draw things here///////
        //////////////////////////////
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

        cubeArray.getCubeData(vertices, colors);

        // Reload the vertex buffer, so any changes in cube positions are rendered
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_DYNAMIC_DRAW);
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
        );

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        // Same thing as for the vertex buffer
        glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), &colors[0], GL_DYNAMIC_DRAW);
        glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
        );
        glDrawArrays(GL_TRIANGLES, 0, cubeArray.getCubeArray().size() * 6 * 2 * 3);
        glDisableVertexAttribArray(0);

        // There are 2 buffers in used to render, a back and front buffer, one is the current displayed, and the back is the one you render to.
        // when the frame is finished being rendered, the buffers get swapped
        glfwSwapBuffers(window);
        // The swap interval says how many frames to wait between switching buffers
        // setting to 1 helps with screen tearing from rendering multiple buffers per frame, any higher and there tends to be input lag
        glfwSwapInterval(1);

        // Check for any events that have happened, before processing them
        glfwPollEvents();
    }

    // Delete the vertex buffer when we're done with the program
    glDeleteBuffers(1, &vertexBuffer);

    // This only runs when the window is closed
    glfwTerminate();
    return 0;
}
