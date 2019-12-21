#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "Core/Context.h"
#include "Core/Tweeny.h"
#include <random>
#include "Core/GameController.h"
int main()
{
    ////////////////////////////////////////////////////////////////
    sf::RenderWindow window(sf::VideoMode(800,600), "Flappy Bird");
    window.setFramerateLimit(60);

    auto& context = Context::GetContext();
    context.InitResources();
    ////////////////////////////////////////////////////////////////

    GameController m_controller;
    m_controller.Init();

    sf::Clock deltaClock;
    while (window.isOpen())
    {
       window.clear(sf::Color::White);
       sf::Event event;
       while(window.pollEvent(event))
       {
           if(event.type == sf::Event::Closed or
              sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
           {
               window.close();
           }
       }
       Tweeny::Update();
       auto delta_time = deltaClock.restart();
       float dt = delta_time.asMilliseconds();
       //////////////////////////////
       m_controller.Update(dt);
       m_controller.Event(event);
       m_controller.Draw(window);
       //////////////////////////////
       window.display();
    }

    return 0;
}



