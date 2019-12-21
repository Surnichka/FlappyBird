#pragma once
#include <SFML/Graphics/Sprite.hpp>

enum class Ease
{
    Linear, Back, Bounce, Elastic
};

float Lerp(float start, float end, float progress);

void RotateTo(sf::Sprite& sprite, float rotation, float duration, Ease ease = Ease::Linear);
void RotateBy(sf::Sprite& sprite, float rotation, float duration, Ease ease = Ease::Linear);
void ScaleBy(sf::Sprite& sprite, float scaleX, float scaleY, float duration, Ease ease = Ease::Linear);
void ScaleTo(sf::Sprite& sprite, float scaleX, float scaleY, float duration, Ease ease = Ease::Linear);
void MoveBy(sf::Sprite& sprite, float x, float y, float duration, Ease ease = Ease::Linear);
void MoveTo(sf::Sprite& sprite, float x, float y, float duration, Ease ease = Ease::Linear);

namespace Tweeny
{
void Update();
bool IsRunning(const sf::Sprite& sprite);
void StopTweeny(const sf::Sprite &sprite);
}
