#pragma once
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#pragma comment(lib, "OpenGL32")

int whatPress = 0;

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (action == GLFW_PRESS && action != GLFW_RELEASE)
    {
        whatPress = key;
        
    }
    if (action == GLFW_RELEASE)
    {
        whatPress = 0;
    }
}

namespace MuSeoun_Engine
{
    class MWindowUtil
    {
    private:
        GLFWwindow* window;
        
    public:
        MWindowUtil(int width, int height, char title[], float halfX, float halfY, int Xblock, int Yblock)
        {
            glfwSetErrorCallback(error_callback);
            if (!glfwInit())
                exit(EXIT_FAILURE);
            window = glfwCreateWindow(width, height, title, NULL, NULL);
            if (!window)
            {
                glfwTerminate();
                exit(EXIT_FAILURE);
            }
            glfwMakeContextCurrent(window);
            glfwSetKeyCallback(window, key_callback);
            glClearColor(1, 1, 1, 1);
            
        }
        ~MWindowUtil()
        {
            glfwDestroyWindow(window);
            glfwTerminate();
        }

        int FindKey()
        {
            return whatPress;
        }

        void Clear()
        {
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void glBeginExtend(double x, double y, int r, int g, int b, double* realX, double* realY, GLenum mode)
        {
            *realX = x / 20.0 - 1;
            *realY = -y / 15.0 + 2 / 3.0;
            glBegin(mode);
            glColor3f(r / 255.0, g / 255.0, b / 255.0);
        }

        void PrintRectangle(double x, double y, int r, int g, int b)
        {
            double realX, realY;
            glBeginExtend(x, y, r, g, b, &realX, &realY, GL_TRIANGLE_STRIP);
            glVertex2f(realX - 0.1, realY - 0.1);
            glVertex2f(realX + 0.1, realY - 0.1);
            glVertex2f(realX - 0.1, realY + 0.1);
            glVertex2f(realX + 0.1, realY + 0.1);
            glEnd();
        }
        void PrintRectangle1(double x, double y, int r, int g, int b)
        {
            double realX, realY;
            glBeginExtend(x, y, r, g, b, &realX, &realY, GL_TRIANGLE_STRIP);
            glVertex2f(realX - 0.05, realY - 0.05);
            glVertex2f(realX + 0.05, realY - 0.05);
            glVertex2f(realX - 0.05, realY + 0.05);
            glVertex2f(realX + 0.05, realY + 0.05);
            glEnd();
        }

        void WindowEvent()
        {
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        bool isEnd()
        {
            return glfwWindowShouldClose(window);
        }
    };
}