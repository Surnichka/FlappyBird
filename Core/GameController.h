#pragma once
#include "../Character/Bird.h"
#include "../Enviroment/PipesCreator.h"
#include "../Utils/ScrollingBackground.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class GameController
{
public:
    void Init();
    void Update(float dt);
    void Draw(sf::RenderWindow& window);
    void Event(sf::Event& event);

private:
    Bird m_bird;
    PipesCreator m_pipes{m_bird};
    ScrollingBackgorund m_background;

    sf::Sprite m_gameOver;
    bool isGameOver = false;
    sf::Text text;
    sf::Font font;
};
