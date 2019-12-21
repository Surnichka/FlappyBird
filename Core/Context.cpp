#include "Context.h"

Context& Context::GetContext()
{
    static Context context;
    return context;
}

void Context::InitResources()
{
    m_resources[Pipe].loadFromFile("../learnSFML/Assets/pipe-green.png");
    m_resources[Bird1].loadFromFile("../learnSFML/Assets/yellowbird-downflap.png");
    m_resources[Bird2].loadFromFile("../learnSFML/Assets/yellowbird-midflap.png");
    m_resources[Bird3].loadFromFile("../learnSFML/Assets/yellowbird-upflap.png");
    m_resources[bBird1].loadFromFile("../learnSFML/Assets/bluebird-downflap.png");
    m_resources[bBird2].loadFromFile("../learnSFML/Assets/bluebird-midflap.png");
    m_resources[bBird3].loadFromFile("../learnSFML/Assets/bluebird-upflap.png");
    m_resources[rBird1].loadFromFile("../learnSFML/Assets/redbird-downflap.png");
    m_resources[rBird2].loadFromFile("../learnSFML/Assets/redbird-midflap.png");
    m_resources[rBird3].loadFromFile("../learnSFML/Assets/redbird-upflap.png");
    m_resources[Base].loadFromFile("../learnSFML/Assets/base.png");
    m_resources[Background].loadFromFile("../learnSFML/Assets/background-day.png");
    m_resources[BackgroundNight].loadFromFile("../learnSFML/Assets/background-night.png");
    m_resources[GameOver].loadFromFile("../learnSFML/Assets/gameover.png");

    m_resources[zero].loadFromFile("../learnSFML/Assets/0.png");
    m_resources[one].loadFromFile("../learnSFML/Assets/1.png");
    m_resources[two].loadFromFile("../learnSFML/Assets/2.png");
    m_resources[three].loadFromFile("../learnSFML/Assets/3.png");
    m_resources[four].loadFromFile("../learnSFML/Assets/4.png");
    m_resources[five].loadFromFile("../learnSFML/Assets/5.png");
    m_resources[six].loadFromFile("../learnSFML/Assets/6.png");
    m_resources[seven].loadFromFile("../learnSFML/Assets/7.png");
    m_resources[eight].loadFromFile("../learnSFML/Assets/8.png");
    m_resources[nine].loadFromFile("../learnSFML/Assets/9.png");
}

sf::Texture& Context::Get(ResourceID key)
{
    return m_resources[key];
}
