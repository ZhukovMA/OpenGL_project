#include <iostream>
#include <cmath>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "multyplyes.h"

// compile: g++ main.cpp -o hello -lGL -lGLEW -lglfw

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();
void new_func_size_callback(GLFWwindow* window, int width, int heigh);

GLfloat* get_figure();

const GLuint WIDTH = 800, HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX  =  WIDTH  / 2.0;
GLfloat lastY  =  HEIGHT / 2.0;
bool    keys[1024];
bool ret = true;

GLfloat APPROX = 0.01f;
GLfloat chill_height = 0.8f;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;


GLfloat x_rotation = 0.0f, y_rotation = 0.0f, z_rotation = 0.0f;
GLfloat scale = 1.0f;

void new_func_size_callback(GLFWwindow* window, int width, int height){
    if(!height){
        height = 0;
    }
    glViewport(0, 0, width, height);
}

GLfloat* get_figure(){
    GLfloat* vertex =(GLfloat*) malloc(sizeof(GLfloat) * (1 + (unsigned)(2.0f/APPROX)) * 9 * 4 * 2);
    GLint j = 0;

    for(GLfloat i = 0.0f; i <= 2.0f*M_PI; i += M_PI*APPROX){
        vertex[j++] = 0.0f;
        vertex[j++] = -chill_height / 2.0f;
        vertex[j++] = 0.0f;

        vertex[j++] = 0.0f;
        vertex[j++] = -1.0f;
        vertex[j++] = 0.0f;


        vertex[j++] = 0.6f * cos(i);
        vertex[j++] = -chill_height / 2.0f;
        vertex[j++] = 0.6f * sin(i);

        vertex[j++] = 0.0f;
        vertex[j++] = -1.0f;
        vertex[j++] = 0.0f;


        vertex[j++] = 0.6f * cos(i + M_PI*APPROX);
        vertex[j++] = -chill_height / 2.0f;
        vertex[j++] = 0.6f * sin(i + M_PI*APPROX);

        vertex[j++] = 0.0f;
        vertex[j++] = -1.0f;
        vertex[j++] = 0.0f;
    }

    for(GLfloat i = 0.0f; i <= 2*M_PI; i += M_PI*APPROX){
        vertex[j++] = 0.0f;
        vertex[j++] = -chill_height / 2;
        vertex[j++] = 0.0f;

        vertex[j++] = 0.0f;
        vertex[j++] = 1.0f;
        vertex[j++] = 0.0f;


        vertex[j++] = 0.6f * cos(i);
        vertex[j++] = chill_height / 2;
        vertex[j++] = 0.6f * sin(i);

        vertex[j++] = 0.0f;
        vertex[j++] = 1.0f;
        vertex[j++] = 0.0f;


        vertex[j++] = 0.6f * cos(i + M_PI*APPROX);
        vertex[j++] = chill_height / 2;
        vertex[j++] = 0.6f * sin(i + M_PI*APPROX);

        vertex[j++] = 0.0f;
        vertex[j++] = 1.0f;
        vertex[j++] = 0.0f;
    }

    for(GLfloat i = 0.0f; i <= 2*M_PI; i += M_PI*APPROX){
        GLfloat ax = cos(i) - cos(i + M_PI*APPROX);
        GLfloat ay = 0.0f;
        GLfloat az = sin(i) - sin(i + M_PI * APPROX);
        
        GLfloat bx = 0.0f;
        GLfloat by = 1.0f;
        GLfloat bz = 0.0f;

        GLfloat nx = ay * bz - az * by;
        GLfloat ny = 0.0f;
        GLfloat nz = ax*by - ay*bx;


        vertex[j++] = 0.6f * cos(i);
        vertex[j++] = -chill_height / 2;
        vertex[j++] = 0.6f * sin(i);

        vertex[j++] = nx;
        vertex[j++] = ny;
        vertex[j++] = nz;


        vertex[j++] = 0.6f * cos(i + M_PI*APPROX);
        vertex[j++] = -chill_height / 2;
        vertex[j++] = 0.6f * sin(i + M_PI*APPROX);

        vertex[j++] = nx;
        vertex[j++] = ny;
        vertex[j++] = nz;


        vertex[j++] = 0.6f * cos(i);
        vertex[j++] = chill_height / 2;
        vertex[j++] = 0.6f * sin(i);

        vertex[j++] = nx;
        vertex[j++] = ny;
        vertex[j++] = nz;
    }

    for(GLfloat i = 0.0f; i <= 2*M_PI; i += M_PI*APPROX){
        GLfloat ax = cos(i) - cos(i + M_PI * APPROX);
        GLfloat ay = 0.0f;
        GLfloat az = sin(i) - sin(i + M_PI*APPROX);
        
        GLfloat bx = 0.0f;
        GLfloat by = 1.0f;
        GLfloat bz = 0.0f;

        GLfloat nx = ay * bz - az * by;
        GLfloat ny = 0.0f;
        GLfloat nz = ax*by - ay*bx;

        vertex[j++] = 0.6f * cos(i);
        vertex[j++] = chill_height / 2;
        vertex[j++] = 0.6f * sin(i);

        vertex[j++] = nx;
        vertex[j++] = ny;
        vertex[j++] = nz;


        vertex[j++] = 0.6f * cos(i + M_PI*APPROX);
        vertex[j++] = chill_height / 2;
        vertex[j++] = 0.6f * sin(i + M_PI*APPROX);

        vertex[j++] = nx;
        vertex[j++] = ny;
        vertex[j++] = nz;


        vertex[j++] = 0.6f * cos(i + M_PI*APPROX);
        vertex[j++] = -chill_height / 2;
        vertex[j++] = 0.6f * sin(i + M_PI*APPROX);

        vertex[j++] = nx;
        vertex[j++] = ny;
        vertex[j++] = nz;
    }

    return vertex;
}

int main()
{
    GLfloat AmbStren, DifStren, SpecStren;
    std::cout << "Enter params of light:" << std::endl;
    std::cout << "\t1)Strenght of ambient light from 0.0 to 1.0(recomend 0.1): ";
    std::cin >> AmbStren;
    std::cout << "\t2)Strenght of diffusion light from 0.0 to 1.0(recomend 1.0): ";
    std::cin >> DifStren;
    std::cout << "\t3)Strenght of specular light from 0.0 to 1.0(recomend 0.5): ";
    std::cin >> SpecStren;
    std::cout << "\t4)Enter approximation parametr less then 1.0: ";
    std::cin >> APPROX;
    std::cout << "\n--------------------------------" << std::endl;
    std::cout << "Starting programm!" << std::endl;

	glm::vec3 strenght(AmbStren, DifStren, SpecStren);
    glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Lab_Work #3 Zhukov", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

    glfwSetFramebufferSizeCallback(window, new_func_size_callback);

    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, WIDTH, HEIGHT);

    glEnable(GL_DEPTH_TEST);

    Shader lightingShader("shaders/lighting.vs", "shaders/lighting.frag");
    Shader lampShader("shaders/lamp.vs", "shaders/lamp.frag");

    GLfloat* vertices = get_figure();

    GLuint VBO, containerVAO;
    glGenVertexArrays(1, &containerVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (1 + (unsigned)(2/APPROX)) * 9 * 4 * 2, vertices, GL_STATIC_DRAW);

    glBindVertexArray(containerVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    
    glm::mat4 chillModel = glm::mat4(1.0f);

    while (!glfwWindowShouldClose(window))
    {

        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        do_movement();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lightingShader.Use();
        GLint objectColorLoc = glGetUniformLocation(lightingShader.Program, "objectColor");
        GLint lightColorLoc = glGetUniformLocation(lightingShader.Program, "lightColor");
        GLint lightPosLoc = glGetUniformLocation(lightingShader.Program, "lightPos");
        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        GLint strenPosLoc = glGetUniformLocation(lightingShader.Program, "strenght");

        glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
        glUniform3f(lightColorLoc,  1.0f, 1.0f, 1.0f);
        glUniform3f(lightPosLoc,    lightPos.x, lightPos.y, lightPos.z);
        glUniform3f(viewPosLoc,     camera.Position.x, camera.Position.y, camera.Position.z);
        glUniform3f(strenPosLoc,     strenght.x, strenght.y, strenght.z);

        glm::mat4 view;
        view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(lightingShader.Program,  "view");
        GLint projLoc = glGetUniformLocation(lightingShader.Program,  "projection");

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(containerVAO);
        glm::mat4 model = glm::mat4(1.0f);

        if(ret){
            chillModel = glm::mat4(1.0f);
            ret = false;
        }else{
            glm::vec4 quaternion;
            glm::mat4 rotation, scalem = glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, scale));
            xyz_rotation_to_quaternion(quaternion, x_rotation, y_rotation, z_rotation);
            quaternion_to_matrix(rotation, quaternion);
            chillModel = rotation * scalem * chillModel;
        }

        
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(chillModel));
        glDrawArrays(GL_TRIANGLES, 0, (1 + (unsigned)(2/APPROX)) * 3 * 4);
        glBindVertexArray(0);

		lampShader.Use();

		modelLoc = glGetUniformLocation(lampShader.Program, "model");
        viewLoc = glGetUniformLocation(lampShader.Program, "view");
        projLoc = glGetUniformLocation(lampShader.Program, "projection");

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        model = glm::mat4(1.0);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.05f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, (1 + (unsigned)(2/APPROX)) * 3 * 4);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    free(vertices);
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void do_movement()
{
    if(keys[GLFW_KEY_W])
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if(keys[GLFW_KEY_S])
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if(keys[GLFW_KEY_A])
        camera.ProcessKeyboard(LEFT, deltaTime);
    if(keys[GLFW_KEY_D])
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if(keys[GLFW_KEY_UP]){
        scale = 1.04f;
    } else if(keys[GLFW_KEY_DOWN]){
        scale = 0.96f;
    } else{
        scale = 1.0f;
    }

    if(keys[GLFW_KEY_Y]){
        x_rotation = glm::radians(5.0f);
    } else if(keys[GLFW_KEY_T]){
        x_rotation = -glm::radians(5.0f);
    } else{
        x_rotation = 0.0f;
    }

    if(keys[GLFW_KEY_G]){
        y_rotation = -glm::radians(5.0f);
    } else if(keys[GLFW_KEY_H]){
        y_rotation = glm::radians(5.0f);
    } else{
        y_rotation = 0.0f;
    }

    if(keys[GLFW_KEY_B]){
        z_rotation = -glm::radians(5.0f);
    } else if(keys[GLFW_KEY_N]){
        z_rotation = glm::radians(5.0f);
    } else{
        z_rotation = 0.0f;
    }
    if(keys[GLFW_KEY_R]){
        ret = true;
    }
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
