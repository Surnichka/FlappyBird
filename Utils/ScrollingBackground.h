#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class ScrollingBackgorund
{
public:
    void Init();
    void Update();
    void Draw(sf::RenderWindow& window);

private:
    sf::Sprite firstBackground;
    sf::Sprite secondBackground;
    sf::Sprite base1;
    sf::Sprite base2;
};
