#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Constants
const unsigned int WINDOW_WIDTH  = 800;
const unsigned int WINDOW_HEIGHT = 600;
const char*        WINDOW_TITLE  = "GLFW";

int main()
{
  // GLFW initialization
  glfwInit();

  // Window Hints
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

  // Clearing the color buffer
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glClearColor(0.68f, 0.78f, 0.62f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(window);

  // Main loop
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
  }

  // Cleaning up and exitting
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
