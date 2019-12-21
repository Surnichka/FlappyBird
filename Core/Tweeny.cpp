#include "Tweeny.h"
#include <vector>
#include <functional>
#include <cassert>
#include <iostream>
#include <cmath>
using namespace std;

struct TweenUpdateFunc
{
    TweenUpdateFunc() = default;
    explicit TweenUpdateFunc(sf::Sprite& sp)
        : sprite(&sp) {}

    bool operator()()
    {
        return Update();
    }
    std::function<bool()> Update;
    sf::Sprite* sprite;
};


static std::vector<TweenUpdateFunc> Tweenies;
static float deltaTime = 0.016f;

float ApplyEasing(float t, Ease ease)
{
    switch(ease)
    {
        case Ease::Linear: return t;
        case Ease::Back: {double s = 2.5; t--; return t * t * ((s + 1) * t + s) + 1;}
        case Ease::Elastic: return sin(-13 * M_PI_2 * (t + 1)) * pow(2, -10 * t) + 1;
        case Ease::Bounce:
        {
            if (t < 4. / 11.) { return (121. * t * t) / 16.;} else if (t < 8. / 11.) { return (363. / 40. * t * t) - (99 / 10. * t) + 17 / 5.; } else if (t < 9. / 10.) { return (4356. / 361. * t * t) - (35442. / 1805. * t) + 16061. / 1805.; } else { return (54. / 5. * t * t) - (513. / 25. * t) + 268. / 25.;};
        }
    }
    return t;
}

void RotateTo(sf::Sprite& sprite, float rotation, float duration, Ease ease)
{
    assert(duration > 0.0f);
    TweenUpdateFunc action(sprite);
    action.Update = [&sprite, initial = sprite.getRotation(), ease, rotation, duration, elapsed = 0.0f]() mutable
    {
        elapsed = std::min(elapsed + deltaTime, duration);
        const auto progress = ApplyEasing(elapsed / duration, ease);

        float next = Lerp(initial, rotation, progress);
        sprite.setRotation(next);

        return elapsed >= duration;
    };
    Tweenies.emplace_back(std::move(action));
}

void RotateBy(sf::Sprite& sprite, float rotation, float duration, Ease ease)
{
    assert(duration > 0.0f);
    TweenUpdateFunc action(sprite);
    action.Update = [&sprite, ease, prev = 0.0f, rotation, duration, elapsed = 0.0f]() mutable
    {
        elapsed = std::min(elapsed + deltaTime, duration);
        const auto progress = ApplyEasing(elapsed / duration, ease);

        float next = Lerp(0.0f, rotation, progress);
        sprite.rotate(next - prev);
        prev = next;

        return elapsed >= duration;
    };
    Tweenies.emplace_back(std::move(action));
}

void MoveBy(sf::Sprite& sprite, float x, float y, float duration, Ease ease)
{
    assert(duration > 0.0f);
    TweenUpdateFunc action(sprite);
    action.Update = [&sprite, ease, prev = sf::Vector2f(0, 0), x, y, duration, elapsed = 0.0f]() mutable
    {
        elapsed = std::min(elapsed + deltaTime, duration);
        const auto progress = ApplyEasing(elapsed / duration, ease);

        sf::Vector2f next = {Lerp(0.0f, x, progress), Lerp(0.0f, y, progress)};
        sprite.move(next - prev);
        prev = next;

        return elapsed >= duration;
    };
    Tweenies.emplace_back(std::move(action));
}

void MoveTo(sf::Sprite& sprite, float x, float y, float duration, Ease ease)
{
    assert(duration > 0.0f);
    TweenUpdateFunc action(sprite);
    action.Update = [&sprite, initial = sprite.getPosition(), ease, x, y, duration, elapsed = 0.0f]() mutable
    {
        elapsed = std::min(elapsed + deltaTime, duration);
        const auto progress = ApplyEasing(elapsed / duration, ease);

        sf::Vector2f next = {Lerp(initial.x, x, progress), Lerp(initial.y, y, progress)};
        sprite.setPosition(next);

        return elapsed >= duration;
    };
    Tweenies.emplace_back(std::move(action));
}

void ScaleBy(sf::Sprite& sprite, float scaleX, float scaleY, float duration, Ease ease)
{
    assert(duration > 0.0f);
    TweenUpdateFunc action(sprite);
    action.Update = [&sprite, ease, prev = sf::Vector2f(0.0f, 0.0f), scaleX, scaleY, duration, elapsed = 0.0f]() mutable
    {
        elapsed = std::min(elapsed + deltaTime, duration);
        const auto progress = ApplyEasing(elapsed / duration, ease);

        sf::Vector2f next = {Lerp(0.0f, scaleX, progress),Lerp(0.0f, scaleY, progress)};
        auto step = next - prev;
        sprite.setScale(sprite.getScale() + step);
        prev = next;

        return elapsed >= duration;
    };
    Tweenies.emplace_back(std::move(action));
}

void ScaleTo(sf::Sprite& sprite, float scaleX, float scaleY, float duration, Ease ease)
{
    assert(duration > 0.0f);
    TweenUpdateFunc action(sprite);
    action.Update = [&sprite, initial = sprite.getScale(), ease, scaleX, scaleY, duration, elapsed = 0.0f]() mutable
    {
        elapsed = std::min(elapsed + deltaTime, duration);
        const auto progress = ApplyEasing(elapsed / duration, ease);

        sf::Vector2f next = {Lerp(initial.x, scaleX, progress), Lerp(initial.y, scaleY, progress)};
        sprite.setScale(next);

        return elapsed >= duration;
    };
    Tweenies.emplace_back(std::move(action));
}

float Lerp(float start, float end, float progress)
{
    return start + (progress * (end - start));
}

void Tweeny::Update()
{
    auto iter = std::remove_if(Tweenies.begin(), Tweenies.end(), [](auto& tween)
    {
        return tween();
    });
    Tweenies.erase(iter, Tweenies.end());
}

bool Tweeny::IsRunning(const sf::Sprite &sprite)
{
    auto iter = std::find_if(Tweenies.begin(), Tweenies.end(), [&sprite](const TweenUpdateFunc& obj)
    {
        return (obj.sprite == &sprite);
    });
    return iter != Tweenies.end();
}

void Tweeny::StopTweeny(const sf::Sprite &sprite)
{
    auto iter = std::find_if(Tweenies.begin(), Tweenies.end(), [&sprite](const TweenUpdateFunc& obj)
    {
        return (obj.sprite == &sprite);
    });
    Tweenies.erase(iter, Tweenies.end());
}
