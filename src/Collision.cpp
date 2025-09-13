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

