#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <map>

class BitMapFont;
struct BitMapText : public sf::Drawable, public sf::Transformable
{
    explicit BitMapText(std::string numbers, BitMapFont* font);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    std::vector<sf::Sprite> sprites;
};

class BitMapFont
{
public:
    void Init();
    BitMapText GenerateBitmap(std::string numbers);
	sf::Sprite GetNumber(int number);
    std::map<int, sf::Texture*> bitMapFont;
};
