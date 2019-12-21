#include "Pipe.h"
#include "../Core/Context.h"

void Pipe::Init()
{
    auto& context = Context::GetContext();
    m_upPipe.setTexture(context.Get(Context::Pipe));
    m_downPipe.setTexture(context.Get(Context::Pipe));
    m_upPipe.setOrigin(m_upPipe.getLocalBounds().width, m_upPipe.getLocalBounds().height);
    m_upPipe.setRotation(180);
    m_upPipe.setPosition(850,0);
    m_downPipe.setPosition(850,0);
}

void Pipe::Update(float dt)
{
    m_upPipe.move(-4.f,0);
    m_downPipe.move(-4.f,0);
    CheckForOutOfBonds();

}

void Pipe::Draw(sf::RenderWindow &window)
{
    window.draw(m_upPipe);
    window.draw(m_downPipe);
}

void Pipe::SetUpPipePosition(int pos)
{
    m_upPipe.setPosition(m_upPipe.getPosition().x, pos);
}

void Pipe::SetDownPipePosition(int pos)
{
    m_downPipe.setPosition(m_downPipe.getPosition().x, pos);
}

void Pipe::CheckForOutOfBonds()
{
    if (m_downPipe.getPosition().x <= -50)
    {
        isOutOfBonds = true;
    }
}

sf::FloatRect Pipe::GetUpBounds()
{
    return m_upPipe.getGlobalBounds();
}

sf::FloatRect Pipe::GetDownBounds()
{
    return m_downPipe.getGlobalBounds();
}
