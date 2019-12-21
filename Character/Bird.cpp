#include "Bird.h"
#include "../Core/Context.h"
#include "../Core/Tweeny.h"
#include "../Core/Signal.h"
#include <random>

namespace Physics
{
    const float Gravity = 3.f;
    const float JumpingPower = -5.f;
}

void Bird::Init()
{
    GetSignal().Connect("game_over", [&]()
    {
       for (auto& b : bird)
       {
           MoveTo(b, 350, 850, 3.5f, Ease::Back);
       }
    });
    m_state = STATES::IDLE;
    bird.resize(3);

    changeTexture();

    for (auto& b : bird)
    {
        b.setScale(1.5f,1.5f);
        b.setPosition(350,300);
        b.setOrigin(b.getLocalBounds().width / 2, b.getLocalBounds().height / 2);
    }
}

void Bird::Update(float dt)
{
    counter += dt;
    if (counter >= 50.0f)
    {
        counter = 0.0f;
        currentIndex += 1;
        if (currentIndex >= 3)
        {
            currentIndex = 0;
        }
    }

    m_timer.Update(std::chrono::milliseconds(15));

    if (m_state == STATES::FALLING)
    {
        for (auto& b : bird)
        {
            b.move(0, Physics::Gravity);
        }
        if (shouldRotate)
        {
            shouldRotate = false;
            for (auto& b : bird)
            {
                RotateTo(b, 360, 1.f, Ease::Back);
                ScaleTo(b, 1.5f, 1.5f, 0.05f, Ease::Back);
            }
        }
    }
    else if(m_state == STATES::FLYING)
    {
        for (auto& b : bird)
        {
            b.move(0, Physics::JumpingPower);
        }
    }
    else
    {
        return;
    }
}

void Bird::Draw(sf::RenderWindow &window)
{
    window.draw(bird[static_cast<size_t>(currentIndex)]);
}

sf::FloatRect Bird::GetBounds()
{
    sf::FloatRect rect = bird[0].getGlobalBounds();
    rect.width -= 15;
    rect.height -= 15;
    return rect;
}

void Bird::changeTexture()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> birdNumber(1,3);
    int index = birdNumber(mt);
    auto& context = Context::GetContext();
    if (index == 1)
    {
        bird[0].setTexture(context.Get(Context::Bird1));
        bird[1].setTexture(context.Get(Context::Bird2));
        bird[2].setTexture(context.Get(Context::Bird3));
    }
    if (index == 2)
    {
        bird[0].setTexture(context.Get(Context::bBird1));
        bird[1].setTexture(context.Get(Context::bBird2));
        bird[2].setTexture(context.Get(Context::bBird3));
    }
    else if(index == 3)
    {
        bird[0].setTexture(context.Get(Context::rBird1));
        bird[1].setTexture(context.Get(Context::rBird2));
        bird[2].setTexture(context.Get(Context::rBird3));
    }
}

void Bird::RestartLevel()
{
    m_state = STATES::IDLE;
    changeTexture();
    for (auto& b : bird)
    {
        b.setPosition(350,300);
    }
}

void Bird::InputEvent(sf::Event& event)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) and isPressed == false)
    {
        shouldRotate = true;
        for (auto& b : bird)
        {
            RotateTo(b, -45, 0.5f, Ease::Back);
            ScaleTo(b, 1.3f, 1.3f, 0.05f, Ease::Back);
        }
        m_state = STATES::FLYING;
        isPressed = true;
        m_timer.RunOnceAfter(std::chrono::milliseconds(225), [&]
        {
            m_state = STATES::FALLING;
        });
    }
    if (event.type == sf::Event::MouseButtonReleased)
    {
        isPressed = false;
    }
}
