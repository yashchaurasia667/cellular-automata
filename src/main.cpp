#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <unistd.h>

#include <automata.h>
#include <learnOpengl/camera.h>
#include <learnOpengl/shader.h>
#include <learnOpengl/utils.h>

unsigned int scr_width = 800, scr_height = 600;
unsigned char *automataTex = new unsigned char[scr_width * scr_height * 3];

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void generateAutomataTex();

int main()
{
  init(scr_width, scr_height);
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow *window =
      glfwCreateWindow(scr_width, scr_height, "TITLE_HERE", NULL, NULL);
  if (window == nullptr)
  {
    std::cout << "Failed to create a GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize opengl function pointers" << std::endl;
    return -1;
  }
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  {
    Shader shader("../src/shaders/automata.vs", "../src/shaders/automata.fs");

    unsigned int renderTex;
    glGenTextures(1, &renderTex);
    glBindTexture(GL_TEXTURE_2D, renderTex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, scr_width, scr_height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, automataTex);

    shader.bind();
    shader.setInt("renderTex", 0);

    glClearColor(0.4, 0.4, 0.4, 0.4);
    while (!glfwWindowShouldClose(window))
    {
      // sleep(1);
      processInput(window);
      glClear(GL_COLOR_BUFFER_BIT);

      generateAutomataTex();
      glBindTexture(GL_TEXTURE_2D, renderTex);
      glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, scr_width, scr_height, GL_RGB,
                      GL_UNSIGNED_BYTE, automataTex);
      shader.bind();
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, renderTex);
      renderQuad();

      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  }

  glfwTerminate();
  return 0;
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
  // scr_width = width;
  // scr_height = height;
  // init(scr_width, scr_height);
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void generateAutomataTex()
{
  int indx = 0;
  zhabotinsky(70, 3);

  const unsigned char darkBlue[3] = {0, 0, 0};
  const unsigned char darkYellow[3] = {255, 255, 255};

  for (int y = 0; y < scr_height; y++)
    for (int x = 0; x < scr_width; x++)
    {
      float t = ((float)cells[y][x] / 100.0f); // 0.0 to 1.0

      automataTex[indx + 0] = (unsigned char)(darkBlue[0] + t * (darkYellow[0] - darkBlue[0]));
      automataTex[indx + 1] = (unsigned char)(darkBlue[1] + t * (darkYellow[1] - darkBlue[1]));
      automataTex[indx + 2] = (unsigned char)(darkBlue[2] + t * (darkYellow[2] - darkBlue[2]));
      indx += 3;
    }
}