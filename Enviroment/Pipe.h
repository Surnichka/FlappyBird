#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Pipe
{
public:
    void Init();
    void Update(float dt);
    void Draw(sf::RenderWindow& window);
    void SetUpPipePosition(int pos);
    void SetDownPipePosition(int pos);
    void CheckForOutOfBonds();
    sf::FloatRect GetUpBounds();
    sf::FloatRect GetDownBounds();

    bool isOutOfBonds = false;
private:
    sf::Sprite m_upPipe;
    sf::Sprite m_downPipe;
};
