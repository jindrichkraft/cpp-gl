#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>

#include "Headers/Shader.hpp"
#include "Headers/VAO.hpp"
#include "Headers/VBO.hpp"
#include "Headers/EBO.hpp"

// Constants
const unsigned int WINDOW_WIDTH  = 800;
const unsigned int WINDOW_HEIGHT = 600;
const char*        WINDOW_TITLE  = "GLFW";

// Shaders
const char* vertexShaderSource = " #version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.f);\n"
  "}\0";

const char* fragmentShaderSource = " #version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "  FragColor = vec4(0.12f, 0.12f, 0.12f, 1.f);\n"
  "}\n\0";

int main()
{
  // GLFW initialization
  glfwInit();

  // Window Hints
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Vertices
  GLfloat vertices[] =
  {
    -0.5f,     -0.5f * float(sqrt(3)) / 3,     0.f,
     0.5f,     -0.5f * float(sqrt(3)) / 3,     0.f,
     0.0f,      0.5f * float(sqrt(3)) * 2 / 3, 0.f,
    -0.5f / 2,  0.5f * float(sqrt(3)) / 6,     0.f,
     0.5f / 2,  0.5f * float(sqrt(3)) / 6,     0.f,
     0.f,      -0.5f * float(sqrt(3)) / 3,     0.f
  };

  GLuint indices[] =
  {
    0, 3, 5,
    3, 2, 4,
    5, 4, 1
  };

  // Creating the GLFW window
  GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window!" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // GLEW initialization
  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    std::cout << "Failed to initialize GLEW!" << std::endl;
    glfwTerminate();
    return -1;
  }

  Shader shaderProgram("src/Shaders/default.vert", "src/Shaders/default.frag");
  VAO VAO1;
  VAO1.Bind();
  VBO VBO1(vertices, sizeof(vertices));
  EBO EBO1(indices, sizeof(indices));

  VAO1.LinkVBO(VBO1, 0);
  VAO1.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();

  // Viewport
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glfwSwapBuffers(window);

  // Viewport
  while (!glfwWindowShouldClose(window))
  {
    glClearColor(0.68f, 0.78f, 0.62f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    shaderProgram.Activate();
    VAO1.Bind();
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  // Deleting the VAO, VBO, EBO, and the shader program
  VAO1.Delete();
  VBO1.Delete();
  EBO1.Delete();
  shaderProgram.Delete();

  // Cleaning up and exitting
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
