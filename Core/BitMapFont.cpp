#include "BitMapFont.h"
#include "../Core/Context.h"

void BitMapFont::Init()
{
    auto& context = Context::GetContext();
    bitMapFont[0] = &context.Get(Context::zero);
    bitMapFont[1] = &context.Get(Context::one);
    bitMapFont[2] = &context.Get(Context::two);
    bitMapFont[3] = &context.Get(Context::three);
    bitMapFont[4] = &context.Get(Context::four);
    bitMapFont[5] = &context.Get(Context::five);
    bitMapFont[6] = &context.Get(Context::six);
    bitMapFont[7] = &context.Get(Context::seven);
    bitMapFont[8] = &context.Get(Context::eight);
    bitMapFont[9] = &context.Get(Context::nine);
}

BitMapText BitMapFont::GenerateBitmap(std::string numbers)
{
    return BitMapText(numbers, this);
}

sf::Sprite BitMapFont::GetNumber(int number)
{
    sf::Sprite sprite;
    sprite.setTexture(*bitMapFont.at(number));
    return sprite;
}

BitMapText::BitMapText(std::string numbers, BitMapFont *font)
{
    for(size_t i = 0; i < numbers.size(); i++)
    {
        auto digit = numbers[i] - '0';
        auto texture = font->bitMapFont.at(digit);
        sf::Sprite spr;
        spr.setTexture(*texture);
        spr.setPosition((i * 24.0f), 0.0f);
        sprites.emplace_back(spr);
    }
}

void BitMapText::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    for(const auto& spr : sprites)
    {
        target.draw(spr, states);
    }
}
