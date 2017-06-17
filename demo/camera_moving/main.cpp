#include <NNE/Engine.hpp>
#include <NNE/VAO.hpp>
#include <NNE/BO.hpp>
#include <NNE/ShaderProgram.hpp>
#include <NNE/Camera/PerspectiveCamera.hpp>
#include <NNE/Texture.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <iostream>
#include <cmath>

int main() {
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 4;
    settings.minorVersion = 0;

    sf::Window window(sf::VideoMode(800, 600, 32), "OpenGL", sf::Style::Titlebar | sf::Style::Close, settings);
    window.setFramerateLimit(60);

    std::cout << window.getSettings().majorVersion << "." << window.getSettings().minorVersion << "\n";

    glEnable(GL_DEPTH_TEST);

    window.setActive(true);

    NNE::Engine::initialize();

    NNE::ShaderProgram shaderProgram;
    shaderProgram.loadShaderFromFile("../data/shader.vert", GL_VERTEX_SHADER);
    shaderProgram.loadShaderFromFile("../data/shader.frag", GL_FRAGMENT_SHADER);
    shaderProgram.link();

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3 (2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    NNE::VAO vao;
    NNE::BO vbo;

    vao.bind();
    vbo.bind(GL_ARRAY_BUFFER);
    vbo.loadData(sizeof(vertices), vertices, GL_STATIC_DRAW);


    vao.configure({
            {3, GL_FLOAT, GL_FALSE, (GLvoid*)0},
            {2, GL_FLOAT, GL_FALSE, (GLvoid*)(3 * sizeof(GLfloat))}
        },
        5 * sizeof(GLfloat)
    );

    vbo.unbind();
    vao.unbind();

    NNE::Texture2D texture;
    NNE::Texture2D::activateTexture(0);
    texture.bind();
    texture.setTextureWrapping(GL_REPEAT, GL_REPEAT);
    texture.setTextureFiltering(GL_LINEAR, GL_LINEAR);

    sf::Image img;
    if (!img.loadFromFile("../data/container.jpg")) {
        std::cout << "Can't load the image\n";
        return 1;
    } else {
        texture.loadImage(0, GL_RGBA, img.getSize().x, img.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr());
        texture.generateMipmap();
    }

    shaderProgram.storeUniform(1, "combined");
    shaderProgram.storeUniform(2, "model");

    shaderProgram.use();
    shaderProgram.setInt(shaderProgram.getUniformLocation("texture1"), 0);

    NNE::PerspectiveCamera camera(800, 600, 45.f, 0.1f, 100.f);
    camera.setPosition({0.f, 0.f, 10.f});
    camera.setDirection({0.f, 0.f, -1.f});
    camera.setUp({0.f, 1.f, 0.f});

    auto oldMousePos = sf::Mouse::getPosition(window);

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float dt = clock.restart().asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            camera.setPosition(camera.getPosition() + (camera.getDirection() * (100.f * dt)));
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            camera.setPosition(camera.getPosition() - (camera.getDirection() * (100.f * dt)));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            camera.setPosition(camera.getPosition() - (camera.getRight() * (100.f * dt)));
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            camera.setPosition(camera.getPosition() + (camera.getRight() * (100.f * dt)));
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            auto mousePos = sf::Mouse::getPosition(window);

            auto mouseDt = mousePos - oldMousePos;
            std::cout << mouseDt.x << " " << mouseDt.y << "\n";

            float newYaw = camera.getYaw() - mouseDt.x * 0.2f;

            if (newYaw > 360.0f) {
                newYaw -= 360.0f;
            } else if (newYaw < -360.0f) {
                newYaw += 360.0f;
            }

            camera.setYaw(newYaw);

            float newPitch = camera.getPitch() + mouseDt.y * 0.2f;

            if (newPitch > 89.f) newPitch = 89.f;
            else if (newPitch < -89.f) newPitch = -89.f;

            camera.setPitch(newPitch);

            std::cout << camera.getYaw() << "\n";
        }

        oldMousePos = sf::Mouse::getPosition(window);

        shaderProgram.use();

        if (camera.update()) {
            shaderProgram.setMat4(1, camera.getCombined());
        }

        // Clear the screen
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        NNE::Texture2D::activateTexture(0);
        texture.bind();

        vao.bind();
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shaderProgram.setMat4(2, model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        vao.unbind();

        // Swap buffers
        window.display();
    }

    return 0;
}
