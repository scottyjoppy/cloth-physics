#include <math.h>
#include <iostream>

#include "Math.h"
#include "Collision.h"

void Collision::CircleVsCircle(Point& p, Ball& b)
{
    float rSum = b.m_radius + p.m_radius;
    sf::Vector2f diff  = b.m_pos - p.m_pos;
    float dist = Math::Length(diff);

    if (dist < rSum && dist > 0.f)
    {
        sf::Vector2f n = diff / dist;
        float pen = rSum - dist;
        b.m_pos += n * pen;
        b.m_prePos += n * pen * m_b;

        if (!p.m_pinned)
        {
            p.m_pos -= n * pen;
            p.m_prePos -= n * pen * m_b;
        }
    }

}

void Collision::StickVsBall(Stick& stick, Ball& ball)
{
    sf::Vector2f p0 = stick.m_p0.m_pos;
    sf::Vector2f p1 = stick.m_p1.m_pos;

    sf::Vector2f ab = p1 - p0;
    sf::Vector2f ac = ball.m_pos - p0;

    float abLenSq = ab.x * ab.x + ab.y * ab.y;
    float t = (ab.x * ac.x + ab.y * ac.y) / abLenSq;

    t = std::clamp(t, 0.f, 1.f);

    sf::Vector2f posClose = p0 + t * ab;

    sf::Vector2f diff = ball.m_pos - posClose;
    float dist = Math::Length(diff);

    if (dist < ball.m_radius)
    {
        sf::Vector2f n = diff / dist;
        float pen = ball.m_radius - dist;
        ball.m_pos += n * pen;
        ball.m_prePos += n * pen * m_b;
    }
}

void Collision::CircleVsWindow(sf::Vector2f& pos, sf::Vector2f& prePos, sf::Vector2f& v, const float r, const sf::RenderWindow& window)
{
    sf::Vector2u winS = window.getSize();
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
