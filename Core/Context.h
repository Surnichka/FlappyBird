#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <map>

class Context
{
public:
    enum ResourceID {
      Pipe, Bird1, Bird2, Bird3, bBird1, bBird2, bBird3, rBird1, rBird2, rBird3,
        Background, BackgroundNight, GameOver, Base,
        zero, one, two, three, four, five, six, seven, eight, nine
    };

    static Context& GetContext();
    void InitResources();
    sf::Texture& Get(ResourceID key);

private:
    std::map<ResourceID, sf::Texture> m_resources;
};
