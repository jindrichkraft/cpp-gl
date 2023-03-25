#include "../Headers/Shader.hpp"

std::string get_file_contents(const char* fileName)
{
  std::ifstream in(fileName, std::ios::binary);
  if (in)
  {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return contents;
  }
  throw errno;
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
  // Reading the shader files
  std::string vertexCode = get_file_contents(vertexFile);
  std::string fragmentCode = get_file_contents(fragmentFile);

  const char* vertexSource = vertexCode.c_str();
  const char* fragmentSource = fragmentCode.c_str();

  // Compilation variables
  int shaderSuccess;
  char shaderInfoLog[512];

  // Vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shaderSuccess);
  if(!shaderSuccess)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, shaderInfoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << shaderInfoLog << std::endl;
  };

  // Fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &shaderSuccess);
  if(!shaderSuccess)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, shaderInfoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << shaderInfoLog << std::endl;
  };

  // Shader Program
  this->ID = glCreateProgram();
  glAttachShader(this->ID, vertexShader);
  glAttachShader(this->ID, fragmentShader);
  glLinkProgram(this->ID);

  // Cleaning up shaders
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
  glUseProgram(this->ID);
}

void Shader::Delete()
{
  glDeleteProgram(this->ID);
}
