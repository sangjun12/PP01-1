#pragma once

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "Image.hpp"
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
        GLuint texName;
        
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
            glClearColor(0, 0, 0, 1);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            glGenTextures(1, &texName);
            glBindTexture(GL_TEXTURE_2D, texName);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                GL_NEAREST);
            
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
        void PrintcoreRectangle(double x, double y, int r, int g, int b)
        {
            double realX, realY;
            glBeginExtend(x, y, r, g, b, &realX, &realY, GL_TRIANGLE_STRIP);
            glVertex2f(realX - 0.05, realY - 0.05);
            glVertex2f(realX + 0.05, realY - 0.05);
            glVertex2f(realX - 0.05, realY + 0.05);
            glVertex2f(realX + 0.05, realY + 0.05);
            glEnd();
        }

        void GameOverscreen(Image* myImage, GLenum format, double x1, double x2, double y1, double y2)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, myImage->width, myImage->height, 0, format, GL_UNSIGNED_BYTE, myImage->image);
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            glBindTexture(GL_TEXTURE_2D, texName);
            glBegin(GL_TRIANGLE_STRIP);
            glTexCoord2f(0.0, 0.0); glVertex3f(x1, y1, 0.0);
            glTexCoord2f(1.0, 0.0); glVertex3f(x2, y1, 0.0);
            glTexCoord2f(0.0, 1.0); glVertex3f(x1, y2, 0.0);
            glTexCoord2f(1.0, 1.0); glVertex3f(x2, y2, 0.0);
            glEnd();
            glFlush();
            glDisable(GL_TEXTURE_2D);
        }
        void GameStartscreen()
        {
            glClearColor(1, 1, 1, 1);
        }
        void GameClearscreen(Image* myImage, GLenum format, double x1, double x2, double y1, double y2)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, myImage->width, myImage->height, 0, format, GL_UNSIGNED_BYTE, myImage->image);
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            glBindTexture(GL_TEXTURE_2D, texName);
            glBegin(GL_TRIANGLE_STRIP);
            glTexCoord2f(0.0, 0.0); glVertex3f(x1, y1, 0.0);
            glTexCoord2f(1.0, 0.0); glVertex3f(x2, y1, 0.0);
            glTexCoord2f(0.0, 1.0); glVertex3f(x1, y2, 0.0);
            glTexCoord2f(1.0, 1.0); glVertex3f(x2, y2, 0.0);
            glEnd();
            glFlush();
            glDisable(GL_TEXTURE_2D);
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