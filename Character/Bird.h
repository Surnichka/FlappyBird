#pragma once
#include <memory>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Core/Timer.hpp"

class Bird
{
public:
    enum STATES {IDLE, FLYING, FALLING};

    void Init();
    void Update(float dt);
    void InputEvent(sf::Event& event);
    void Draw(sf::RenderWindow& window);
    sf::FloatRect GetBounds();

    void RestartLevel();

    STATES m_state;
    std::vector<sf::Sprite> bird;
private:
    void changeTexture();
private:
    Timer m_timer;
    int currentIndex = 0;
    int counter = 0.0f;

    bool shouldRotate = false;
    bool isPressed = false;
};
