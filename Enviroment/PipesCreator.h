#pragma once
#include "Pipe.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Character/Bird.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "../Core/BitMapFont.h"

class PipesCreator
{
public:
    PipesCreator(Bird& bird);

    void Update(float dt);
    void Draw(sf::RenderWindow& window);
    void CleanAfterOutOfBonds();
    void CheckForCollision();
    void CheckForCollisionScore();
    void RestartLevel();

private:
    Bird& m_bird;
    int counter = 2.0f;
    std::vector<sf::RectangleShape> m_shape;
    std::vector<Pipe> m_pipes;

    int currentNumber = 0;
    BitMapFont bitfont;
    std::vector<sf::Sprite> flyingSprites;
};
