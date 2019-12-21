#include "ScrollingBackground.h"
#include "../Core/Context.h"
#include <random>

void ScrollingBackgorund::Init()
{
    auto& context = Context::GetContext();
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> backgroundNumber(1,2);
    int index = backgroundNumber(mt);
    if (index == 1)
    {
        firstBackground.setTexture(context.Get(Context::Background));
        secondBackground.setTexture(context.Get(Context::Background));
    }
    else
    {
        firstBackground.setTexture(context.Get(Context::BackgroundNight));
        secondBackground.setTexture(context.Get(Context::BackgroundNight));
    }

    base1.setTexture(context.Get(Context::Base));
    base1.setScale(2.4f, 1.f);
    base1.setPosition(0, 500);
    base2.setTexture(context.Get(Context::Base));
    base2.setScale(2.4f, 1.f);
    base2.setPosition(805, 500);

    firstBackground.setScale(2.8f,1.2f);
    secondBackground.setScale(2.8f,1.2f);
    secondBackground.setPosition(800, 0);
}

void ScrollingBackgorund::Update()
{
    if (firstBackground.getPosition().x <= -800)
    {
        firstBackground.setPosition(800,0);
    }
    if (secondBackground.getPosition().x <= -800)
    {
        secondBackground.setPosition(800,0);
    }
    if (base1.getPosition().x <= - 800)
    {
        base1.setPosition(805, 500);
    }
    if (base2.getPosition().x <= - 800)
    {
        base2.setPosition(805, 500);
    }

    base1.move(-3.0, 0);
    base2.move(-3.0, 0);

    firstBackground.move(-3.f,0);
    secondBackground.move(-3.f,0);
}

void ScrollingBackgorund::Draw(sf::RenderWindow &window)
{
    window.draw(firstBackground);
    window.draw(secondBackground);
    window.draw(base1);
    window.draw(base2);
}
