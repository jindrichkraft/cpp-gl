#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>

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
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.f,
     0.5f, -0.5f * float(sqrt(3)) / 3, 0.f,
     0.f,   0.5f * float(sqrt(3)) * 2, 0.f
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

  // Shaders
  int shaderSuccess;
  char shaderInfoLog[512];

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shaderSuccess);
  if(!shaderSuccess)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, shaderInfoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << shaderInfoLog << std::endl;
  };

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &shaderSuccess);
  if(!shaderSuccess)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, shaderInfoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << shaderInfoLog << std::endl;
  };

  // Shader Program
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

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
