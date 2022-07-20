#include    <glad/gl.h>
#include    <GLFW/glfw3.h>

#include    <iostream>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
static const char* shaderCodeVertex = R"(

#version 460 core

layout (location=0) out vec3 color;

const vec2 pos[3] = vec2[3](
    vec2(-0.6, -0.4),
    vec2(0.6, -0.4),
    vec2(0.0, 0.6)
);

const vec3 col[3] = vec3[3](
    vec3(1.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(0.0, 0.0, 1.0)
);

void main()
{
    gl_Position = vec4(pos[gl_VertexID], 0.0, 1.0);
    color = col[gl_VertexID];
}

)";

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
static const char* shaderCodeFragment = R"(

#version 460 core

layout (location=0) in vec3 color;
layout (location=0) out vec4 out_FragColor;

void main()
{
    out_FragColor = vec4(color, 1.0);
}

)";

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int main()
{
    // Функция обратного вызова для обработки ошибок GLFW
    glfwSetErrorCallback(
        [](int error, const char *description)
        {
            std::cout << "Error: "
                      << error << " "
                      << description << std::endl;
        }
    );

    // Инициализация GLFW
    if (!glfwInit())
        exit(EXIT_FAILURE);

    // Сообщаем GLFW версию OpenGL и используемый профиль
    // (OpenGL 4.6 Core Profile)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Создаем окно приложения
    GLFWwindow *window = glfwCreateWindow(1280,
                                          720,
                                          "Simple example",
                                          nullptr,
                                          nullptr);

    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Задаем callback-функцию для обработки нажатия клавиш
    glfwSetKeyCallback(window,
       [](GLFWwindow * window, int key, int scancode, int action, int mods)
       {
           (void) scancode;
           (void) mods;

           if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
           {
               glfwSetWindowShouldClose(window, GLFW_TRUE);
           }
       }

    );

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

    GLuint VAO;
    glCreateVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    const GLuint shaderVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shaderVertex, 1, &shaderCodeVertex, nullptr);
    glCompileShader(shaderVertex);

    const GLuint shaderFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shaderFragment, 1, &shaderCodeFragment, nullptr);
    glCompileShader(shaderFragment);

    const GLuint program = glCreateProgram();
    glAttachShader(program, shaderVertex);
    glAttachShader(program, shaderFragment);
    glLinkProgram(program);
    glUseProgram(program);

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(program);
    glDeleteShader(shaderFragment);
    glDeleteShader(shaderVertex);
    glDeleteVertexArrays(1, &VAO);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
