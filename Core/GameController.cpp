#include "GameController.h"
#include "../Core/Context.h"
#include "Tweeny.h"
#include "../Core/Signal.h"
#include <iostream>
#include <SFML/Graphics/Text.hpp>

void GameController::Init()
{
    GetSignal().Connect("game_over", [&]()
    {
        isGameOver = true;
        MoveTo(m_gameOver, 300, 250, 1.5f, Ease::Elastic);
    });

    m_background.Init();
    m_bird.Init();
    m_gameOver.setTexture(Context::GetContext().Get(Context::GameOver));
    m_gameOver.setPosition(300,0);
    font.loadFromFile("../learnSFML/Assets/CHUBBY.TTF");
}

void GameController::Update(float dt)
{
    if (isGameOver)
    {
        return;
    }

    m_background.Update();
    m_bird.Update(dt);
    m_pipes.Update(dt);
}

void GameController::Draw(sf::RenderWindow &window)
{
    m_background.Draw(window);
    m_pipes.Draw(window);
    m_bird.Draw(window);

    if (isGameOver)
    {
        window.draw(m_gameOver);
        text.setPosition(200, 330);
        text.setFont(font);
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(1.f);
        text.setString("Press RIGHT MOUSE for New Game");
        window.draw(text);
    }
}

void GameController::Event(sf::Event &event)
{
    if (isGameOver)
    {
//        if (event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
        {
            m_pipes.RestartLevel();
            m_bird.RestartLevel();
            for (auto& b : m_bird.bird)
            {
                Tweeny::StopTweeny(b);
                b.setRotation(0);
            }
            isGameOver = false;
        }
    }

    m_bird.InputEvent(event);
}
