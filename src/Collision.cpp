#include <math.h>
#include <iostream>

#include "Math.h"
#include "Collision.h"

bool Collision::StickVsBall(const Stick& stick, const Ball& ball)
{
    sf::Vector2f p0 = stick.m_p0.m_pos;
    sf::Vector2f p1 = stick.m_p1.m_pos;

    sf::Vector2f ab = p1 - p0;
    sf::Vector2f ac = ball.m_pos - p0;

    float abLenSq = ab.x * ab.x + ab.y * ab.y;
    float t = (ab.x * ac.x + ab.y * ac.y) / abLenSq;

    if (t < 0.f) t = 0.f;
    else if (t > 1.f) t = 1.f;

    sf::Vector2f posClose = p0 + t * ab;

    float dist = Math::Length(ball.m_pos - posClose);

    return dist <= ball.m_radius;
}

void Collision::BallVsWindow(Ball& ball, const sf::RenderWindow& window)
{
    sf::Vector2u winS = window.getSize();
    sf::Vector2f& pos = ball.m_pos;
    sf::Vector2f& prePos = ball.m_prePos;
    sf::Vector2f& v = ball.m_v;
    float r = ball.m_radius;

    if (pos.x > winS.x - r)
    {
        pos.x = winS.x - r;
        prePos.x = pos.x + v.x * m_b;
    }
    else if (pos.x < r)
    {
        pos.x = r;
        prePos.x = pos.x + v.x * m_b;
    }

    if (pos.y > winS.y - r)
    {
        pos.y = winS.y - r;
        prePos.y = pos.y + v.y * m_b;
    }
    else if (pos.y < r)
    {
        pos.y = r;
        prePos.y = pos.y + v.y * m_b;
    }
}
