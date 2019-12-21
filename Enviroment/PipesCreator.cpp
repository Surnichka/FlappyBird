#include "PipesCreator.h"
#include <random>
#include "../Core/Tweeny.h"
#include "../Core/Signal.h"

namespace
{
    std::random_device rd;
    std::mt19937 mt(rd());
}

PipesCreator::PipesCreator(Bird &bird) : m_bird(bird)
{
    bitfont.Init();
    flyingSprites.resize(20);
}

void PipesCreator::Update(float dt)
{
    counter += dt;
    for (auto& p : m_pipes)
    {
        p.Update(dt);
    }

    if (counter >= 1000.f)
    {
        counter = 0.f;

        std::uniform_int_distribution<int> upPos(-140, -70);
        std::uniform_int_distribution<int> downPos(350, 390);

        int up = upPos(mt);
        int down = downPos(mt);

        Pipe pipe;
        pipe.Init();
        pipe.SetUpPipePosition(up);
        pipe.SetDownPipePosition(down);
        m_pipes.push_back(pipe);

        sf::RectangleShape shape;
        shape.setSize({10,600});
        shape.setPosition(900, 0);
        m_shape.push_back(shape);
    }
    CheckForCollision();
    CleanAfterOutOfBonds();
    CheckForCollisionScore();

    for (auto& sh : m_shape)
    {
        sh.move(-4.0f,0);
    }
}

void PipesCreator::Draw(sf::RenderWindow &window)
{
    for(auto& p : m_pipes)
    {
        p.Draw(window);
    }

    auto bitText = bitfont.GenerateBitmap(std::to_string(currentNumber));
    bitText.setPosition(365, 50);
    window.draw(bitText);
    for(auto& sp : flyingSprites)
    {
        window.draw(sp);
    }
}

void PipesCreator::CleanAfterOutOfBonds()
{
    auto iter = remove_if(m_pipes.begin(), m_pipes.end(), [](const Pipe& pipe)
    {
       return pipe.isOutOfBonds;
    });
    m_pipes.erase(iter, m_pipes.end());
}

void PipesCreator::CheckForCollision()
{
    for (auto& p : m_pipes)
    {
        if (p.GetUpBounds().intersects(m_bird.GetBounds()) or
            p.GetDownBounds().intersects(m_bird.GetBounds()))
        {
            GetSignal().Dispatch("game_over");
        }
    }
}

void PipesCreator::CheckForCollisionScore()
{
    for (auto& s : m_shape)
    {
        if (s.getGlobalBounds().intersects(m_bird.GetBounds()))
        {
            currentNumber += 1;
            for(int i = 0; i < flyingSprites.size(); i++)
            {
                if(Tweeny::IsRunning(flyingSprites[i]))
                {
                    continue;
                }
                std::uniform_int_distribution<int> dist(20, 100);
                flyingSprites[i] = bitfont.GetNumber(1);
                auto xPos = i % 2 ? - 50 : 850;
                flyingSprites[i].setPosition(xPos + dist(mt), dist(mt));
                flyingSprites[i].setScale(1.0f, 1.0f);

                std::uniform_real_distribution<float> time(0.5f, 1.5f);
                auto duration = time(mt);
                MoveTo(flyingSprites[i], 380, 50, duration, Ease::Back);
                ScaleTo(flyingSprites[i], 0.0f, 0.0f, duration);
            }
        }
    }
}

void PipesCreator::RestartLevel()
{
    m_pipes.clear();
    m_shape.clear();
    currentNumber = 0;
}

