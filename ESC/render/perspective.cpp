//
//  perspective.cpp
//  ESC
//
//  Created by Chaidhat Chaimongkol on 27/04/2019.
//  Copyright © 2019 Chai112. All rights reserved.
//

#include "perspective.hpp"

//#include "shader.hpp" // must be above glfw
#include "mouseInput.hpp"

#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/gtc/matrix_transform.hpp>

void V_Perspective::update (GLFWwindow* window, MouseIn mouseIn, glm::vec3 playerTransform, GLuint shader_programme)
{

// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) 4 / (float)3, 0.1f, 100.0f);

// Or, for an ortho camera :
//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

// draw points 0-3 from the currently bound VAO with current in-use shader

// Camera matrix
glm::mat4 View = glm::lookAt(
                             playerTransform, // Camera is at (4,3,3), in World Space
                             glm::vec3(mouseIn.x(), mouseIn.y(), mouseIn.z()) + playerTransform,
                             glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                             );

//gl_log("\nx %f %f\n", yMouse * 100, sinf(((yMouse-4.5)/4.5)*180*0.01745329252));

// Model matrix : an identity matrix (model will be at the origin)
glm::mat4 Model = glm::mat4(1.0f);
// Our ModelViewProjection : multiplication of our 3 matrices
glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around

// Get a handle for our "MVP" uniform
// Only during the initialisation
GLuint MatrixID = glGetUniformLocation(shader_programme, "MVP");

// Send our transformation to the currently bound shader, in the "MVP" uniform
// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
};
