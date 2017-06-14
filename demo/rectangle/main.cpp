#include <NNE/Engine.hpp>
#include <NNE/VAO.hpp>
#include <NNE/BO.hpp>
#include <NNE/ShaderProgram.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>

const GLchar* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 color;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position, 1.0);\n"
    "ourColor = color;\n"
    "}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
    "in vec3 ourColor;\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(ourColor, 1.0f);\n"
    "}\n\0";

int main() {
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 4;
    settings.minorVersion = 0;

    sf::Window window(sf::VideoMode(800, 600, 32), "OpenGL", sf::Style::Titlebar | sf::Style::Close, settings);
    window.setFramerateLimit(60);

    std::cout << window.getSettings().majorVersion << "." << window.getSettings().minorVersion << "\n";

    window.setActive(true);

    NNE::Engine::initialize();

    NNE::ShaderProgram shaderProgram;
    shaderProgram.loadShader(vertexShaderSource, GL_VERTEX_SHADER);
    shaderProgram.loadShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    shaderProgram.link();

    GLfloat vertices[] = {
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // Top Right
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // Bottom Right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // Bottom Left
        -0.5f,  0.5f, 0.0f, 0.3f, 0.3f, 0.3f   // Top Left
    };
    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3,  // First Triangle
        1, 2, 3   // Second Triangle
    };

    NNE::VAO vao;
    NNE::BO vbo, ebo;

    vao.bind();
    vbo.bind(GL_ARRAY_BUFFER);
    vbo.loadData(sizeof(vertices), vertices, GL_STATIC_DRAW);

    ebo.bind(GL_ELEMENT_ARRAY_BUFFER);
    ebo.loadData(sizeof(indices), indices, GL_STATIC_DRAW);

    vao.configure({
            {3, GL_FLOAT, GL_FALSE, (GLvoid*)0},
            {3, GL_FLOAT, GL_FALSE, (GLvoid*)(3 * sizeof(GLfloat))}
        },
        6 * sizeof(GLfloat)
    );

    vbo.unbind();
    vao.unbind();
    ebo.unbind();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear the screen
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.use();
        vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        vao.unbind();

        // Swap buffers
        window.display();
    }

    return 0;
}
